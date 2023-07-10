#include "s21_string.h"

char *s21_strpbrk(const char *first_string, const char *second_string) {
  int switch_flag = 0, count = 0, pointer = 0;
  for (int j = 0; first_string[j] != '\0'; j++) {
    for (int i = 0; 1; i++) {
      if (second_string[i] == '\0') {
        break;
      }
      if (first_string[j] == second_string[i] && switch_flag == 0) {
        switch_flag = 1;
        pointer = j;
        break;
      }
    }
    if (switch_flag == 1) {
      count++;
    }
  }
  static char string[1000] = {'\0'};
  for (int k = 0; k < count; k++) {
    string[k] = first_string[pointer];
    pointer++;
  }
  char *result = string;
  if (string[0] == '\0') {
    result = s21_NULL;
  }
  return result;
}
