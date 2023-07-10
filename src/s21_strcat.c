#include "s21_string.h"

char *s21_strcat(char *first_string, const char *second_string) {
  int count = 0;
  for (int i = 0; 1; i++) {
    if (first_string[i] == '\0') {
      break;
    }
    count++;
  }
  int j = 0;
  for (int i = count; 1; i++) {
    if (second_string[j] == '\0') {
      break;
    }
    first_string[i] = second_string[j];
    j++;
  }
  return first_string;
}
