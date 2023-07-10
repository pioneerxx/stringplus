#include "s21_string.h"

void *s21_trim(const char *string, const char *trim_chars) {
  int pointer = 0;
  int first_count = s21_strlen(string);
  int second_count = s21_strlen(trim_chars);
  static char intermediate_string[1000] = {'\0'};
  for (int i = 0; i < first_count; i++) {
    if (string[i] == trim_chars[i] && i < second_count) {
      continue;
    } else {
      intermediate_string[pointer] = string[i];
      pointer++;
    }
  }
  static char result_string[1000] = {'\0'};
  first_count = s21_strlen(intermediate_string);
  int j = 0;
  int skip_flag = 0;
  int second_pointer = 0;
  for (int i = 0; i < first_count; i++) {
    if (i == first_count - second_count) {
      skip_flag = 1;
    }
    if (skip_flag == 1) {
      if (intermediate_string[i] == trim_chars[j]) {
        j++;
        continue;
      }
    }
    result_string[second_pointer] = intermediate_string[i];
    second_pointer++;
  }
  char *result = result_string;
  return (void *)result;
}
