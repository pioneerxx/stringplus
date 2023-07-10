#include "s21_string.h"

void *s21_memchr(const void *string, int search_symbol, s21_size_t valume) {
  unsigned char *ar = (unsigned char *)string;
  unsigned char *foundChar = s21_NULL;
  while ((ar != s21_NULL) && (valume--)) {
    if (*ar != search_symbol) {
      ar++;
    } else {
      foundChar = ar;
      break;
    }
  }
  return foundChar;
}
