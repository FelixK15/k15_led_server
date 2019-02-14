#ifndef _K15_WIN32_SD_H_
#define _K15_WIN32_SD_H_

#define O_CREAT 0x01
#define O_WRITE 0x02
#define O_TRUNC 0x04
#define O_READ  0x08

struct File
{
    size_t size()
    {
        return 0u;
    }

    uint8_t peek()
    {
        return 0;
    }

    uint8_t read()
    {
        return 0;
    }

    uint16_t read(const void* pBuffer, size_t bufferSizeInBytes)
    {  
        return 0;
    }

    void flush()
    {

    }

    void close()
    {

    }

    void print(int value)
    {

    }

    void print(const char* pString)
    {

    }

    bool operator!() const
    {
        return true;
    }
};

struct SDImpl
{
    uint8_t begin()
    {
        return 1;
    }

    void remove(const char* pPath)
    {

    }

    uint8_t exists(const char* pPath)
    {
        return 1;
    }

    File open(const char* pPath, uint32_t mode)
    {
        return File();
    }

    File open(const char* pPath)
    {
        return File();
    }
};

static SDImpl SD;

#endif