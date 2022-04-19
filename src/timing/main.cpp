#include <stdio.h>
#include <string>
#include "pico/stdlib.h"

float multiply_float(float a, float b)
{
  return a * b;
}

double multiply_double(double a, double b)
{
  const double c = a * b;
  return c;
}

bool float_check_zero(float a)
{
  return a == 0.;
}

bool float_check_zero_int(float a)
{
  return *(int*)&a == 0.;
}

bool float_check_zero_fast(float a)
{
  return *(char*)&a == 0;
}

bool char_check_zero(char a)
{
  return a == 0;
}

void print_binary(float f, int i)
{
    printf("%f: 0b", f);
    int n = *(float*)&f;
    int k;
    for (k = i - 1; k >= 0; k--) 
    {
        printf((n >> k) & 1 ? "1" : "0");
    }
    printf("\n");
}

std::string to_bin_string(int n, unsigned short len)
{
    std::string binary;
    for (unsigned short i = (1 << len - 1); i > 0; i = i / 2) {
        binary += (n & i) ? "1" : "0";
    }
 
    return binary;
}

std::string to_bin_string(float f)
{
    std::string binary;
    const int n = *(int*)&f;
    const unsigned short len = 32;
    for (unsigned i = (1 << len - 1); i > 0; i = i / 2) {
        binary += (n & i) ? "1" : "0";
    }
 
    return binary;
}

std::string to_bin_string_(float f)
{
    std::string binary;
    const int n = *(int*)&f;
    const unsigned short len = 32;
    for (unsigned i = 1; i < (1 << len - 1); i = i * 2) {
        binary += (n & i) ? "1" : "0";
    }
 
    return binary;
}

std::string to_bin_string_(int n, unsigned short len)
{
    std::string binary;
    for (unsigned i = 1; i < (1 << len); i = i * 2) {
        binary += (n & i) ? "1" : "0";
    }
 
    return binary;
}

bool float_check_exponent_not_zero_log(float f)
{
  printf("Bin: %s\n", to_bin_string_(f).data());
  short* p = (short*)&f;
  p++;
  short c = *p;
  printf("First two bytes: %s\n", to_bin_string_(c, 8).data());
  c = c << 1;

  char* pe = (char*)&c;
  pe++;
  char e = *pe;
  printf("Exponent: %s\n", to_bin_string_(e, 8).data());
  return e == 0;
}

bool float_check_exponent_not_zero(float f)
{
  short* p = (short*)&f;
  p++;
  short c = *p;
  c = c << 1;

  char* pe = (char*)&c;
  pe++;
  char e = *pe;
  return e != 0;
}

int main(int argc, char *argv[])
{
  stdio_init_all();

  float f = -0.00000152;

  for(;;)
  {
    printf("1: %d\n", float_check_exponent_not_zero(f));      // 1
    printf("2: %d\n", float_check_exponent_not_zero(0));      // 0
    printf("3: %d\n", float_check_exponent_not_zero(1e-37));  // 1
    printf("4: %d\n", float_check_exponent_not_zero(1e-38));  // 0
    sleep_ms(1000);
  }

  multiply_float((float)*argv[1], (float)*argv[2]);
  multiply_double((float)*argv[1], (float)*argv[2]);

  float_check_zero((float)*argv[1]);
  float_check_zero_fast((float)*argv[1]);
  char_check_zero(*argv[1]);
}
