#include "s21_string.h"

long int s21_atoi(const char *str) {
  int res = 0;
  int sign = 1;
  int overflow = 0;

  while (*str == ' ') str++;

  if (*str == '-') {
    str++;
    sign = -1;
  }

  if (*str == '+') {
    str++;
  }

  while (*str && *str >= '0' && *str <= '9') {
    res = res * 10 + (*str - '0');
    if (res < 0) {
      overflow = 1;
      break;
    }
    str++;
  }
  if (overflow)
    res = sign > 0 ? 2147483647 : -2147483647 - 1;
  else
    res *= sign;

  return res;
}