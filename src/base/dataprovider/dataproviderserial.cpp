#include "dataproviderserial.h"

#include <stdio.h>
#include "pico/stdio.h"
#include "pico/stdlib.h"

void DataProviderSerial::fetchData(uint8_t* pData, unsigned int unSize)
{
    unsigned int unReceived = 0; 
    int nBuffer = 0;

    for(; unReceived < unSize; unReceived++)
    {
        while((nBuffer = getchar_timeout_us(0)) == PICO_ERROR_TIMEOUT) { }

        pData[unReceived] = nBuffer;
    }
}