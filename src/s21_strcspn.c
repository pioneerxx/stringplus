#include "s21_string.h"

s21_size_t s21_strcspn(const char *first_string, const char *search_string) {
  int count = 0, switch_flag = 0;
  for (int i = 0; first_string[i] != '\0'; i++) {
    for (int j = 0; search_string[j] != '\0'; j++) {
      if (first_string[i] == search_string[j]) {
        switch_flag = 1;
        break;
      }
    }
    if (switch_flag == 0) {
      count++;
    } else {
      break;
    }
  }
  return count;
}
