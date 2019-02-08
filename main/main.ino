#include <SD.h>
#include <LiquidCrystal.h>
#include <Ethernet.h>

#ifndef K15_CONFIG_PATH
#define K15_CONFIG_PATH "config.ini"
#endif

#ifndef K15_CSGI_CONFIG_PATH
#define K15_CSGI_CONFIG_PATH "k15_lsrv.cfg"
#endif

#ifndef K15_DEFAULT_USER
#define K15_DEFAULT_USER "admin"
#endif

#ifndef K15_DEFAULT_PASSWORD
#define K15_DEFAULT_PASSWORD "1234"
#endif

#ifndef K15_DEFAULT_MAC_ADDRESS
#define K15_DEFAULT_MAC_ADDRESS "7E:D5:E6:4E:6D:8C"
#endif

#ifndef K15_DEFAULT_IP4_ADDRESS
#define K15_DEFAULT_IP4_ADDRESS "192.168.1.78"
#endif

#ifndef K15_DEFAULT_DNS_ADDRESS
#define K15_DEFAULT_DNS_ADDRESS "192.168.1.254"
#endif

#ifndef K15_DEFAULT_SUBNET_MASK
#define K15_DEFAULT_SUBNET_MASK "255.255.255.0"
#endif

#ifndef K15_DEFAULT_GATEWAY
#define K15_DEFAULT_GATEWAY "192.168.1.254"
#endif

#ifndef K15_DEFAULT_SERIAL_OUT
#define K15_DEFAULT_SERIAL_OUT 1
#endif

#ifndef K15_DEFAULT_USE_DHCP
#define K15_DEFAULT_USE_DHCP 0
#endif

#ifndef K15_DEFAULT_HTML_SERVER_PORT
#define K15_DEFAULT_HTML_SERVER_PORT 80
#endif

#ifndef K15_DEFAULT_CSGI_SERVER_PORT
#define K15_DEFAULT_CSGI_SERVER_PORT 3500
#endif

////STATUS PINS
#ifndef K15_SD_ERROR_PIN
#define K15_SD_ERROR_PIN 5
#endif

#ifndef K15_ETHERNET_ERROR_PIN
#define K15_ETHERNET_ERROR_PIN 6
#endif

#ifndef K15_OK_STATUS_PIN
#define K15_OK_STATUS_PIN 7
#endif

////HARDWARE PINS
#ifndef K15_SD_PIN 
#define K15_SD_PIN 4
#endif

#ifndef K15_ETHERNET_PIN
#define K15_ETHERNET_PIN 10
#endif

#ifndef countof
#define countof(x) (sizeof(x) / sizeof(x[0]))
#endif

#ifndef writeToSerial
#define writeToSerial(x) {/*if((config.flagMask & K15_SERIAL_OUT) > 0u)*/ Serial.print(x);}
#endif

typedef enum
{
    K15_INIT_SUCCESS         = 0x01,
    K15_INIT_SD_ERROR        = 0x02,
    K15_INIT_ETHERNET_ERROR  = 0x04,
    K15_SERIAL_OUT           = 0x08,
    K15_USE_DHCP             = 0x10,
    K15_HAS_DNS              = 0x20,
    K15_HAS_GATEWAY          = 0x40,
    K15_HAS_SUBNET_MASK      = 0x80
} kls_flags;

typedef enum
{
    K15_CONFIG_PARSER_STATE_READ_TOKEN   = 0,
    K15_CONFIG_PARSER_STATE_IP_ADDRESS   = 1,
    K15_CONFIG_PARSER_STATE_MAC_ADDRESS  = 2,
    K15_CONFIG_PARSER_STATE_FLAG         = 3,
    K15_CONFIG_PARSER_STATE_PORT         = 4,
    K15_CONFIG_PARSER_STATE_TEXT         = 5
} kls_config_parser_state;

typedef enum
{
    K15_HTML_STATE_READ_METHOD           = 0,
    K15_HTML_STATE_READ_PATH             = 1,
    K15_HTML_STATE_READ_PARAMETERS       = 2,
    K15_HTML_STATE_SKIP_TO_PARAMETERS	= 3,
    K15_HTML_STATE_IGNORE_TOKENS         = 4
} kls_html_request_parser_state;

typedef enum 
{
    K15_HTML_GET_METHOD      = 0,
    K15_HTML_POST_METHOD     = 1,
    K15_HTML_UNKNOWN_METHOD  = 2
} kls_html_request_method;

typedef enum 
{
    K15_HTML_RESPONSE_OK                     = 200,
    K15_HTML_RESPONSE_MOVED_PERMANENTLY      = 301,
    K15_HTML_RESPONSE_FOUND                  = 302,
    K15_HTML_RESPONSE_NOT_MODIFIED	         = 304,
    K15_HTML_RESPONSE_BAD_REQUEST            = 400,
    K15_HTML_RESPONSE_FORBIDDEN	             = 401,
    K15_HTML_RESPONSE_NOT_FOUND              = 404,
    K15_HTML_RESPONSE_INTERNAL_SERVER_ERROR  = 500,
    K15_HTML_RESPONSE_BAD_GATEWAY	         = 502
} kls_html_response_code;

typedef enum 
{
    K15_CSGI_STATE_IGNORE_UNTIL_TOKEN_BEGIN      = 0,
    K15_CSGI_STATE_READ_TOKEN                    = 1,
} kls_csgi_state;

typedef enum 
{
    K15_LED_MODE_OFF             = 0,
    K15_LED_MODE_CONSTANT_COLOR  = 1,
    K15_LED_MODE_PULSE_COLOR     = 2,

    K15_LED_MODE_COUNT
} kls_led_mode;

typedef enum
{
    K15_LED_IDENTIFIER_PLAYER_1	= 0,
    K15_LED_IDENTIFIER_PLAYER_2,
    K15_LED_IDENTIFIER_PLAYER_3,
    K15_LED_IDENTIFIER_PLAYER_4,
    K15_LED_IDENTIFIER_PLAYER_5,
    K15_LED_IDENTIFIER_AMBIENCE_1,
    K15_LED_IDENTIFIER_AMBIENCE_2,

    K15_LED_IDENTIFIER_COUNT 
} kls_led_identifier;

typedef enum 
{
    K15_PLAYER_1_IDENTIFIER = 0x01,
    K15_PLAYER_2_IDENTIFIER = 0x02,
    K15_PLAYER_3_IDENTIFIER = 0x04,
    K15_PLAYER_4_IDENTIFIER = 0x08,
    K15_PLAYER_5_IDENTIFIER = 0x10,

    K15_PLAYER_ALL_IDENTIFIER = K15_PLAYER_1_IDENTIFIER | K15_PLAYER_2_IDENTIFIER |
        K15_PLAYER_3_IDENTIFIER | K15_PLAYER_4_IDENTIFIER | K15_PLAYER_5_IDENTIFIER, 

    K15_PLAYER_IDENTIFIER_COUNT = 5
} kls_player_identifier;

typedef enum 
{
    K15_LED_FLAG_HAS_TARGET_COLOR   = 0x01
} kls_led_flag;

typedef struct 
{
    LiquidCrystal displays[K15_LCD_IDENTIFIER_COUNT];
} kls_lcd_context;

typedef struct 
{
    unsigned long       steamId;
    unsigned long       lastUpdateTimeInMs;
    kls_led_identifier  ledIdentifier;
    char                name[32];
} kls_player_context;

typedef struct 
{
    char                            path[128];
    kls_html_request_parser_state   state;
    kls_html_request_method         method;
    uint8_t                         pathLengthInBytes;
} kls_html_request_parser_context;

typedef struct
{
    byte rgbPins[3];
    byte intensity;
} kls_led_strip;

typedef struct 
{
    LiquidCrystal*  pLCD;
    uint8_t         switchPin;
} kls_lcd;

typedef struct 
{
    uint8_t rsPin;
    uint8_t enablePin;
    uint8_t dbPins[8];
} kls_lcd_pins;

typedef struct 
{
    char                        keyToken[32];
    uint8_t                     textBufferSize;
    kls_config_parser_state     state;
    uint16_t*                   pPort;
    char*                       pText;
    byte*                       pIPAddress;
    byte*                       pMacAddress;
    byte*                       pFlagMask;
    byte                        flag;
} kls_config_parser_context;

typedef struct 
{
    EthernetServer* pServer;
    kls_csgi_state  state;
} kls_csgi_context;

typedef struct 
{
    EthernetServer* pServer;
} kls_html_context;

//FK: Maybe go for RGB565 and store color in uint16_t?
typedef struct 
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} kls_rgb_color;

typedef struct 
{
    uint8_t         flagMask;
    kls_led_mode    mode;

    kls_rgb_color   baseColor;
    kls_rgb_color   color;
    kls_rgb_color   targetColor;
    kls_rgb_color	nextTargetColor;

    unsigned long   fadeTimeMarkerInMs;
    unsigned long   totalFadeTimeInMs;
} kls_led;

typedef struct 
{
    kls_led leds[K15_LED_IDENTIFIER_COUNT];
    unsigned long lastUpdateTimeInMs;
    unsigned long defaultFadeTimeInMs;
} kls_led_context;

typedef struct 
{
    kls_lcd_pins        lcdPins;
    kls_lcd             lcds[8];
    kls_led_strip       ledStrips[8];
    char                username[32];
    char                password[32];
    uint16_t            htmlServerPort;
    uint16_t            csgiServerPort;
    byte                macAddress[6];  
    byte                ipAddress[4];
    byte                dnsAddress[4];
    byte                subnetMask[4];
    byte                gateway[4];  
    byte                flagMask;
} kls_config;

kls_config config;
kls_csgi_context csgiContext;
kls_html_context htmlContext;
kls_led_context ledContext;
kls_player_context playerContexts[K15_PLAYER_IDENTIFIER_COUNT];

void copyByteBuffer(byte* pBufferTo, const byte* pBufferFrom, uint8_t length)
{
    for (uint8_t i = 0; i < length; ++i)
    {
        pBufferTo[i] = pBufferFrom[i];
    }
}

void copyString(char* pTo, const char* pFrom)
{
    while (*pFrom)
    {
        *pTo++ = *pFrom++;
    }

    *pTo = 0;
}

byte asciiDecimalCharToByte(char asciiCharacter)
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

byte isTextAscii( char asciiChar )
{
    return asciiChar >= 'a' && asciiChar <= 'z' || asciiChar >= 'A' && asciiChar <= 'Z';
}

byte asciiHexCharToByte(char hexChar)
{
  if (isDecimalAscii(hexChar))
  {
    return asciiDecimalCharToByte(hexChar);
  }
  
  switch(hexChar)
  {
    case 'a':
    case 'A':
      return 10;

    case 'b':
    case 'B':
      return 11;

    case 'c':
    case 'C':
      return 12;

    case 'd':
    case 'D':
      return 13;

    case 'e':
    case 'E':
      return 14;

    case 'f':
    case 'F':
      return 15;
  }

  return 0;
}

byte hexAsciiDecimalCharToByte(char hexChar)
{
  if (isDecimalAscii(hexChar))
  {
    return asciiDecimalCharToByte(hexChar);
  }
  
  return asciiHexCharToByte(hexChar);
}

byte hexStringToByte(byte* hex, uint8_t length)
{
  if (length == 0)
  {
    return 0;
  }
  else if (length == 1)
  {
    return asciiHexCharToByte(*hex);
  }

  return (asciiHexCharToByte(hex[0]) << 4) | asciiHexCharToByte(hex[1]);
}

uint32_t decimalStringToUint32( const char* pToken, uint8_t length )
{
    if (length == 0)
    {
        return 0;
    }

    if (*pToken == 0)
    {
        return 0;
    }

    uint8_t i = length;
    uint32_t decimal = 0;
    uint32_t multiplier = 1;

    do 
    {
        decimal += (uint32_t)asciiDecimalCharToByte(pToken[--i]) * multiplier;
            multiplier *= 10;
    } while(i > 0);

    return decimal;
}

uint8_t getStringLength(const char* pString)
{
    if (pString == NULL)
    {
        return 0;
    }

    int length = 0u;
    while (*pString++)
    {
        ++length;
    }

    return length;
}

uint8_t tokeniseString(char** pTokenBuffers, uint8_t maxTokenCount, uint8_t tokenBufferSize, const char* pString, char token)
{
    char* pTokenBuffer = *pTokenBuffers;
    uint8_t tokenIndex = 0;
    uint8_t tokenCount = 0;
    while (*pString)
    {
        if (tokenCount == maxTokenCount)
        {
            break;
        }
        
        if (*pString == token || tokenIndex == (tokenBufferSize - 1))
        {
            pTokenBuffer[tokenIndex] = 0;
            pTokenBuffer = *++pTokenBuffers;
            tokenIndex = 0;
            ++tokenCount;
            continue;
        }

        pTokenBuffer[tokenIndex++] = *pString++;
    }

    pTokenBuffer[tokenIndex] = 0;

    return tokenCount;
}

byte isValidLedMode(uint8_t ledMode)
{
    return ledMode < K15_LED_MODE_COUNT;
}

byte isValidLedIndex(uint8_t ledIndex)
{
    return ledIndex < K15_LED_IDENTIFIER_COUNT;
}

byte isValidIpAddressToken( const char* pToken )
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

byte isValidMacAddressToken(const char* pToken)
{
    if (pToken == NULL)
    {
        return 0;
    }

    if (*pToken == 0)
    {
        return 0;
    }

    uint8_t parts = 0;
    uint8_t hexIndex = 0;

    do 
    {
    if (isHexAscii(*pToken))
    {
        if (hexIndex == 2)
        {
            return 0;
        }
        ++hexIndex;
    }
    else if (*pToken == ':' || *pToken == 0)
    {
        if (hexIndex == 0)
        {
            return 0;
        }

        ++parts;
        hexIndex = 0;
    } 
    else
    {
        //FK: invalid character
        return 0;
    }
    } while(*pToken++);

    return (parts == 6);
}

byte isValidPortToken( const char* pToken )
{
    while (*pToken)
    {
        if(!isDecimalAscii(*pToken++))
        {
            return 0;
        }  
    }
    
    return 1;
}

kls_rgb_color uint32ToColor(uint32_t value)
{
    kls_rgb_color color;
    color.r = (value >> 16) & 0xFF;
    color.g = (value >>  8) & 0xFF;
    color.b = (value >>  0) & 0xFF;
    return color;
}

byte tokenToIpAddress( byte* pOutIpAddress, const char* pToken )
{
    uint8_t decimalIndex = 0u;
    char decimal[3u];

  do 
  {
    if( *pToken == '.' || *pToken == 0 ) 
    {
      *pOutIpAddress = (byte)decimalStringToUint32( decimal, decimalIndex );
      pOutIpAddress++;

      decimalIndex = 0;
    }
    else
    {
      if (decimalIndex == sizeof(decimal))
      {
        //FK: prevent overflow
        return 0;
      }

      decimal[decimalIndex++] = *pToken;
    }
  } while (*pToken++ );

    return 1;
}

byte tokenToMacAddress(byte* pOutMacAddress, const char* pToken)
{
    if (!isValidMacAddressToken(pToken))
  {
    return 0;
  }

  uint8_t hexIndex = 0;
  byte hex[2u];

  do 
  {
    if( *pToken == ':' || *pToken == 0 ) 
    {
      *pOutMacAddress = hexStringToByte( hex, hexIndex); 
      pOutMacAddress++;

      hexIndex = 0;
    }
    else
    {
      if (hexIndex == sizeof(hex))
      {
        //FK: prevent overflow
        return 0;
      }

      hex[hexIndex++] = *pToken;
    }
  } while (*pToken++ );

  return 1;
}

byte tokenToBool(byte* pFlagMask, uint8_t bitMask, const char* pToken)
{
    if (pToken[0] == '0')
    {
        *pFlagMask &= ~bitMask;
        return 1;
    }
    else if (pToken[0] == '1')
    {
        *pFlagMask |= bitMask;
        return 1;
    }

    return 0;
}

byte tokenToPort( uint16_t* pOutPort, const char* pToken, uint8_t tokenLength)
{
    if (!isValidPortToken(pToken))
    {
        writeToSerial(F("is no valid port token\n"));
        return 0;
    }

    *pOutPort = decimalStringToUint32(pToken, tokenLength);
    
    return (*pOutPort >= 80);
}

byte stringContains( const char* pStack, const char* pNeedle )
{
    if (pNeedle == NULL || pStack == NULL)
    {
        return 0;
    }

    byte contains = 1;
    const char* pN = pNeedle;

    while(*pStack)
    {
        if ( *pStack == *pNeedle )
        {
            while (*pStack == *pNeedle)
            {
                ++pStack;
                ++pNeedle;

                if (*pNeedle == 0)
                {
                    return 1;
                }
            }

            pNeedle = pN;
        }

        ++pStack;
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

char decimalToAsciiChar(uint8_t decimal)
{
    return decimal + 48;
}

byte isValidPath(const char* pPath, uint8_t pathLength)
{
    if (pPath == NULL)
    {
        return 0;
    }

    if (pathLength == 0)
    {
        return 0;
    }

    int8_t pathDepth = 0;
    uint8_t charIndex = 0u;
    
    do 
    {
        char pathChar = pPath[charIndex];

        if (pathChar == '.' && charIndex > 0u && pPath[charIndex - 1] == '.')
        {
            pathDepth -= 1;
        }
        else if (pathChar == '/' || pathChar == '\\')
        {
            pathDepth += 1;
        }
    } while( ++charIndex < pathLength );

    return pathDepth >= 0;
}

void decimalToAsciiString(uint16_t value, char* pString, uint8_t stringLength)
{
    uint8_t stringIndex = 0;

    while (value != 0)
    {
        const uint8_t i = value % 10;
        value -= i;
        value /= 10;

        pString[stringIndex++] = decimalToAsciiChar(i);

        if (stringIndex == stringLength)
        {
            return;
        }  
    }
}

void enableSlaveSD()
{
    digitalWrite(K15_ETHERNET_ERROR_PIN, HIGH);
    digitalWrite(K15_SD_PIN,             LOW);
}

void enableSlaveEthernet()
{
    digitalWrite(K15_SD_PIN,         HIGH);
    digitalWrite(K15_ETHERNET_PIN,   LOW);
}

void writeCSGIConfig()
{
    SD.remove(K15_CSGI_CONFIG_PATH);
    File configFile = SD.open(K15_CSGI_CONFIG_PATH, O_CREAT | O_WRITE | O_TRUNC);

    if( !configFile )
    {
        writeToSerial(F("Error: Could not create csgi config file '"));
        writeToSerial(K15_CSGI_CONFIG_PATH);
        writeToSerial("'\n");
        return;
    }

    configFile.print(F("\"K15 LED Server v.1\"\n"));
    configFile.print(F("{\n"));
    configFile.print(F("\t\"uri\"\t\"http://"));
   // configFile.print(Ethernet.localIP());
    configFile.print(F(":"));
    configFile.print(config.csgiServerPort);
    configFile.print(F("\"\n"));
    configFile.print(F("\t\"timeout\"\t\"5.0\"\n"));
    configFile.print(F("\t\"throttle\"\t\"0.5\"\n"));
    configFile.print(F("\t\"heartbeat\"\t\"30.0\"\n"));
    configFile.print(F("\t\"data\"\n"));
    configFile.print(F("\t{\n"));
    configFile.print(F("\t\t\"provider\"\t\"1\"\n"));
    configFile.print(F("\t\t\"map\"\t\"1\"\n"));
    configFile.print(F("\t\t\"round\"\t\"1\"\n"));
    configFile.print(F("\t\t\"player_id\"\t\"0\"\n"));
    configFile.print(F("\t\t\"player_state\"\t\"1\"\n"));
    configFile.print(F("\t\t\"player_weapons\"\t\"0\"\n"));
    configFile.print(F("\t\t\"player_match_stats\"\t\"1\"\n"));
    configFile.print(F("\t}\n"));
    configFile.print(F("}\n"));

    configFile.close();
}

void writeDefaultConfigIni()
{
    File configFile = SD.open(K15_CONFIG_PATH, O_CREAT | O_WRITE | O_TRUNC);

    if( !configFile )
    {
        writeToSerial(F("Error: Could not create config file '"));
        writeToSerial(K15_CONFIG_PATH);
        writeToSerial("'\n");
        return;
    }
    
    configFile.print(F("//login data\n"));
    
    configFile.print(F("user="));
    configFile.print(K15_DEFAULT_USER);
    configFile.print(F("\n"));

    configFile.print(F("password="));
    configFile.print(K15_DEFAULT_PASSWORD);
    configFile.print(F("\n\n"));
    
    configFile.print(F("//network\n"));

    configFile.print(F("mac_address="));
    configFile.print(K15_DEFAULT_MAC_ADDRESS);
    configFile.print(F("\n"));

    configFile.print(F("use_dhcp="));
    configFile.print(K15_DEFAULT_USE_DHCP);
    configFile.print(F("\n\n"));

    configFile.print(F("//Only used when 'use_dhcp=0'\n"));

    configFile.print(F("ip4_address="));
    configFile.print(K15_DEFAULT_IP4_ADDRESS);
    configFile.print(F("\n\n"));

    configFile.print(F("//optional\n"));
    configFile.print(F("dns_address="));
    configFile.print(K15_DEFAULT_DNS_ADDRESS);
    configFile.print(F("\n"));

    configFile.print(F("subnet_mask="));
    configFile.print(K15_DEFAULT_SUBNET_MASK);
    configFile.print(F("\n"));
    
    configFile.print(F("gateway="));
    configFile.print(K15_DEFAULT_GATEWAY);
    configFile.print(F("\n\n"));

    configFile.print(F("//server settings\n"));
    configFile.print(F("htmlserver_port="));
    configFile.print(K15_DEFAULT_HTML_SERVER_PORT);
    configFile.print(F("\n"));

    configFile.print(F("csgiserver_port="));
    configFile.print(K15_DEFAULT_CSGI_SERVER_PORT);
    configFile.print(F("\n\n"));

    configFile.print(F("serial_out="));
    configFile.print(K15_DEFAULT_SERIAL_OUT);
    configFile.print(F("\n"));

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
    kls_config_parser_context parserContext;
    parserContext.state = K15_CONFIG_PARSER_STATE_READ_TOKEN;

    byte result = 1;
    uint8_t tokenIndex = 0u;
    char token[32];
    
    File configFile = SD.open(K15_CONFIG_PATH, O_READ);
    while (configFile.peek() != -1)
    {
        byte tokenChar = configFile.read();

        if (tokenChar == '=')
        {
            token[tokenIndex] = 0;

            copyByteBuffer( ( byte* )parserContext.keyToken, ( byte* )token, tokenIndex+1);

            if (stringIsEqual(token, "user"))
            {
                parserContext.state             = K15_CONFIG_PARSER_STATE_TEXT;
                parserContext.pText             = config.username;
                parserContext.textBufferSize    = sizeof(config.username);
            }
            else if (stringIsEqual(token, "password"))
            {
                parserContext.state             = K15_CONFIG_PARSER_STATE_TEXT;
                parserContext.pText             = config.password;
                parserContext.textBufferSize    = sizeof(config.password);
            }
            else if (stringIsEqual(token, "mac_address"))
            {
                parserContext.state         = K15_CONFIG_PARSER_STATE_MAC_ADDRESS;
                parserContext.pMacAddress   = config.macAddress;
            }
            else if (stringIsEqual(token, "ip4_address"))
            {
                parserContext.state         = K15_CONFIG_PARSER_STATE_IP_ADDRESS;
                parserContext.pIPAddress    = config.ipAddress;
            }
            else if (stringIsEqual(token, "dns_address"))
            {
                parserContext.state         = K15_CONFIG_PARSER_STATE_IP_ADDRESS;
                parserContext.pIPAddress    = config.dnsAddress;
            }
            else if (stringIsEqual(token, "subnet_mask"))
            {
                parserContext.state         = K15_CONFIG_PARSER_STATE_IP_ADDRESS;
                parserContext.pIPAddress    = config.subnetMask;
            }
            else if (stringIsEqual(token, "gateway"))
            {
                parserContext.state         = K15_CONFIG_PARSER_STATE_IP_ADDRESS;
                parserContext.pIPAddress    = config.gateway;
            }
            else if (stringIsEqual(token, "htmlserver_port"))
            {
                parserContext.state     = K15_CONFIG_PARSER_STATE_PORT;
                parserContext.pPort     = &config.htmlServerPort;
            }
            else if (stringIsEqual(token, "csgiserver_port"))
            {
                parserContext.state     = K15_CONFIG_PARSER_STATE_PORT;
                parserContext.pPort     = &config.csgiServerPort;
            }
            else if (stringIsEqual(token, "serial_out"))
            {
                parserContext.state     = K15_CONFIG_PARSER_STATE_FLAG;
                parserContext.pFlagMask = &config.flagMask;
                parserContext.flag      = K15_SERIAL_OUT;
            }
            else if (stringIsEqual(token, "use_dhcp"))
            {
                parserContext.state     = K15_CONFIG_PARSER_STATE_FLAG;
                parserContext.pFlagMask = &config.flagMask;
                parserContext.flag      = K15_USE_DHCP;
            }
            else 
            {
                unknownToken:
                writeToSerial(F("Error: Unknown config token '"));
                writeToSerial(token);
                writeToSerial(F("'.\n"));

                parserContext.state = K15_CONFIG_PARSER_STATE_READ_TOKEN;
            }
            
            tokenIndex = 0;
        }
        else if (tokenChar == ' ' || tokenChar == '\t')
        {
            //FK: ignore whitespace
            continue;
        }
        else if (tokenChar == '\n')
        {
            token[tokenIndex] = 0;
            if (parserContext.state == K15_CONFIG_PARSER_STATE_IP_ADDRESS)
            {
                if (!tokenToIpAddress(parserContext.pIPAddress, token))
                {
                    writeToSerial(F("Error: token '"));
                    writeToSerial(parserContext.keyToken);
                    writeToSerial(F("' has invalid value '"));
                    writeToSerial(token);
                    writeToSerial(F("' (valid example: 192.168.1.51).\n"));
                    result = 0;
                    goto cleanUp;
                }
            }
            else if (parserContext.state == K15_CONFIG_PARSER_STATE_MAC_ADDRESS)
            {
                if (!tokenToMacAddress(parserContext.pMacAddress, token))
                {
                    writeToSerial(F("Error: token '"));
                    writeToSerial(parserContext.keyToken);
                    writeToSerial(F("' has invalid value '"));
                    writeToSerial(token);
                    writeToSerial(F("' (valid example: AA:BB:CC:DD:EE:FF).\n"));
                    result = 0;
                    goto cleanUp;
                }
            }
            else if (parserContext.state == K15_CONFIG_PARSER_STATE_FLAG)
            {
                if (!tokenToBool(parserContext.pFlagMask, parserContext.flag, token))
                {
                    writeToSerial(F("Error: token '"));
                    writeToSerial(parserContext.keyToken);
                    writeToSerial(F("' has invalid value '"));
                    writeToSerial(token);
                    writeToSerial(F("' (only valid values are '1' or '0').\n"));
                    result = 0;
                    goto cleanUp;
                }
            }
            else if (parserContext.state == K15_CONFIG_PARSER_STATE_PORT)
            {
                if (!tokenToPort(parserContext.pPort, token, tokenIndex))
                {
                    writeToSerial(F("Error: token '"));
                    writeToSerial(parserContext.keyToken);
                    writeToSerial(F("' has invalid value '"));
                    writeToSerial(token);
                    writeToSerial(F("' (valid value range is 80-65535).\n"));
                    result = 0;
                    goto cleanUp;
                }
            }
            else if (parserContext.state == K15_CONFIG_PARSER_STATE_TEXT)
            {
                if (tokenIndex > parserContext.textBufferSize)
                {
                    writeToSerial(F("Error: token '"));
                    writeToSerial(parserContext.keyToken);
                    writeToSerial(F("' is too long. Max size: "));
                    writeToSerial(parserContext.textBufferSize);
                    writeToSerial(F(".\n"));
                    result = 0;
                    goto cleanUp;
                }

                copyByteBuffer((byte*)parserContext.pText, (byte*)token, tokenIndex+1);
            }

            tokenIndex = 0;
            parserContext.state = K15_CONFIG_PARSER_STATE_READ_TOKEN;
        }
        else
        {
            if ( ( tokenIndex + 1u ) == sizeof( token ) )
            {
                token[tokenIndex] = 0;

                //FK: seek until new line
                seekUntilNewline(&configFile);

                writeToSerial(F("Error: token '"));
                writeToSerial(token);
                writeToSerial(F("is too long (32 character max)\n"));
                tokenIndex = 0u;
                continue;
            }

            token[tokenIndex++] = tokenChar;
        
            if (tokenIndex == 2)
            {
                //FK: Comment - ignore rest of line
                if (token[0] == '/' && token[1] == '/')
                {
                    seekUntilNewline(&configFile);
                    tokenIndex = 0;
                    parserContext.state = K15_CONFIG_PARSER_STATE_READ_TOKEN;
                }
            }
        }
    }

    cleanUp:
      configFile.flush();
      configFile.close();

    return result;
}

void setLEDColor(kls_led_identifier ledId, kls_rgb_color color)
{
    ledContext.leds[ledId].nextTargetColor = color;
    ledContext.leds[ledId].flagMask |= K15_LED_FLAG_HAS_TARGET_COLOR;
}

void setLEDMode(kls_led_identifier ledId, kls_led_mode mode)
{
    ledContext.leds[ledId].mode = mode;
}

void setup()
{
    Serial.begin( 9600 );

    pinMode(PIN_SPI_SCK,         OUTPUT);
    pinMode(PIN_SPI_MOSI,        OUTPUT);
    pinMode(PIN_SPI_SS,          OUTPUT);
    pinMode(PIN_SPI_MISO,        INPUT);

    pinMode(K15_ETHERNET_PIN,    OUTPUT);
    pinMode(K15_SD_PIN,          OUTPUT);

    pinMode(K15_SD_ERROR_PIN,        OUTPUT);
    pinMode(K15_ETHERNET_ERROR_PIN,  OUTPUT);
    pinMode(K15_OK_STATUS_PIN,       OUTPUT);

    digitalWrite(PIN_SPI_SCK,      HIGH);
    digitalWrite(PIN_SPI_MOSI,     HIGH);
    digitalWrite(PIN_SPI_SS,       HIGH);
    digitalWrite(PIN_SPI_MISO,     HIGH);

    digitalWrite(K15_SD_ERROR_PIN,       LOW);
    digitalWrite(K15_ETHERNET_ERROR_PIN, LOW);
    digitalWrite(K15_OK_STATUS_PIN,      LOW);

    enableSlaveSD();

    if( !SD.begin() )
    {
        writeToSerial(F("Could not initialize SD library\n"));
        config.flagMask |= K15_INIT_SD_ERROR;
        return;
    }

    //DEBUG
    SD.remove( K15_CONFIG_PATH );

    if ( !SD.exists( K15_CONFIG_PATH ) )
    {
        writeToSerial(F("Creating default config...\n"));
        writeDefaultConfigIni();
    }

    if ( !parseConfigFile( &config ) )
    {
        config.flagMask |= K15_INIT_SD_ERROR;
        writeToSerial(F("Could not parse config file.\n"));
        return;
    }

    writeCSGIConfig();
    enableSlaveEthernet();

    #if 0
    LiquidCrystal* pLCD = new LiquidCrystal( config.lcdPins.rsPin, config.lcdPins.enablePin, 
        config.lcdPins.dbPins[0], config.lcdPins.dbPins[1], config.lcdPins.dbPins[2],
        config.lcdPins.dbPins[5], config.lcdPins.dbPins[4], config.lcdPins.dbPins[5],
        config.lcdPins.dbPins[6], config.lcdPins.dbPins[7] );

    if (!pLCD)
    {
        writeToSerial("Out of memory.\n");
        return;
    }

    pLCD->begin(16, 2);
    pLCD->print("TEST");
    for (uint8_t ledIndex = 0; ledIndex < countof(config.ledStrips); ++ledIndex)
    {
       // pinMode(config.ledStrips[ledIndex].rgbPins[0], OUTPUT);
        //pinMode(config.ledStrips[ledIndex].rgbPins[1], OUTPUT);
        //pinMode(config.ledStrips[ledIndex].rgbPins[2], OUTPUT);
    }

    for (uint8_t lcdIndex = 0; lcdIndex < countof(config.lcds); ++lcdIndex)
    {
        //config.lcds[lcdIndex].pLCD = pLCD;
        //pinMode(config.lcds[lcdIndex].switchPin, OUTPUT);
    }
    #endif

   

   

    byte hasAddress = 0;
    if ( ( config.flagMask & K15_USE_DHCP ) > 0u )
    {
        writeToSerial(F("Waiting for DHCP...\n"));
        if ( !Ethernet.begin( config.macAddress ) )
        {
            writeToSerial(F("Error: Could not initialize ethernet with DHCP enabled...Trying via IP.\n"));
            config.flagMask &= ~K15_USE_DHCP;
        }
        else
        {
            hasAddress = 1;
        }
    }

    if (!hasAddress)
    {
         IPAddress ipAddress( config.ipAddress[0], config.ipAddress[1], config.ipAddress[2], config.ipAddress[3] );

        if ( ( config.flagMask & K15_HAS_DNS ) == 0u )
        {
            Ethernet.begin(config.macAddress, ipAddress);
        }
        else
        {
            IPAddress dnsAddress( config.dnsAddress[0], config.dnsAddress[1], config.dnsAddress[2], config.dnsAddress[3] );
    
            if ( ( config.flagMask & K15_HAS_GATEWAY ) == 0u )
            {
                Ethernet.begin(config.macAddress, ipAddress, dnsAddress);
            }
            else
            {
                IPAddress gatewayAddress( config.gateway[0], config.gateway[1], config.gateway[2], config.gateway[3] );
    
                if ( ( config.flagMask & K15_HAS_SUBNET_MASK ) == 0 )
                {
                    Ethernet.begin(config.macAddress, ipAddress, dnsAddress, gatewayAddress);
                }
                else
                {
                    IPAddress subnetMask( config.subnetMask[0], config.subnetMask[1], config.subnetMask[2], config.subnetMask[3] );
                    Ethernet.begin(config.macAddress, ipAddress, dnsAddress, gatewayAddress, subnetMask);
                }
            }
        }
    }
   
    writeToSerial(F("Ethernet hardwarestatus="));
    writeToSerial(Ethernet.hardwareStatus());
    writeToSerial("\n");

    writeToSerial(F("Ethernet linkStatus="));
    writeToSerial(Ethernet.linkStatus());
    writeToSerial("\n");

    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        config.flagMask |= K15_INIT_ETHERNET_ERROR;
        writeToSerial(F("Warning: No network hardware has been found.\n"));
        return;
    }

    const EthernetLinkStatus linkStatus = Ethernet.linkStatus();
  
    if (linkStatus != Unknown && linkStatus != LinkON)
    {
        config.flagMask |= K15_INIT_ETHERNET_ERROR;
        writeToSerial(F("Warning: No network cable is plugged in.\n"));
        return;
    }
    
    csgiContext.pServer = new EthernetServer(config.csgiServerPort); 
    csgiContext.state   = K15_CSGI_STATE_READ_TOKEN;

    htmlContext.pServer = new EthernetServer(config.htmlServerPort); 
 
    if (htmlContext.pServer == NULL || csgiContext.pServer == NULL)
    {
        writeToSerial(F("Error: Out of Memory\n"));
        return;
    }

    htmlContext.pServer->begin();
    csgiContext.pServer->begin();

    writeToSerial(Ethernet.localIP());
    writeToSerial("\n");

    config.flagMask |= K15_INIT_SUCCESS;

    digitalWrite(K15_OK_STATUS_PIN, HIGH);
}

const char* getHTMLResponseText(uint16_t htmlResponseCode)
{
    switch(htmlResponseCode)
    {
        case 200:
            return "OK";
        case 301:
            return "MOVED PERMANENTLY";
        case 302:
            return "FOUND";
        case 400:
            return "BAD REQUEST";
        case 401:
            return "UNAUTHORIZED";
        case 404:
            return "NOT FOUND";
        case 500:
            return "INTERNAL SERVER ERROR";
        case 502:
            return "BAD GATEWAY";
        default:
            break;
    }

    return "UNKNOWN";
}

const char* getHTMLContentType(const char* pFilePath, uint8_t filePathLength)
{
    char extension[4];

    if (pFilePath[filePathLength - 3u] == '.')
    {
        extension[0] = pFilePath[filePathLength - 2u];
        extension[1] = pFilePath[filePathLength - 1u];
        extension[2] = 0;
    }
    else 
    {
        extension[0] = pFilePath[filePathLength - 3u];
        extension[1] = pFilePath[filePathLength - 2u];
        extension[2] = pFilePath[filePathLength - 1u];
        extension[3] = 0;
    }

    if (stringIsEqual(extension, "htm"))
    {
        return "text/html";
    }
    else if (stringIsEqual(extension, "css"))
    {
        return "text/css";
    }
    else if (stringIsEqual(extension, "jpg"))
    {
        return "image/jpg";
    }
    else if (stringIsEqual(extension, "png"))
    {
        return "image/png";
    }
    else if (stringIsEqual(extension, "jsn"))
    {
        return "image/json";
    }
    
    return "text/plain";
}

void sendFileToHTMLClient(EthernetClient* pClient, File* pFile)
{
    byte buffer[2048u];

    int16_t bytesRead = 0u;
    do 
    {
        enableSlaveSD();
        bytesRead = pFile->read(buffer, sizeof(buffer));
        enableSlaveEthernet();
        pClient->write(buffer, bytesRead);
    } while(bytesRead == sizeof(buffer));
}

void sendHTMLResponseToClient(EthernetClient* pClient, kls_html_response_code responseCode, const char* pResponseFile, uint8_t responseFileLengthInBytes)
{
    char buffer[256u];
    enableSlaveSD();
    File responseFile = SD.open(pResponseFile);
    const uint32_t responseFileSize = responseFile.size();

    const size_t bytesWritten = sprintf(buffer, "HTTP/1.1 %d %s\r\nConnection: close\r\nContent-Type: %s\r\nContent-Length: %u\r\n\r\n", 
        (uint16_t)responseCode, getHTMLResponseText(responseCode), getHTMLContentType(pResponseFile, responseFileLengthInBytes), responseFileSize );

    enableSlaveEthernet();
    pClient->write(buffer, bytesWritten);

    sendFileToHTMLClient(pClient, &responseFile);
    enableSlaveSD();
    responseFile.close();
    enableSlaveEthernet();
}

void sendHTMLResponseToClient(EthernetClient* pClient, kls_html_response_code responseCode)
{
    char buffer[256u];
    const size_t bytesWritten = sprintf(buffer, "HTTP/1.1 %d %s\r\nConnection: close\r\n", (uint16_t)responseCode, getHTMLResponseText(responseCode));
    pClient->write(buffer, bytesWritten);   
}


void sendHTMLResponseToClient(EthernetClient* pClient, kls_html_response_code responseCode, const char* pResponseFile)
{
    const uint8_t fileNameLength = getStringLength(pResponseFile);

    if (fileNameLength != 0)
    {
        sendHTMLResponseToClient(pClient, responseCode, pResponseFile, fileNameLength); 
    }
    else
    {
        sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_NOT_FOUND);
    }
}

byte parseHTMLRequestMethod(kls_html_request_method* pOutMethod, const char* pRequestMethodString)
{
    if (stringIsEqual(pRequestMethodString, "GET"))
    {
        *pOutMethod = K15_HTML_GET_METHOD;
        return 1;
    }
    else if(stringIsEqual(pRequestMethodString, "POST"))
    {
        *pOutMethod = K15_HTML_POST_METHOD;
        return 1;
    }
    
    writeToSerial("Error: bad html request method: '");
    writeToSerial(pRequestMethodString);
    writeToSerial("'.\n");

    return 0;
}

void handleHTMLPostRequest(EthernetClient* pClient, const char* pPath, uint8_t pathLengthInBytes, const char* pParameters, uint8_t parameterLengthInBytes)
{
    if (stringIsEqual(pPath, "/login"))
    {
        char params[2][64];
        const uint8_t tokenCount = tokeniseString((char**)params, sizeof(params[0]), sizeof(params), pParameters, '&');

        if (tokenCount != 2u)
        {
            sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_BAD_REQUEST);
            return;
        }

        if (!stringIsEqual(params[0], config.username) || !stringIsEqual(params[1], config.password))
        {
            sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_FORBIDDEN);
            return;
        }

        sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_OK, "/admin.htm");
    }
    else if (stringIsEqual(pPath, "/led_mode"))
    {
        char params[2][64];
        const uint8_t tokenCount = tokeniseString((char**)params, sizeof(params[0]), sizeof(params), pParameters, '&');

        if (tokenCount != 2u)
        {
            writeToSerial("Invalid parameter string in POST /led_mode: ");
            writeToSerial(pParameters);
            writeToSerial("\n");
            sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_BAD_REQUEST);
            return;
        }

        const uint16_t ledIndex = decimalStringToUint32(params[0], getStringLength(params[0]));

        if (!isValidLedIndex(ledIndex))
        {
            writeToSerial("Invalid LED Index in POST /led_mode parsing: ");
            writeToSerial(ledIndex);
            writeToSerial("\n");
            sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_BAD_REQUEST);
            return;
        }

        const uint16_t ledMode = decimalStringToUint32(params[1], getStringLength(params[1]));

        if (!isValidLedMode(ledMode))
        {
            writeToSerial("Invalid LED mode in POST /led_mode parsing: ");
            writeToSerial(ledMode);
            writeToSerial("\n");
            sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_BAD_REQUEST);
            return;
        }

        setLEDMode((kls_led_identifier)ledIndex, (kls_led_mode)ledMode);
        sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_OK);
    }
    else if (stringIsEqual(pPath, "/led_color"))
    {
        char params[2][64];
        const uint8_t tokenCount = tokeniseString((char**)params, sizeof(params[0]), sizeof(params), pParameters, '&');

        if (tokenCount != 2u)
        {
            writeToSerial("Invalid parameter string in POST /led_color: ");
            writeToSerial(pParameters);
            writeToSerial("\n");
            sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_BAD_REQUEST);
            return;
        }

        const uint32_t ledIndex = decimalStringToUint32(params[0], getStringLength(params[0]));

        if (!isValidLedIndex(ledIndex))
        {
            writeToSerial("Invalid LED Index in POST /led_color parsing: ");
            writeToSerial(ledIndex);
            writeToSerial("\n");
            sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_BAD_REQUEST);
            return;
        }

        const uint32_t ledColorDecimal = decimalStringToUint32(params[1], getStringLength(params[1]));
        const kls_rgb_color ledColor = uint32ToColor(ledColorDecimal);

        setLEDColor((kls_led_identifier)ledIndex, ledColor);
        sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_OK);
    }
    else
    {
        sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_NOT_FOUND);
    }
}

void handleHTMLGetRequest(EthernetClient* pClient, const char* pPath, uint8_t pathLengthInBytes)
{
    if (!isValidPath(pPath, pathLengthInBytes))
    {
        writeToSerial("Error: Path '");
        writeToSerial(pPath);
        writeToSerial("' is invalid.\n");

        sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_FORBIDDEN);
        return;
    }

    if (stringIsEqual(pPath, "/"))
    {
        const char indexFile[] = "/index.htm\0";
        pPath = indexFile;
        pathLengthInBytes = sizeof(indexFile) - 2;
    }

    //FK: Route SPI to SD
    enableSlaveSD();
    const byte fileExist = SD.exists(pPath);
    enableSlaveEthernet();

    if (!fileExist)
    {
        writeToSerial("Error: File '");
        writeToSerial(pPath);
        writeToSerial("' does not exist.\n");
        
        sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_NOT_FOUND);
        return;
    }
    
    writeToSerial("Sending file '");
    writeToSerial(pPath);
    writeToSerial("' to client...\n");

    sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_OK, pPath, pathLengthInBytes);
}

byte parseHTMLRequestLine(EthernetClient* pClient, kls_html_request_parser_context* pParser, const char* pLine, int16_t lineLengthInBytes)
{
    char token[128];
    uint8_t tokenIndex = 0;

    for (int16_t byteIndex = 0; byteIndex < lineLengthInBytes; ++byteIndex)
    {
        char clientChar = pLine[byteIndex];
        writeToSerial(clientChar);
        token[tokenIndex++] = clientChar;

        if (pParser->state == K15_HTML_STATE_READ_METHOD)
        {
            if (clientChar == ' ' || clientChar == '\n')
            {
                token[tokenIndex-1] = 0;
                if (!parseHTMLRequestMethod(&pParser->method, token))
                {
                    sendHTMLResponseToClient(pClient, K15_HTML_RESPONSE_BAD_REQUEST);     
                    return 1;
                }

                pParser->state = K15_HTML_STATE_READ_PATH;
                tokenIndex = 0;
            }
        }
        else if (pParser->state == K15_HTML_STATE_READ_PATH)
        {
            if (clientChar == ' ' || clientChar == '\n')
            {
                token[tokenIndex-1] = 0;
                copyByteBuffer((byte*)pParser->path, (byte*)token, tokenIndex);
                pParser->pathLengthInBytes = tokenIndex;

                if (pParser->method == K15_HTML_GET_METHOD)
                {
                    handleHTMLGetRequest(pClient, pParser->path, pParser->pathLengthInBytes);
                    return 1;
                }
                else if (pParser->method == K15_HTML_POST_METHOD)
                {
                    pParser->state = K15_HTML_STATE_SKIP_TO_PARAMETERS;
                    tokenIndex = 0;
                }
            }
        }
        else if (pParser->state == K15_HTML_STATE_SKIP_TO_PARAMETERS)
        {
            if (tokenIndex == 1 && token[0] == '\r')
            {
                continue;
            }
            else if (tokenIndex == 2 && token[0] == '\r' && token[1] == '\n')
            {
                pParser->state == K15_HTML_STATE_READ_PARAMETERS;
            }

            tokenIndex = 0;
        }
        else if (pParser->state == K15_HTML_STATE_READ_PARAMETERS)
        {
            if (clientChar == ' ' || clientChar == '\n')
            {
                handleHTMLPostRequest(pClient, pParser->path, pParser->pathLengthInBytes, token, tokenIndex);
                return 1;
            }
        }
    }

    return 0;
}

void handleHTMLClients()
{
    EthernetClient client = htmlContext.pServer->available();

    if (client)
    {
        kls_html_request_parser_context parser;
        parser.state    = K15_HTML_STATE_READ_METHOD;
        parser.method   = K15_HTML_UNKNOWN_METHOD;
    
        char lineBuffer[2048];
        uint8_t tokenIndex = 0u;
        byte requestHandled = 0;

        while (client.connected())
        {
            if (requestHandled)
            {
                break;
            }

            const int16_t bytesAvailable = (int16_t)client.available();
            writeToSerial("bytesAvailable:");
            writeToSerial(bytesAvailable);
            writeToSerial("\n");

            if (bytesAvailable == 0)
            {
                break;
            }

            if (bytesAvailable > (int16_t)sizeof(lineBuffer))
            {
                writeToSerial("Request is too large.\n");
                sendHTMLResponseToClient(&client, K15_HTML_RESPONSE_INTERNAL_SERVER_ERROR);
                break;
            }

            client.read((uint8_t*)lineBuffer, bytesAvailable);
            requestHandled = parseHTMLRequestLine(&client, &parser, lineBuffer, bytesAvailable);
        }

        if (requestHandled == 0)
        {
            sendHTMLResponseToClient(&client, K15_HTML_RESPONSE_INTERNAL_SERVER_ERROR);
        }
    }

    client.stop();
}

void bombExplode()
{
}

void bombPlanted()
{
}

void bombDropped(kls_player_identifier playerIdentifier)
{
    const char* pPlayerName = playerContexts[playerIdentifier].name;

    broadMessage(K15_PLAYER_1_IDENTIFIER)
}

void bombPickedUp()
{
}

void playerConnected(const char* pPlayerName, unsigned long steamId)
{
    const unsigned long nowInMs = millis();
    const uint8_t playerNameLength = getStringLength(pPlayerName);

    for (uint8_t playerIndex = 0u; playerIndex < sizeof(playerContexts); ++playerIndex)
    {
        if (playerContexts[playerIndex].steamId == 0u)
        {
            playerContexts[playerIndex].steamId = steamId;
            copyString(playerContexts[playerIndex].name, pPlayerName);
            return;
        }
    }

    uint8_t oldestPlayerIndex           = (~0);
    unsigned long oldestUpdateTimeInMs  = 0u;
    for (uint8_t playerIndex = 0u; playerIndex < sizeof(playerContexts); ++playerIndex)
    {
        if (playerContexts[playerIndex].lastUpdateTimeInMs > oldestUpdateTimeInMs)
        {
            oldestUpdateTimeInMs = playerContexts[playerIndex].lastUpdateTimeInMs;
            oldestPlayerIndex    = playerIndex;
        }
    }

    if (oldestPlayerIndex < sizeof(playerContexts))
    {
        playerContexts[oldestPlayerIndex].steamId = steamId;
        copyString(playerContexts[oldestPlayerIndex, pPlayerName);
    }

    return;
}

void playerHealthChanged(kls_led_identifier identifier, uint8_t health)
{
    static const kls_rgb_color fullHealth   = {0u, 255u, 0u};
    static const kls_rgb_color noHealth	    = {255u, 0u, 0u};

    kls_rgb_color ledColor = lerpColorValues(&noHealth, &fullHealth, health);
    setLEDColor(identifier, ledColor); 
}

void handleCSGIClients()
{
    EthernetClient client = csgiContext.pServer->available();

    if (client)
    {
        writeToSerial("New CSGI Client.\n");
    }

    char token[32];
    uint8_t tokenIndex = 0u;
    if (client.connected())
    {
        while(client.available())
        {
            char tokenChar = client.read();

            if (csgiContext.state == K15_CSGI_STATE_IGNORE_UNTIL_TOKEN_BEGIN)
            {
                //FK: Eat whitespaces
                if (tokenChar != '"')
                {
                    continue;
                }

                csgiContext.state = K15_CSGI_STATE_READ_TOKEN;
            }
            else if (csgiContext.state == K15_CSGI_STATE_READ_TOKEN)
            {
                if (tokenChar == '"' || tokenChar == ',' || tokenChar == '}')
                {
                    token[tokenIndex] = 0;
                    csgiContext.state = K15_CSGI_STATE_IGNORE_UNTIL_TOKEN_BEGIN;
                    continue;
                }

                token[tokenIndex++] = tokenChar;
            }
        }
    }

    sendHTMLResponseToClient(&client, K15_HTML_RESPONSE_OK);
    client.stop();
}

byte handleError()
{
    const byte hasError = ( ( config.flagMask & K15_INIT_ETHERNET_ERROR ) > 0u ) ||
      ( ( config.flagMask & K15_INIT_SD_ERROR ) > 0u );

    if( hasError != 1 )
    {
        return 0;
    }

    static const unsigned long  errorPulseTimeInMicroSeconds = 600000u;
    static unsigned long        errorPulseTimerInMicroSeconds = 0;
    static unsigned long        lastPulseMicroSeconds = 0;
    static byte                 pinStatus = LOW;
    
    if (lastPulseMicroSeconds == 0)
    {
        lastPulseMicroSeconds = micros();
        return 1;
    }

    const unsigned long currentMicroSeconds = micros();
    const unsigned long deltaInMicroSeconds = (currentMicroSeconds - lastPulseMicroSeconds);
    
    errorPulseTimerInMicroSeconds += deltaInMicroSeconds;

    if( errorPulseTimerInMicroSeconds >= errorPulseTimeInMicroSeconds )
    {
        byte statusPin = 0;
        errorPulseTimerInMicroSeconds = 0;

        if( ( config.flagMask & K15_INIT_SD_ERROR ) > 0u )
        {
            statusPin = K15_SD_ERROR_PIN;
        }
        else if( ( config.flagMask & K15_INIT_ETHERNET_ERROR ) > 0u )
        {
            statusPin = K15_ETHERNET_ERROR_PIN;
        }

        pinStatus = !pinStatus;
        digitalWrite(statusPin, pinStatus);
    }

    lastPulseMicroSeconds = currentMicroSeconds;

    return 1;
}

kls_rgb_color lerpColorValues(const kls_rgb_color* pFrom, const kls_rgb_color* pTo, uint8_t lerpFactor)
{
    //FK: lerpFactor [0,100]

    kls_rgb_color color;

    color.r = uint8_t(((uint16_t)pFrom->r * (100 - lerpFactor) + (uint16_t)pTo->r * lerpFactor) / 100);
    color.g = uint8_t(((uint16_t)pFrom->g * (100 - lerpFactor) + (uint16_t)pTo->g * lerpFactor) / 100);
    color.b = uint8_t(((uint16_t)pFrom->b * (100 - lerpFactor) + (uint16_t)pTo->b * lerpFactor) / 100);

    return color;
}

void updateLEDColor()
{
    const unsigned long nowInMs = millis();
    const unsigned long thenInMs = ledContext.lastUpdateTimeInMs; 
    const unsigned long deltaInMs = thenInMs - nowInMs;

    for(uint8_t ledIndex = 0u; ledIndex < K15_LED_IDENTIFIER_COUNT; ++ledIndex)
    {
        kls_led* pLED = ledContext.leds + ledIndex;
        if (pLED->fadeTimeMarkerInMs > 0u)
        {
            if (pLED->fadeTimeMarkerInMs < deltaInMs)
            {
                pLED->fadeTimeMarkerInMs = 0u;
                pLED->color = pLED->targetColor;
                continue;
            }

            const uint8_t lerp = (pLED->fadeTimeMarkerInMs * 100) / pLED->totalFadeTimeInMs;
            pLED->color = lerpColorValues(&pLED->baseColor, &pLED->targetColor, lerp);
            pLED->fadeTimeMarkerInMs -= deltaInMs;
        }
        else if ((pLED->flagMask & K15_LED_FLAG_HAS_TARGET_COLOR) > 0u)
        {
            pLED->baseColor = pLED->color;
            pLED->targetColor = pLED->nextTargetColor;
            pLED->fadeTimeMarkerInMs = ledContext.defaultFadeTimeInMs;
            pLED->totalFadeTimeInMs = ledContext.defaultFadeTimeInMs;
            pLED->flagMask &= ~K15_LED_FLAG_HAS_TARGET_COLOR;
        }
    }

    ledContext.lastUpdateTimeInMs = nowInMs;
}

void loop()
{
    if( handleError() )
    {
      return;
    }
    
    const unsigned long startMicros = millis();

    handleHTMLClients();
    handleCSGIClients();
    updateLEDColor();

    const unsigned long endMicros = millis();
    const unsigned long deltaMillis = endMicros - startMicros;
}
