#include "uart_helper.h"

#include <stdio.h>
#include "pico/stdlib.h"

void uart_read_line(char *szBuffer, unsigned int unSize)
{
    unsigned int i = 0;
    int d = 0;

    for (;;)
    {
        d = getchar_timeout_us(0);
        if (d == PICO_ERROR_TIMEOUT)
        {
            continue;
        }

        szBuffer[i] = d;
        i++;

        //printf(">%c<", d);

        if (d == '\n' || i >= unSize - 1)
        {
            szBuffer[i] = '\0';
            //printf("done: %s", szBuffer);
            break;
        }
    }
}