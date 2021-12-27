#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

int main(int argc, char *argv[])
{
  stdio_init_all();

  while(true)
  {
      sleep_ms(1000);

      absolute_time_t time = get_absolute_time();

      printf("time: %lld\n", time);
  }
}
