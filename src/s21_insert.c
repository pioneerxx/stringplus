#include "s21_string.h"

void *s21_insert(const char *first_string, const char *second_string,
                 s21_size_t start_index) {
  static char string[1000] = {'\0'};
  int index = (int)start_index;
  char *result = &string[0];
  if (first_string != s21_NULL && second_string != s21_NULL) {
    int first_len = s21_strlen(first_string);
    int second_len = s21_strlen(second_string);
    if (first_string != s21_NULL && index <= first_len) {
      if (second_string == s21_NULL) {
        if (result != s21_NULL) s21_strcpy(result, first_string);
      } else {
        if (result != s21_NULL) {
          s21_strncpy(result, first_string, start_index);
          result = result + start_index;
          first_string = first_string + start_index;
          s21_strcpy(result, second_string);
          result = result + second_len;
          s21_strcpy(result, first_string);
          result = result - second_len - start_index;
        }
      }
    }
    if (index > first_len) {
      result = s21_NULL;
    }
  } else {
    result = s21_NULL;
  }
  return (void *)result;
}
