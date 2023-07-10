#include "s21_string.h"

void *s21_memcpy(void *first_string, const void *second_string,
                 s21_size_t valume) {
  unsigned char *destination = (unsigned char *)first_string;
  unsigned char *source = (unsigned char *)second_string;
  int int_valume = valume;
  for (int i = 0; i < int_valume; i++) {
    destination[i] = source[i];
  }
  return destination;
}
