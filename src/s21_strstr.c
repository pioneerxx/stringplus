#include "s21_string.h"

char *s21_strstr(const char *first_string, const char *second_string) {
  int count = 0, pointer = 0;
  int end_cycle = 0, result_valume = 0;
  int first_valume = s21_strlen(first_string);
  int second_valume = s21_strlen(second_string);
  for (int i = 0; i < first_valume && end_cycle != 1; i++) {
    count = 0;
    if (first_string[i] == second_string[0]) {
      int k = 0;
      for (int j = i; j < second_valume + i; j++) {
        if (first_string[j] == second_string[k]) {
          count++;
        } else if (first_string[j] != second_string[k] &&
                   count != second_valume) {
          break;
        }
        k++;
      }
    }
    if (count == second_valume) {
      end_cycle = 1;
      pointer = i;
    }
  }
  result_valume = first_valume - pointer;
  static char string[1000] = {'\0'};
  for (int j = 0; j < result_valume; j++) {
    string[j] = first_string[pointer];
    pointer++;
  }
  char *result = string;
  if (count != second_valume) {
    result = s21_NULL;
  }
  return result;
}
