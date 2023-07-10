#include "s21_string.h"

s21_size_t s21_strspn(const char *first_string, const char *second_string) {
  int switch_flag = 0, count = 0;
  int first_valume = s21_strlen(first_string);
  int second_valume = s21_strlen(second_string);
  for (int i = 0; i < first_valume; i++) {
    switch_flag = 0;
    for (int j = 0; j < second_valume; j++) {
      if (first_string[i] == second_string[j]) {
        switch_flag = 1;
        count = i;
      }
    }
    if (switch_flag == 0) {
      break;
    }
  }
  if (switch_flag == 0 && count != 0) {
    count++;
  }
  return count;
}
