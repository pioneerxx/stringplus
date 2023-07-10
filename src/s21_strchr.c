#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int counter = 0, fl = 0;
  char *res = s21_NULL;
  while (*(str + counter)) {
    if (*(str + counter) == (char)c) {
      res = (char *)(str + counter);
      fl = 1;
      break;
    }
    counter++;
  }
  if (*(str + counter) == c && !fl) res = (char *)(str + counter);
  return res;
}