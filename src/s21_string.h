#ifndef S21_STRING
#define S21_STRING

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int s21_size_t;

typedef struct flags {
  char typeflag;
  int leftflag;
  int signflag;
  int spaceflag;
  int isprecision;
  int issharp;
  int fillzero;
} printflags;

typedef struct flagsScan {
  char typeflag;
  int iswidth;
  int width;
} scanflags;

#define s21_NULL ((void *)0)
#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0

void *s21_memchr(const void *string, int search_symbol, s21_size_t valume);
int s21_memcmp(const void *first_string, const void *second_string,
               s21_size_t valume);
void *s21_memcpy(void *first_string, const void *second_string,
                 s21_size_t valume);
void *s21_memmove(void *first_string, const void *second_string,
                  s21_size_t valume);
void *s21_memset(void *string, int search_symbol, s21_size_t valume);

char *s21_strcat(char *first_string, const char *second_string);
char *s21_strncat(char *first_string, const char *second_string,
                  s21_size_t valume);
char *s21_strchr(const char *search_string, int search_symbol);
int s21_strcmp(const char *first_string, const char *second_string);
int s21_strncmp(const char *first_string, const char *second_string,
                s21_size_t valume);
char *s21_strcpy(char *first_string, const char *second_string);
char *s21_strncpy(char *first_string, const char *second_string,
                  s21_size_t valume);
s21_size_t s21_strcspn(const char *first_string, const char *search_string);
char *s21_strerror(int error_number);
s21_size_t s21_strlen(const char *string);
char *s21_strpbrk(const char *first_string, const char *second_string);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *first_string, const char *second_string);
char *s21_strstr(const char *first_string, const char *second_string);
char *s21_strtok(char *str, const char *separator);

void *s21_to_upper(const char *string);
void *s21_to_lower(const char *string);
void *s21_insert(const char *first_string, const char *second_string,
                 s21_size_t start_index);
void *s21_trim(const char *string, const char *trim_chars);

long int s21_atoi(const char *str);

void convertNonDecimal(char *value, long int n, int base, int isUP,
                       printflags flags, int precision, int isshort,
                       int isaddress, int size);
void convert(char *value, long int n, printflags flags, int precision,
             int size);
void convertString(char *value1, char *str, int precision, printflags flags);
void roundFloats(char *ptr, char ending, int isE);
void noTrailing(char *value, int isE);
void convertMantiss(char *value, long double n, int precision, printflags flags,
                    int isUP, int size);
void convertFloat(char *value, long double n, int precision, printflags flags,
                  int size);
void specG(char *value, long double n, int precision, printflags flags,
           int isUP, int size);
void convertChar(char *value, int n);
int s21_sprintf(char *str, const char *format, ...);

void skipFunc(const char *str, int *pos, const char *format, int *format_i,
              int *end);
void smartConvertScan(long int *n, const char *str, int *pos, int numberSpec,
                      int *end, char specifier, int *counter);
void convertDecimalScan(long long int *n, const char *str, int *pos,
                        int numberSpec, int *counter, int *end);
void convertCharScan(char *n, const char *str, int *pos, const char *format,
                     int format_i);
void convertStringScan(char *aboba, const char *str, int *pos, scanflags flags,
                       int *counter);
int convertFloatScan(long double *n, const char *str, int *pos, int *counter);
void convertMantissScan(long double *n, const char *str, int *pos,
                        int minusFlag, int expFlag, int negativeNumber);
int convertUnsignedInt(unsigned long int *n, const char *str, int *pos);
int s21_sscanf(const char *str, const char *format, ...);

#endif  // S21_STRING
