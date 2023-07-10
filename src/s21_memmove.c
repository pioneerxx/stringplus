#include "s21_string.h"

void *s21_memmove(void *first_string, const void *second_string,
                  s21_size_t valume) {
  char *destination = (char *)first_string;
  const char *source = (const char *)second_string;
  static char temp[1000] = {'\0'};
  int i = 0;
  int q = valume;
  while ((q--) && (source + i)) {
    temp[i] = source[i];
    i++;
  }
  i = 0;
  q = valume;
  while ((q--) && (destination + i)) {
    destination[i] = temp[i];
    i++;
  }
  return destination;
}
