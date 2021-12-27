#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#include "../base/communication/communicationhandler.h"

int main(int argc, char *argv[])
{
    stdio_init_all();

    printf("Start...\n");

    CommunicationHandler oHandler;

    Command oCommand;
    oHandler.waitForCommand(oCommand);

    printf("Received command!\n");

    while(true){};
}
