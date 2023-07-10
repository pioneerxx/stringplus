#include "s21_string.h"

void *s21_memset(void *string, int search_symbol, s21_size_t valume) {
  unsigned char *str = (unsigned char *)string;
  int int_valume = valume;
  for (int i = 0; i < int_valume; i++) {
    str[i] = search_symbol;
  }
  return (void *)str;
}
