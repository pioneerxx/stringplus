#include "s21_string.h"

char *s21_strncpy(char *first_string, const char *second_string,
                  s21_size_t valume) {
  int valume_copy = valume;
  for (int i = 0; i < valume_copy; i++) {
    first_string[i] = second_string[i];
  }
  return first_string;
}
