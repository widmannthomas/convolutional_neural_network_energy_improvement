#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#include "../base/dataprovider/dataproviderserial.h"
#include "../base/dataprovider/dataconverter.h"

int main(int argc, char *argv[])
{
  stdio_init_all();

  IDataProvider* pDataProvider = new DataProviderSerial();
  DataConverter<float> oConverter;
  char arrBuffer[100];

  while(true)
  {
      pDataProvider->fetchData(arrBuffer, 16);
      float* pFloatData = oConverter.fromByteStream(arrBuffer, 16);

      printf("Successfully received data. f: %f, %f, %f, %f", pFloatData[0], pFloatData[1], pFloatData[2], pFloatData[3]);
  }
}
