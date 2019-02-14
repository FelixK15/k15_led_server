#ifndef _K15_WIN32_ETHERNET_H_
#define _K15_WIN32_ETHERNET_H_

struct IPAddress
{
    IPAddress(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
    {

    }
};

enum EthernetHardwareStatus
{
    EthernetNoHardware = 0,
};

enum EthernetLinkStatus
{
    Unknown = 0,
    LinkON
};

struct EthernetImpl
{
    uint8_t begin( const byte* pMacAddress )
    {
        return 1;
    }

    uint8_t begin( const byte* pMacAddress, IPAddress ipAddress)
    {
        return 1;
    }

    uint8_t begin( const byte* pMacAddress, IPAddress ipAddress, IPAddress dnsAddress )
    {
        return 1;
    }

    uint8_t begin( const byte* pMacAddress, IPAddress ipAddress, IPAddress dnsAddress, IPAddress gatewayAddress )
    {
        return 1;
    }

    uint8_t begin( const byte* pMacAddress, IPAddress ipAddress, IPAddress dnsAddress, IPAddress gatewayAddress, IPAddress subnetMask )
    {
        return 1;
    }

    EthernetHardwareStatus hardwareStatus()
    {
        return EthernetNoHardware;
    }

    EthernetLinkStatus linkStatus()
    {
        return LinkON;
    }

    IPAddress localIP()
    {
        return IPAddress(127,0,0,1);
    }
};

static EthernetImpl Ethernet;

struct EthernetClient
{
    uint8_t connected()
    {
        return 1;
    }

    uint8_t available()
    {
        return 1;
    }

    char read()
    {  
        return 1;
    }

    int read(void* pBuffer, int16_t bufferSizeInBytes)
    {
        return 0;
    }

    void write(void* pBuffer, size_t byteCountInBuffer)
    {
        
    }

    void stop()
    {

    }

    operator bool() const
    {
        return true;
    }
};

struct EthernetServer
{
    EthernetServer(int port)
    {

    }

    void begin()
    {

    }

    EthernetClient available()
    {
        return EthernetClient();
    }
};

#endif 