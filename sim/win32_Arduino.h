#ifndef _K15_WIN32_ARDUINO_H_
#define _K15_WIN32_ARDUINO_H_

#include <stdio.h>
#include <stdint.h>

typedef uint8_t byte;

#define F(x) x

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0

#define PIN_SPI_SCK     0
#define PIN_SPI_MOSI	1
#define PIN_SPI_SS      2
#define PIN_SPI_MISO    3

struct SerialImpl
{
    void begin(int r)
    {
        (void)r;
    }

    void print(const char* pString)
    {
        printf(pString);
    }

    void print(uint32_t value)
    {
        printf("%u", value);
    }
};

static SerialImpl Serial;

void pinMode(int pin, int mode)
{

}

void digitalWrite(int pin, int value)
{

}

unsigned long millis()
{
    return 0;
}

unsigned long micros()
{
    return 0;
}

extern void setup();
extern void loop();

int main(int argc, char** argv)
{
    setup();

    while(1)
    {
        loop();
    }
}

#endif