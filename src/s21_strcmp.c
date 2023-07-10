#include "s21_string.h"

int s21_strcmp(const char *first_string, const char *second_string) {
  int first_string_count = 0;
  int second_string_count = 0;
  int result = 0;
  for (int i = 0; 1; i++) {
    if (first_string[i] == '\0') {
      break;
    }
    first_string_count += first_string[i];
  }
  for (int i = 0; 1; i++) {
    if (second_string[i] == '\0') {
      break;
    }
    second_string_count += second_string[i];
  }
  result = first_string_count - second_string_count;
  return result;
}
