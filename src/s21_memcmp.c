#include "s21_string.h"

int s21_memcmp(const void *first_string, const void *second_string,
               s21_size_t valume) {
  unsigned char *ar1 = (unsigned char *)first_string;
  unsigned char *ar2 = (unsigned char *)second_string;
  int res = 0;
  while ((ar1) && (ar2) && (valume--)) {
    if (*ar1 != *ar2) {
      res = *ar1 - *ar2;
      break;
    }
    ar1++;
    ar2++;
  }
  return res;
}
