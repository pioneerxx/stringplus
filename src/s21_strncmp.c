#include "s21_string.h"

int s21_strncmp(const char *first_string, const char *second_string,
                s21_size_t valume) {
  int status = 0;
  int valume_copy = valume;
  for (int i = 0; i < valume_copy; i++) {
    status += first_string[i] - second_string[i];
  }
  return status;
}
