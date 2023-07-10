#include "s21_string.h"

char *s21_strrchr(const char *search_string, int search_symbol) {
  int pointer = 0;
  int switch_flag = 0;
  int valume = s21_strlen(search_string);
  for (int i = 0; i < valume; i++) {
    if (search_string[i] == search_symbol) {
      pointer = i;
      switch_flag = 1;
    }
  }
  char *result = (char *)search_string;
  if (switch_flag == 0) {
    result = s21_NULL;
  } else {
    result += pointer;
  }
  return result;
}
