#include <SD.h>
#include <Ethernet.h>
#include <LiquidCrystal.h>

#ifndef K15_LED_SERVER_CONFIG_PATH
#define K15_LED_SERVER_CONFIG_PATH "config.ini"
#endif

#ifndef K15_LED_SERVER_DEFAULT_USER
#define K15_LED_SERVER_DEFAULT_USER "admin"
#endif

#ifndef K15_LED_SERVER_DEFAULT_PASSWORD
#define K15_LED_SERVER_DEFAULT_PASSWORD "1234"
#endif

#ifndef K15_LED_SERVER_DEFAULT_MAC_ADDRESS
#define K15_LED_SERVER_DEFAULT_MAC_ADDRESS "7E:D5:E6:4E:6D:8C"
#endif

#ifndef K15_LED_SERVER_DEFAULT_IP4_ADDRESS
#define K15_LED_SERVER_DEFAULT_IP4_ADDRESS "192.168.1.51"
#endif

#ifndef K15_LED_SERVER_DEFAULT_DNS_ADDRESS
#define K15_LED_SERVER_DEFAULT_DNS_ADDRESS "192.168.1.1"
#endif

#ifndef K15_LED_SERVER_DEFAULT_SUBNET_MASK
#define K15_LED_SERVER_DEFAULT_SUBNET_MASK "255.255.255.0"
#endif

#ifndef K15_LED_SERVER_DEFAULT_GATEWAY
#define K15_LED_SERVER_DEFAULT_GATEWAY "192.168.1.1"
#endif

#ifndef K15_LED_SERVER_DEFAULT_SERIAL_OUT
#define K15_LED_SERVER_DEFAULT_SERIAL_OUT 1
#endif

#ifndef K15_LED_SERVER_DEFAULT_USE_DHCP
#define K15_LED_SERVER_DEFAULT_USE_DHCP 0
#endif

#ifndef K15_LED_SERVER_DEFAULT_HTML_SERVER_PORT
#define K15_LED_SERVER_DEFAULT_HTML_SERVER_PORT 80
#endif

#ifndef K15_LED_SERVER_DEFAULT_CSGI_SERVER_PORT
#define K15_LED_SERVER_DEFAULT_CSGI_SERVER_PORT 3500
#endif

////RGB PINS////
#ifndef K15_LED_SERVER_DEFAULT_LED_R0_PIN
#define K15_LED_SERVER_DEFAULT_LED_R0_PIN 1
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_G0_PIN
#define K15_LED_SERVER_DEFAULT_LED_G0_PIN 2
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_B0_PIN
#define K15_LED_SERVER_DEFAULT_LED_B0_PIN 3
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_R1_PIN
#define K15_LED_SERVER_DEFAULT_LED_R1_PIN 4
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_G1_PIN
#define K15_LED_SERVER_DEFAULT_LED_G1_PIN 5
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_B1_PIN
#define K15_LED_SERVER_DEFAULT_LED_B1_PIN 6
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_R2_PIN
#define K15_LED_SERVER_DEFAULT_LED_R2_PIN 7
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_G2_PIN
#define K15_LED_SERVER_DEFAULT_LED_G2_PIN 8
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_B2_PIN
#define K15_LED_SERVER_DEFAULT_LED_B2_PIN 9
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_R3_PIN
#define K15_LED_SERVER_DEFAULT_LED_R3_PIN 10
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_G3_PIN
#define K15_LED_SERVER_DEFAULT_LED_G3_PIN 11
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_B3_PIN
#define K15_LED_SERVER_DEFAULT_LED_B3_PIN 12
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_R4_PIN
#define K15_LED_SERVER_DEFAULT_LED_R4_PIN 13
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_G4_PIN
#define K15_LED_SERVER_DEFAULT_LED_G4_PIN 14
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_B4_PIN
#define K15_LED_SERVER_DEFAULT_LED_B4_PIN 15
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_R5_PIN
#define K15_LED_SERVER_DEFAULT_LED_R5_PIN 16
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_G5_PIN
#define K15_LED_SERVER_DEFAULT_LED_G5_PIN 17
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_B5_PIN
#define K15_LED_SERVER_DEFAULT_LED_B5_PIN 18
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_R6_PIN
#define K15_LED_SERVER_DEFAULT_LED_R6_PIN 19
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_G6_PIN
#define K15_LED_SERVER_DEFAULT_LED_G6_PIN 20
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_B6_PIN
#define K15_LED_SERVER_DEFAULT_LED_B6_PIN 21
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_R7_PIN
#define K15_LED_SERVER_DEFAULT_LED_R7_PIN 22
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_G7_PIN
#define K15_LED_SERVER_DEFAULT_LED_G7_PIN 23
#endif

#ifndef K15_LED_SERVER_DEFAULT_LED_B7_PIN
#define K15_LED_SERVER_DEFAULT_LED_B7_PIN 24
#endif

////LCD PINS
#ifndef K15_LED_SERVER_DEFAULT_LCD_DB0_PIN 
#define K15_LED_SERVER_DEFAULT_LCD_DB0_PIN 30
#endif

#ifndef K15_LED_SERVER_DEFAULT_lcd_db_pin_1 
#define K15_LED_SERVER_DEFAULT_lcd_db_pin_1 31
#endif

#ifndef K15_LED_SERVER_DEFAULT_lcd_db_pin_2 
#define K15_LED_SERVER_DEFAULT_lcd_db_pin_2 32
#endif

#ifndef K15_LED_SERVER_DEFAULT_lcd_db_pin_3 
#define K15_LED_SERVER_DEFAULT_lcd_db_pin_3 33
#endif

#ifndef K15_LED_SERVER_DEFAULT_lcd_db_pin_4 
#define K15_LED_SERVER_DEFAULT_lcd_db_pin_4 34
#endif

#ifndef K15_LED_SERVER_DEFAULT_lcd_db_pin_5 
#define K15_LED_SERVER_DEFAULT_lcd_db_pin_5 35
#endif

#ifndef K15_LED_SERVER_DEFAULT_lcd_db_pin_6 
#define K15_LED_SERVER_DEFAULT_lcd_db_pin_6 36
#endif

#ifndef K15_LED_SERVER_DEFAULT_lcd_db_pin_7 
#define K15_LED_SERVER_DEFAULT_lcd_db_pin_7 37
#endif

#ifndef K15_LED_SERVER_DEFAULT_LCD_ENABLE_PIN
#define K15_LED_SERVER_DEFAULT_LCD_ENABLE_PIN 38
#endif

#ifndef K15_LED_SERVER_DEFAULT_LCD_RS_PIN 
#define K15_LED_SERVER_DEFAULT_LCD_RS_PIN 39
#endif


////LCD SWITCH PINS
#ifndef K15_LED_SERVER_DEFAULT_LCD_SWITCH_0_PIN
#define K15_LED_SERVER_DEFAULT_LCD_SWITCH_0_PIN 42
#endif

#ifndef K15_LED_SERVER_DEFAULT_LCD_SWITCH_1_PIN
#define K15_LED_SERVER_DEFAULT_LCD_SWITCH_1_PIN 43
#endif

#ifndef K15_LED_SERVER_DEFAULT_LCD_SWITCH_2_PIN
#define K15_LED_SERVER_DEFAULT_LCD_SWITCH_2_PIN 44
#endif

#ifndef K15_LED_SERVER_DEFAULT_LCD_SWITCH_3_PIN
#define K15_LED_SERVER_DEFAULT_LCD_SWITCH_3_PIN 45
#endif

#ifndef K15_LED_SERVER_DEFAULT_LCD_SWITCH_4_PIN
#define K15_LED_SERVER_DEFAULT_LCD_SWITCH_4_PIN 46
#endif

#ifndef K15_LED_SERVER_DEFAULT_LCD_SWITCH_5_PIN
#define K15_LED_SERVER_DEFAULT_LCD_SWITCH_5_PIN 47
#endif

#ifndef K15_LED_SERVER_DEFAULT_LCD_SWITCH_6_PIN
#define K15_LED_SERVER_DEFAULT_LCD_SWITCH_6_PIN 48
#endif

#ifndef K15_LED_SERVER_DEFAULT_LCD_SWITCH_7_PIN
#define K15_LED_SERVER_DEFAULT_LCD_SWITCH_7_PIN 49
#endif

#ifndef countof
#define countof(x) (sizeof(x) / sizeof(x[0]))
#endif

#ifndef writeToSerial
#define writeToSerial(x) {/*if((config.flagMask & K15_LED_SERVER_SERIAL_OUT) > 0u)*/ Serial.print(x);}
#endif

typedef enum
{
    K15_LED_SERVER_INIT_SUCCESS     = 0x01,
    K15_LED_SERVER_SERIAL_OUT       = 0x02,
    K15_LED_SERVER_USE_DHCP         = 0x04,
    K15_LED_SERVER_HAS_DNS		    = 0x08,
    K15_LED_SERVER_HAS_GATEWAY	    = 0x10,
    K15_LED_SERVER_HAS_SUBNET_MASK  = 0x20
} kls_flags;

typedef enum
{
    K15_LED_SERVER_CONFIG_PARSER_STATE_READ_TOKEN   = 0,
    K15_LED_SERVER_CONFIG_PARSER_STATE_IP_ADDRESS   = 1,
    K15_LED_SERVER_CONFIG_PARSER_STATE_MAC_ADDRESS  = 2,
    K15_LED_SERVER_CONFIG_PARSER_STATE_FLAG	        = 3,
    K15_LED_SERVER_CONFIG_PARSER_STATE_PIN	        = 4,
    K15_LED_SERVER_CONFIG_PARSER_STATE_LED_RGB_PINS	= 5,
    K15_LED_SERVER_CONFIG_PARSER_STATE_PORT	        = 6,
    K15_LED_SERVER_CONFIG_PARSER_STATE_TEXT	        = 7
} kls_config_parser_state;

typedef enum 
{
    K15_LED_SERVER_CSGI_STATE_IGNORE_UNTIL_TOKEN_BEGIN      = 0,
    K15_LED_SERVER_CSGI_STATE_READ_TOKEN                     = 1
} kls_csgi_state;

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
    byte*                       pRGBPins;
    byte*                       pIPAddress;
    byte*                       pMacAddress;
    byte*                       pPin;
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
    EthernetServer* pHTMLServer;
    kls_lcd_pins    lcdPins;
    kls_lcd         lcds[8];
    kls_led_strip   ledStrips[8];
    char            username[32];
    char            password[32];
    uint16_t        htmlServerPort;
    uint16_t        csgiServerPort;
    byte            macAddress[6];  
    byte            ipAddress[4];
    byte            dnsAddress[4];
    byte            subnetMask[4];
    byte            gateway[4];  
    byte            flagMask;
} kls_config;

kls_config config;
kls_csgi_context csgiContext;

void copyByteBuffer(byte* pBufferTo, const byte* pBufferFrom, uint8_t length)
{
    for (uint8_t i = 0; i < length; ++i)
    {
        pBufferTo[i] = pBufferFrom[i];
    }
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

uint16_t decimalStringToUint16( const char* pToken, uint8_t length )
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
	uint16_t decimal = 0;
    uint16_t multiplier = 1;

	do 
	{
    	decimal += (uint16_t)asciiDecimalCharToByte(pToken[--i]) * multiplier;
        multiplier *= 10;
	} while(i > 0);

    return decimal;
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

byte tokenToIpAddress( byte* pOutIpAddress, const char* pToken )
{
    uint8_t decimalIndex = 0u;
    char decimal[3u];

	do 
	{
		if( *pToken == '.' || *pToken == 0 ) 
		{
			*pOutIpAddress = (byte)decimalStringToUint16( decimal, decimalIndex );
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

byte tokenToPin(uint8_t* pOutPin, const char* pToken, uint8_t tokenLength)
{
    *pOutPin = (byte)decimalStringToUint16(pToken, tokenLength);
    return 1;
}

byte tokenToRGBPins(uint8_t* pOutPins, const char* pToken)
{
    if (*pToken++ != '[')
    {
        return 0;
    }

    uint8_t pinCount = 0;

    while(*pToken)
    {
        //FK: eat symbols
        while (*pToken == ' ' || *pToken == '\t' || *pToken == ',' || *pToken == ']')
        {
            ++pToken;

            if (*pToken == 0)
            {
                return 1;
            }
        }

        uint8_t pinTokenLength = 0;
        const char* pPinToken = pToken;

        while (*pToken != ',' && *pToken != ']')
        {
            if (*pToken == 0)
            {
                return 0;
            }

            if (!isDecimalAscii(*pToken++))
            {
                continue;
            }

            pinTokenLength++;
        }

        ++pinCount;
        *pOutPins++ = (byte)decimalStringToUint16(pPinToken, pinTokenLength);
        pinTokenLength = 0;
    }
    
    return pinCount == 3;
}

byte tokenToPort( uint16_t* pOutPort, const char* pToken, uint8_t tokenLength)
{
    if (!isValidPortToken(pToken))
    {
        writeToSerial("is no valid port token\n");
        return 0;
    }

    *pOutPort = decimalStringToUint16(pToken, tokenLength);
    
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
    
    configFile.print("//login data\n");
    
    configFile.print("user=");
    configFile.print(K15_LED_SERVER_DEFAULT_USER);
    configFile.print("\n");

    configFile.print("password=");
    configFile.print(K15_LED_SERVER_DEFAULT_PASSWORD);
    configFile.print("\n\n");

    configFile.print("//network\n");

    configFile.print("mac_address=");
    configFile.print(K15_LED_SERVER_DEFAULT_MAC_ADDRESS);
    configFile.print("\n");

    configFile.print("serial_out=");
    configFile.print(K15_LED_SERVER_DEFAULT_SERIAL_OUT);
    configFile.print("\n");

    configFile.print("use_dhcp=");
    configFile.print(K15_LED_SERVER_DEFAULT_USE_DHCP);
    configFile.print("\n\n");

    configFile.print("//Only used when 'use_dhcp=0'\n");

    configFile.print("ip4_address=");
    configFile.print(K15_LED_SERVER_DEFAULT_IP4_ADDRESS);
    configFile.print("\n");

    configFile.print("dns_address=");
    configFile.print(K15_LED_SERVER_DEFAULT_DNS_ADDRESS);
    configFile.print("\n");

    configFile.print("subnet_mask=");
    configFile.print(K15_LED_SERVER_DEFAULT_SUBNET_MASK);
    configFile.print("\n");
    
    configFile.print("gateway=");
    configFile.print(K15_LED_SERVER_DEFAULT_GATEWAY);
    configFile.print("\n\n");

    configFile.print("//server settings\n");

    configFile.print("htmlserver_port=");
    configFile.print(K15_LED_SERVER_DEFAULT_HTML_SERVER_PORT);
    configFile.print("\n");

    configFile.print("csgiserver_port=");
    configFile.print(K15_LED_SERVER_DEFAULT_CSGI_SERVER_PORT);
    configFile.print("\n\n");

    configFile.print("//lcd settings\n");

    configFile.print("lcd_db_pin_0=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_DB0_PIN);
    configFile.print("\n");

    configFile.print("lcd_db_pin_1=");
    configFile.print(K15_LED_SERVER_DEFAULT_lcd_db_pin_1);
    configFile.print("\n");

    configFile.print("lcd_db_pin_2=");
    configFile.print(K15_LED_SERVER_DEFAULT_lcd_db_pin_2);
    configFile.print("\n");

    configFile.print("lcd_db_pin_3=");
    configFile.print(K15_LED_SERVER_DEFAULT_lcd_db_pin_3);
    configFile.print("\n");

    configFile.print("lcd_db_pin_4=");
    configFile.print(K15_LED_SERVER_DEFAULT_lcd_db_pin_4);
    configFile.print("\n");

    configFile.print("lcd_db_pin_5=");
    configFile.print(K15_LED_SERVER_DEFAULT_lcd_db_pin_5);
    configFile.print("\n");

    configFile.print("lcd_db_pin_6=");
    configFile.print(K15_LED_SERVER_DEFAULT_lcd_db_pin_6);
    configFile.print("\n");

    configFile.print("lcd_db_pin_7=");
    configFile.print(K15_LED_SERVER_DEFAULT_lcd_db_pin_7);
    configFile.print("\n");

    configFile.print("lcd_rs_pin=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_RS_PIN);
    configFile.print("\n");

    configFile.print("lcd_enable_pin=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_ENABLE_PIN);
    configFile.print("\n\n");

    configFile.print("//lcd switch settings\n");

    configFile.print("lcd_switch_pin_0=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_SWITCH_0_PIN);
    configFile.print("\n");

    configFile.print("lcd_switch_pin_1=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_SWITCH_1_PIN);
    configFile.print("\n");

    configFile.print("lcd_switch_pin_2=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_SWITCH_2_PIN);
    configFile.print("\n");

    configFile.print("lcd_switch_pin_3=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_SWITCH_3_PIN);
    configFile.print("\n");

    configFile.print("lcd_switch_pin_4=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_SWITCH_4_PIN);
    configFile.print("\n");

    configFile.print("lcd_switch_pin_5=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_SWITCH_5_PIN);
    configFile.print("\n");

    configFile.print("lcd_switch_pin_6=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_SWITCH_6_PIN);
    configFile.print("\n");

    configFile.print("lcd_switch_pin_7=");
    configFile.print(K15_LED_SERVER_DEFAULT_LCD_SWITCH_7_PIN);
    configFile.print("\n\n");

    configFile.print("//led rgb strip settings\n");
  
    configFile.print("led_strip_rgb_pins_0=[");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_R0_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_G0_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_B0_PIN);
    configFile.print("]\n");

    configFile.print("led_strip_rgb_pins_1=[");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_R1_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_G1_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_B1_PIN);
    configFile.print("]\n");

    configFile.print("led_strip_rgb_pins_2=[");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_R2_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_G2_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_B2_PIN);
    configFile.print("]\n");

    configFile.print("led_strip_rgb_pins_3=[");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_R3_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_G3_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_B3_PIN);
    configFile.print("]\n");

    configFile.print("led_strip_rgb_pins_4=[");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_R4_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_G4_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_B4_PIN);
    configFile.print("]\n");

    configFile.print("led_strip_rgb_pins_5=[");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_R5_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_G5_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_B5_PIN);
    configFile.print("]\n");

    configFile.print("led_strip_rgb_pins_6=[");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_R6_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_G6_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_B6_PIN);
    configFile.print("]\n");

    configFile.print("led_strip_rgb_pins_7=[");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_R7_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_G7_PIN);
    configFile.print(", ");
    configFile.print(K15_LED_SERVER_DEFAULT_LED_B7_PIN);
    configFile.print("]\n");

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
    parserContext.state = K15_LED_SERVER_CONFIG_PARSER_STATE_READ_TOKEN;

    uint8_t tokenIndex = 0u;
    char token[32];
    
    File configFile = SD.open(K15_LED_SERVER_CONFIG_PATH, FILE_READ);
    while (configFile.peek() != -1)
    {
        byte tokenChar = configFile.read();

        if (tokenChar == '=')
        {
            token[tokenIndex] = 0;

            copyByteBuffer( ( byte* )parserContext.keyToken, ( byte* )token, tokenIndex+1);

            if (stringIsEqual(token, "user"))
            {
                parserContext.state	            = K15_LED_SERVER_CONFIG_PARSER_STATE_TEXT;
                parserContext.pText             = config.username;
                parserContext.textBufferSize    = sizeof(config.username);
            }
            else if (stringIsEqual(token, "password"))
            {
                parserContext.state	            = K15_LED_SERVER_CONFIG_PARSER_STATE_TEXT;
                parserContext.pText             = config.password;
                parserContext.textBufferSize    = sizeof(config.password);
            }
            else if (stringIsEqual(token, "mac_address"))
            {
                parserContext.state         = K15_LED_SERVER_CONFIG_PARSER_STATE_MAC_ADDRESS;
                parserContext.pMacAddress   = config.macAddress;
            }
            else if (stringIsEqual(token, "ip4_address"))
            {
                parserContext.state         = K15_LED_SERVER_CONFIG_PARSER_STATE_IP_ADDRESS;
                parserContext.pIPAddress    = config.ipAddress;
            }
            else if (stringIsEqual(token, "dns_address"))
            {
                parserContext.state         = K15_LED_SERVER_CONFIG_PARSER_STATE_IP_ADDRESS;
                parserContext.pIPAddress    = config.dnsAddress;
            }
            else if (stringIsEqual(token, "subnet_mask"))
            {
                parserContext.state         = K15_LED_SERVER_CONFIG_PARSER_STATE_IP_ADDRESS;
                parserContext.pIPAddress    = config.subnetMask;
            }
            else if (stringIsEqual(token, "gateway"))
            {
                parserContext.state         = K15_LED_SERVER_CONFIG_PARSER_STATE_IP_ADDRESS;
                parserContext.pIPAddress    = config.gateway;
            }
            else if (stringIsEqual(token, "htmlserver_port"))
            {
                parserContext.state     = K15_LED_SERVER_CONFIG_PARSER_STATE_PORT;
                parserContext.pPort     = &config.htmlServerPort;
            }
            else if (stringIsEqual(token, "csgiserver_port"))
            {
                parserContext.state     = K15_LED_SERVER_CONFIG_PARSER_STATE_PORT;
                parserContext.pPort     = &config.csgiServerPort;
            }
            else if (stringIsEqual(token, "serial_out"))
            {
                parserContext.state     = K15_LED_SERVER_CONFIG_PARSER_STATE_FLAG;
                parserContext.pFlagMask = &config.flagMask;
                parserContext.flag      = K15_LED_SERVER_SERIAL_OUT;
            }
            else if (stringIsEqual(token, "use_dhcp"))
            {
                parserContext.state     = K15_LED_SERVER_CONFIG_PARSER_STATE_FLAG;
                parserContext.pFlagMask = &config.flagMask;
                parserContext.flag      = K15_LED_SERVER_USE_DHCP;
            }
            else if (stringIsEqual(token, "lcd_enable_pin"))
            {
                parserContext.state = K15_LED_SERVER_CONFIG_PARSER_STATE_PIN;
                parserContext.pPin  = &config.lcdPins.enablePin;
            }
            else if (stringIsEqual(token, "lcd_rs_pin"))
            {
                parserContext.state = K15_LED_SERVER_CONFIG_PARSER_STATE_PIN;
                parserContext.pPin  = &config.lcdPins.rsPin;
            }
            else if (stringContains(token, "lcd_db_pin_"))
            {
                if (!isDecimalAscii(token[11]) && token[12] != 0)
                {
                    goto unknownToken;
                }

                const uint8_t pinIndex = asciiDecimalCharToByte(token[11]);
                parserContext.state = K15_LED_SERVER_CONFIG_PARSER_STATE_PIN;
                parserContext.pPin  = &config.lcdPins.dbPins[pinIndex];
            }
            else if (stringContains(token, "lcd_switch_pin_"))
            {
                if (!isDecimalAscii(token[15]) && token[16] != 0)
                {
                    goto unknownToken;
                }

                const uint8_t lcdIndex = asciiDecimalCharToByte(token[15]);
                parserContext.state = K15_LED_SERVER_CONFIG_PARSER_STATE_PIN;
                parserContext.pPin  = &config.lcds[lcdIndex].switchPin;
            }
            else if (stringContains(token, "led_strip_rgb_pins_"))
            {
                if (!isDecimalAscii(token[19]) && token[20] != 0)
                {
                    goto unknownToken;
                }

                const uint8_t ledIndex  = asciiDecimalCharToByte(token[19]);
                parserContext.state     = K15_LED_SERVER_CONFIG_PARSER_STATE_LED_RGB_PINS;
                parserContext.pRGBPins  = config.ledStrips[ledIndex].rgbPins;
            }
            else 
            {
                unknownToken:
                writeToSerial("Error: Unknown config token '");
                writeToSerial(token);
                writeToSerial("'.\n");

                parserContext.state = K15_LED_SERVER_CONFIG_PARSER_STATE_READ_TOKEN;
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
            if (parserContext.state == K15_LED_SERVER_CONFIG_PARSER_STATE_IP_ADDRESS)
            {
                if (!tokenToIpAddress(parserContext.pIPAddress, token))
                {
                    writeToSerial("Error: token '");
                    writeToSerial(parserContext.keyToken);
                    writeToSerial("' has invalid value '");
                    writeToSerial(token);
                    writeToSerial("' (valid example: 192.168.1.51).\n");
                    return 0;
                }
            }
            else if (parserContext.state == K15_LED_SERVER_CONFIG_PARSER_STATE_MAC_ADDRESS)
            {
                if (!tokenToMacAddress(parserContext.pMacAddress, token))
                {
                    writeToSerial("Error: token '");
                    writeToSerial(parserContext.keyToken);
                    writeToSerial("' has invalid value '");
                    writeToSerial(token);
                    writeToSerial("' (valid example: AA:BB:CC:DD:EE:FF).\n");
                    return 0;
                }
            }
            else if (parserContext.state == K15_LED_SERVER_CONFIG_PARSER_STATE_FLAG)
            {
                if (!tokenToBool(parserContext.pFlagMask, parserContext.flag, token))
                {
                    writeToSerial("Error: token '");
                    writeToSerial(parserContext.keyToken);
                    writeToSerial("' has invalid value '");
                    writeToSerial(token);
                    writeToSerial("' (only valid values are '1' or '0').\n");
                    return 0;
                }
            }
            else if (parserContext.state == K15_LED_SERVER_CONFIG_PARSER_STATE_PIN)
            {
                if (!tokenToPin(parserContext.pPin, token, tokenIndex))
                {
                    writeToSerial("Error: token '");
                    writeToSerial(parserContext.keyToken);
                    writeToSerial("' has invalid value '");
                    writeToSerial(token);
                    writeToSerial("' (only valid values are valid pin identifier).\n");
                    return 0;
                }
            }
            else if (parserContext.state == K15_LED_SERVER_CONFIG_PARSER_STATE_LED_RGB_PINS)
            {
                if (!tokenToRGBPins(parserContext.pRGBPins, token))
                {
                    writeToSerial("Error: token '");
                    writeToSerial(parserContext.keyToken);
                    writeToSerial("' has invalid value '");
                    writeToSerial(token);
                    writeToSerial("' (only valid values are valid pin identifier in a tuple like '[1, 3, 4]).\n");
                    return 0;
                }
            }
            else if (parserContext.state == K15_LED_SERVER_CONFIG_PARSER_STATE_PORT)
            {
                if (!tokenToPort(parserContext.pPort, token, tokenIndex))
                {
                    writeToSerial("Error: token '");
                    writeToSerial(parserContext.keyToken);
                    writeToSerial("' has invalid value '");
                    writeToSerial(token);
                    writeToSerial("' (valid value range is 80-65535).\n");
                    return 0;
                }
            }
            else if (parserContext.state == K15_LED_SERVER_CONFIG_PARSER_STATE_TEXT)
            {
                if (tokenIndex > parserContext.textBufferSize)
                {
                    writeToSerial("Error: token '");
                    writeToSerial(parserContext.keyToken);
                    writeToSerial("' is too long. Max size: ");
                    writeToSerial(parserContext.textBufferSize);
                    writeToSerial(".\n");
                    return 0;
                }

                copyByteBuffer((byte*)parserContext.pText, (byte*)token, tokenIndex+1);
            }

            tokenIndex = 0;
            parserContext.state = K15_LED_SERVER_CONFIG_PARSER_STATE_READ_TOKEN;
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
        
            if (tokenIndex == 2)
            {
                //FK: Comment - ignore rest of line
                if (token[0] == '/' && token[1] == '/')
                {
                    seekUntilNewline(&configFile);
                    tokenIndex = 0;
                    parserContext.state = K15_LED_SERVER_CONFIG_PARSER_STATE_READ_TOKEN;
                }
            }
        }
    }

    return 1;
}

void setup()
{
    Serial.begin( 9600 );
    
    if( !SD.begin() )
    {
        writeToSerial("Could not initialize SD library\n");
        
        //FK: TODO: blink red LED
        return;
    }

    //debug
    SD.remove( K15_LED_SERVER_CONFIG_PATH );

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

    for (uint8_t ledIndex = 0; ledIndex < countof(config.ledStrips); ++ledIndex)
    {
        pinMode(config.ledStrips[ledIndex].rgbPins[0], OUTPUT);
        pinMode(config.ledStrips[ledIndex].rgbPins[1], OUTPUT);
        pinMode(config.ledStrips[ledIndex].rgbPins[2], OUTPUT);
    }

    for (uint8_t lcdIndex = 0; lcdIndex < countof(config.lcds); ++lcdIndex)
    {
        config.lcds[lcdIndex].pLCD = pLCD;
        pinMode(config.lcds[lcdIndex].switchPin, OUTPUT);
    }

    byte hasAddress = 0;
    if ( ( config.flagMask & K15_LED_SERVER_USE_DHCP ) > 0u )
    {
        if ( !Ethernet.begin( config.macAddress ) )
        {
            writeToSerial("Error: Could not initialize ethernet with DHCP enabled...Trying via IP.\n");
            config.flagMask &= ~K15_LED_SERVER_USE_DHCP;
        }
        else
        {
            hasAddress = 1;
        }
    }

    if (hasAddress)
    {
        return;
    }

    IPAddress ipAddress( config.ipAddress[0], config.ipAddress[1], config.ipAddress[2], config.ipAddress[3] );

    if ( ( config.flagMask & K15_LED_SERVER_HAS_DNS ) == 0u )
    {
        Ethernet.begin(config.macAddress, ipAddress);
    }
    else
    {
        IPAddress dnsAddress( config.dnsAddress[0], config.dnsAddress[1], config.dnsAddress[2], config.dnsAddress[3] );

        if ( ( config.flagMask & K15_LED_SERVER_HAS_GATEWAY ) == 0u )
        {
            Ethernet.begin(config.macAddress, ipAddress, dnsAddress);
        }
        else
        {
            IPAddress gatewayAddress( config.gateway[0], config.gateway[1], config.gateway[2], config.gateway[3] );

            if ( ( config.flagMask & K15_LED_SERVER_HAS_SUBNET_MASK ) == 0 )
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

    Serial.print("Ethernet hardwarestatus=");
    Serial.print(Ethernet.hardwareStatus());
    Serial.print("\n");

    Serial.print("Ethernet linkStatus=");
    Serial.print(Ethernet.linkStatus());
    Serial.print("\n");

    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        writeToSerial("Warning: No network hardware has been found.\n");
        return;
    }

    if (Ethernet.linkStatus() != LinkON)
    {
        writeToSerial("Warning: No network cable is plugged in.\n");
        //return;
    }

    csgiContext.pServer = new EthernetServer(config.csgiServerPort); 
    csgiContext.state   = K15_LED_SERVER_CSGI_STATE_READ_TOKEN;

    config.pHTMLServer = new EthernetServer(config.htmlServerPort);

    if (config.pHTMLServer == NULL || csgiContext.pServer == NULL)
    {
        writeToSerial("Error: Out of Memory\n");
        return;
    }

    config.pHTMLServer->begin();
    csgiContext.pServer->begin();

    config.flagMask |= K15_LED_SERVER_INIT_SUCCESS;
}

void send200ResponseToClient(EthernetClient* pClient)
{
}

void handleHTMLClients()
{
    EthernetClient client = config.pHTMLServer->available();

    if (client)
    {
        writeToSerial("New HTML Client.");
    }

    //FK: TODO: Read GET and decide what page the user wants (?)
}

void handleCSGIClients()
{
    EthernetClient client = csgiContext.pServer->available();

    if (client)
    {
        writeToSerial("New CSGI Client.");
    }

    char token[32];
    uint8_t tokenIndex = 0u;
    if (client.connected())
    {
        while(client.available())
        {
            char tokenChar = client.read();

            if (csgiContext.state == K15_LED_SERVER_CSGI_STATE_IGNORE_UNTIL_TOKEN_BEGIN)
            {
                //FK: Eat whitespaces
                if (tokenChar != '"')
                {
                    continue;
                }

                csgiContext.state = K15_LED_SERVER_CSGI_STATE_READ_TOKEN;
            }
            else if (csgiContext.state == K15_LED_SERVER_CSGI_STATE_READ_TOKEN)
            {
                if (tokenChar == '"' || tokenChar == ',' || tokenChar == '}')
                {
                    token[tokenIndex] = 0;
                    csgiContext.state = K15_LED_SERVER_CSGI_STATE_IGNORE_UNTIL_TOKEN_BEGIN;
                    continue;
                }

                token[tokenIndex++] = tokenChar;
            }
        }
    }

    send200ResponseToClient(&client);

    client.stop();
}

void loop()
{
    if( ( config.flagMask & K15_LED_SERVER_INIT_SUCCESS ) == 0)
    {
        delay( 1000 );
        return;
    }

    const unsigned long startMicros = millis();

    handleHTMLClients();
    handleCSGIClients();

    const unsigned long endMicros = millis();
    const unsigned long deltaMillis = endMicros - startMicros;

    Serial.println(deltaMillis);
}
