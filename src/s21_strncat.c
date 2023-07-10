#include "s21_string.h"

char *s21_strncat(char *first_string, const char *second_string,
                  s21_size_t valume) {
  int count = 0;
  for (int i = 0; 1; i++) {
    if (first_string[i] == '\0') {
      break;
    }
    count++;
  }
  int j = 0;
  int valume_copy = valume;
  for (int i = count; j < valume_copy; i++) {
    first_string[i] = second_string[j];
    j++;
  }
  return first_string;
}
