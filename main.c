#include <SD.h>
#include <Ethernet.h>

#ifndef K15_LED_SERVER_CONFIG_PATH
#define K15_LED_SERVER_CONFIG_PATH "config.ini"
#endif

#ifndef K15_LED_SERVER_DEFAULT_MAC_ADDRESS
#define K15_LED_SERVER_DEFAULT_MAC_ADDRESS "7E:D5:E6:4E:6D"
#endif

#ifndef K15_LED_SERVER_DEFAULT_IP4_ADDRESS
#define K15_LED_SERVER_DEFAULT_IP4_ADDRESS "192.168.1.51"
#endif

#ifndef K15_LED_SERVER_DEFAULT_SERIAL_OUT
#define K15_LED_SERVER_DEFAULT_SERIAL_OUT 1
#endif

typedef enum
{
    K15_LED_SERVER_INIT_SUCCESS = 0x01,
    K15_LED_SERVER_SERIAL_OUT   = 0x02
} kls_flags;

typedef enum
{
    K15_LED_SERVER_CONFIG_PARSER_STATE_READ_TOKEN   = 0,
    K15_LED_SERVER_CONFIG_PARSER_STATE_MAC_ADDRESS  = 1,
    K15_LED_SERVER_CONFIG_PARSER_STATE_IP4_ADDRESS  = 2,
    K15_LED_SERVER_CONFIG_PARSER_STATE_SERIAL_OUT   = 3
} kls_config_parser_state;

typedef struct 
{
    byte flagMask;
    byte macAddress[6];  
    byte ipAddress[4];  
} kls_config;

kls_config config;

void writeToSerial(const char* pMessage)
{
    //if ( ( config.flagMask & K15_LED_SERVER_SERIAL_OUT ) > 0u )
    {
        Serial.print(pMessage);
    }
}

byte asciiCharToByte(char asciiCharacter)
{
    return asciiCharacter - 48;
}

byte isDecimalAscii( char asciiChar )
{
    return asciiChar >= 48 && asciiChar <= 57;
}

byte isHexAscii( char asciiChar )
{
    return asciiChar >= 48 && asciiChar <= 57 || asciiChar >= 'a' && asciiChar <= 'f' || asciiChar >= 'A' && asciiChar <= 'F'; 
}

byte decimalStringToByte( const char* pToken, uint8_t length )
{
    if (length == 0)
    {
        return 0;
    }

    if (*pToken == 0)
    {
        return 0;
    }

    uint8_t multiplier = 1;
    byte decimal = 0;

    for (uint8_t i = 1u; i < length - 1u; ++i)
    {
        decimal += asciiCharToByte(pToken[length - i]) * multiplier;
        multiplier *= 10;
    }

    return decimal;
}

byte isValidIp4AddressToken( const char* pToken )
{
    uint8_t partCount = 0u;
    while(*pToken)
    {
        if (*pToken == '.')
        {
            partCount++;
        }
        else if (!isDecimalAscii(*pToken))
        {
            return 0;
        }

        pToken++;
    }

    return partCount == 3u;
}

byte tokenToIp4Address( byte* ip4Address, const char* pToken )
{
    byte success = 0;
    uint8_t decimalIndex = 0u;
    byte decimal[3u];

    writeToSerial("tokenToIp4Address\n");
    writeToSerial(pToken);

    if (isValidIp4AddressToken(pToken))
    {
        while( *pToken )
        {
            if( *pToken != '.' )
            {
                decimal[decimalIndex++] = *pToken;
            }
            else if( *pToken == '.' ) 
            {
                *ip4Address = decimalStringToByte( decimal, decimalIndex );
                ip4Address++;
            }

            pToken++;
        }

        success = (*pToken == 0);
    }

    if (!success)
    {
        writeToSerial(pToken);
        writeToSerial("is not a valid ip4 address.\n");
    }
   
    return success;
}

byte tokenToMacAddress(byte* macAddress, const char* pToken)
{
    return 1;
}

byte tokenToBool(byte* flagMask, uint8_t bitMask, const char* pToken)
{
    if (pToken[0] == '0')
    {
        *flagMask &= ~bitMask;
        return 1;
    }
    else if (pToken[0] == '1')
    {
        *flagMask |= bitMask;
        return 1;
    }

    return 0;
}

byte stringIsEqual(const char* pStringA, const char* pStringB)
{
    if (pStringA == NULL || pStringB == NULL)
    {
        return 0;
    }

    byte equal = 1;

    while(*pStringA++ && *pStringB++) 
    {
        if (*pStringA != *pStringB)
        {
            equal = 0;
        }
    }

    return equal;
}

void writeDefaultConfigIni()
{
    File configFile = SD.open(K15_LED_SERVER_CONFIG_PATH, FILE_WRITE);

    if( !configFile )
    {
        writeToSerial("Error: Could not create config file '");
        writeToSerial(K15_LED_SERVER_CONFIG_PATH);
        writeToSerial("'\n");
        return;
    }
    
    configFile.print("mac_address=");
    configFile.print(K15_LED_SERVER_DEFAULT_MAC_ADDRESS);
    configFile.print("\n");

    configFile.print("ip4_address=");
    configFile.print(K15_LED_SERVER_DEFAULT_IP4_ADDRESS);
    configFile.print("\n");

    configFile.print("serial_out=");
    configFile.print(K15_LED_SERVER_DEFAULT_SERIAL_OUT);
    configFile.print("\n");

    configFile.close();
}

void seekUntilNewline(File* pFile)
{
    byte tokenChar = 0;
    do 
    {
        tokenChar = pFile->read();
        if (tokenChar == -1)
        {
            return;
        }

    } while(tokenChar != '\n');
}

byte parseConfigFile(kls_config* pConfig)
{
    kls_config_parser_state parserState = K15_LED_SERVER_CONFIG_PARSER_STATE_READ_TOKEN;
    byte token[32] = {0};
    int8_t tokenIndex = 0u;

    File configFile = SD.open(K15_LED_SERVER_CONFIG_PATH, FILE_READ);
    
    while (configFile.peek() != -1)
    {
        byte tokenChar = configFile.read();

        if (tokenChar == '=')
        {
            token[tokenIndex] = 0;

            if (stringIsEqual(token, "mac_address"))
            {
                parserState = K15_LED_SERVER_CONFIG_PARSER_STATE_MAC_ADDRESS;
                tokenIndex = 0;
            }
            else if (stringIsEqual(token, "ip4_address"))
            {
                parserState = K15_LED_SERVER_CONFIG_PARSER_STATE_IP4_ADDRESS;
                tokenIndex = 0;
            }
            else if (stringIsEqual(token, "serial_out"))
            {
                parserState = K15_LED_SERVER_CONFIG_PARSER_STATE_SERIAL_OUT;
                tokenIndex = 0;
            }
            else 
            {
                writeToSerial("Error: Unknown config token '");
                writeToSerial(token);
                writeToSerial("'.\n");

                parserState = K15_LED_SERVER_CONFIG_PARSER_STATE_READ_TOKEN;
            }
        }
        else if (tokenChar == ' ' || tokenChar == '\t')
        {
            //FK: ignore whitespace
            continue;
        }
        else if (tokenChar == '\n')
        {
            token[tokenIndex] = 0;
            if (parserState == K15_LED_SERVER_CONFIG_PARSER_STATE_IP4_ADDRESS)
            {
                if (!tokenToIp4Address(config.ipAddress, token))
                {
                    return 0;
                }

                writeToSerial("ip4address=");
                writeToSerial(token);
                writeToSerial("\n");
            }
            else if (parserState == K15_LED_SERVER_CONFIG_PARSER_STATE_MAC_ADDRESS)
            {
                if (!tokenToMacAddress(config.macAddress, token))
                {
                    return 0;
                }

                writeToSerial("macaddress=");
                writeToSerial(token);
                writeToSerial("\n");
            }
            else if (parserState == K15_LED_SERVER_CONFIG_PARSER_STATE_SERIAL_OUT)
            {
                if (!tokenToBool(&config.flagMask, K15_LED_SERVER_SERIAL_OUT, token))
                {
                    return 0;
                }
            }

            tokenIndex = 0;
            parserState = K15_LED_SERVER_CONFIG_PARSER_STATE_READ_TOKEN;
        }
        else
        {
            if ( ( tokenIndex + 1u ) == sizeof( token ) )
            {
                token[tokenIndex] = 0;

                //FK: seek until new line
                seekUntilNewline(&configFile);

                writeToSerial("Token '");
                writeToSerial(token);
                writeToSerial("is too long (32 character max)\n");
                tokenIndex = 0u;
                continue;
            }

            token[tokenIndex++] = tokenChar;
        }
    }

    return 1;
}

void setup()
{
    Serial.begin( 9600 );
    
    if( !SD.begin(4) )
    {
        writeToSerial("Could not initialize SD library\n");
        
        //FK: TODO: blink red LED
        return;
    }

    if ( !SD.exists( K15_LED_SERVER_CONFIG_PATH ) )
    {
        writeToSerial("Creating default config...\n");
        
        //FK: Create new config ini
        writeDefaultConfigIni();
    }

    if ( !parseConfigFile( &config ) )
    {
        writeToSerial("Could not parse config file.\n");
        return;
    }

    Serial.print(config.ipAddress[0]);
    Serial.print(".");
    Serial.print(config.ipAddress[1]);
    Serial.print(".");
    Serial.print(config.ipAddress[2]);
    Serial.print(".");
    Serial.print(config.ipAddress[3]);
    Serial.print("\n");

    if ( ( config.flagMask & K15_LED_SERVER_SERIAL_OUT ) > 0u )
    {
        Serial.begin( 9600 );
    }

    Ethernet.begin( config.macAddress, config.ipAddress );

    config.flagMask |= K15_LED_SERVER_INIT_SUCCESS;
}

void loop()
{
    if( ( config.flagMask & K15_LED_SERVER_INIT_SUCCESS ) == 0)
    {
        delay( 1000 );
    }
}