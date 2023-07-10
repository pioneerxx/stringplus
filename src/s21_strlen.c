#include "s21_string.h"

s21_size_t s21_strlen(const char *string) {
  int count = 0;
  while (string[count] != '\0') {
    count++;
  }
  return count;
}
