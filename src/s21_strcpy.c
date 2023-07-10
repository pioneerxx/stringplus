#include "s21_string.h"

char *s21_strcpy(char *first_string, const char *second_string) {
  for (int i = 0; 1; i++) {
    first_string[i] = second_string[i];
    if (first_string[i] == '\0') {
      break;
    }
  }
  return first_string;
}
