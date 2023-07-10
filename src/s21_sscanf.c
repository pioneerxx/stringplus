#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list arg;
  int counter = 0;
  int str_i = 0;
  int format_i = 0;
  int end = 0;
  int parameters = 0;
  int *num = 0;
  void **ptr = s21_NULL;
  char *symbol = '\0';
  char *stringSymbols = '\0';
  unsigned short int *numUnsignedShortInt = 0;
  unsigned int *numUnsignedInt = 0;
  unsigned long int *numUnsignedLongInt = 0;
  short int *numShort = 0;
  long int *numLong = 0;
  float *numFloat = 0;
  double *numDouble = 0;
  long double *numLongDouble = 0;
  int count = 0;
  va_start(arg, format);
  while (format[format_i] != '\0') {
    if (format[format_i] != '%' && format[format_i] != ' ') {
      if (format[format_i] == str[str_i]) {
        for (int i = format_i; format[i] == str[str_i] &&
                               (format[i] != '%' && format[format_i] != ' ');
             i++) {
          str_i++;
          format_i++;
          count++;
          if (format[format_i] != str[str_i] && (format[format_i] != '%')) {
            format_i = s21_strlen(format);
          }
        }
      } else {
        format_i++;
      }
      continue;
    } else if (format[format_i] != '%' && format[format_i] == ' ') {
      if (format[format_i] == str[str_i]) {
        for (int i = format_i; format[i] == str[str_i] && format[i] != '%';
             i++) {
          str_i++;
          format_i++;
          count++;
        }
      } else {
        format_i++;
      }
      continue;
    } else {
      scanflags flagsScan = {0, 0, 0};
      format_i++;
      if ((format[format_i] >= '0' && format[format_i] <= '9') ||
          format[format_i] == '*') {
        flagsScan.iswidth = 1;
        char width[10];
        int widthsize = 0;
        while (format[format_i] >= '0' && format[format_i] <= '9') {
          width[widthsize] = format[format_i];
          widthsize++;
          format_i++;
        }
        width[widthsize] = '\0';
        flagsScan.width = s21_atoi(width);
      }
      if (format[format_i] == 'h' || format[format_i] == 'l' ||
          format[format_i] == 'L') {
        flagsScan.typeflag = format[format_i];
        format_i++;
      }
      if (format[format_i] == 'l') {
        format_i += 1;
      }
      switch (format[format_i]) {
        case '*':
          skipFunc(str, &str_i, format, &format_i, &end);
          break;
        case 'c':
          parameters++;
          symbol = va_arg(arg, char *);
          convertCharScan(symbol, str, &str_i, format, format_i);
          counter++;
          break;
        case 's':
          stringSymbols = va_arg(arg, char *);
          if (end == 0) {
            convertStringScan(stringSymbols, str, &str_i, flagsScan, &counter);
          }
          break;
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'f':
          parameters++;
          switch (flagsScan.typeflag) {
            case 'l':
              numDouble = va_arg(arg, double *);
              break;
            case 'L':
              numLongDouble = va_arg(arg, long double *);
              break;
            case '\0':
              numFloat = va_arg(arg, float *);
              break;
          }
          long double nf = 0;
          if (end == 0) {
            end = convertFloatScan(&nf, str, &str_i, &counter);
          } else {
            nf = 1.0;
          }
          switch (flagsScan.typeflag) {
            case 'l':
              *numDouble = (double)nf;
              break;
            case 'L':
              *numLongDouble = (long double)nf;
              break;
            case '\0':
              *numFloat = (float)nf;
              break;
          }
          break;
        case 'd':
          parameters++;
          switch (flagsScan.typeflag) {
            case 'l':
              numLong = va_arg(arg, long int *);
              break;
            case 'h':
              numShort = va_arg(arg, short int *);
              break;
            case '\0':
              num = va_arg(arg, int *);
              break;
          }
          long long int n = 0;
          if (end == 0) {
            convertDecimalScan(&n, str, &str_i, flagsScan.width, &counter,
                               &end);
            if (!end) {
              switch (flagsScan.typeflag) {
                case 'l':
                  *numLong = (long int)n;
                  break;
                case 'h':
                  *numShort = (short int)n;
                  break;
                case '\0':
                  *num = (int)n;
                  break;
              }
            }
          }
          break;
        case 'u':
          parameters++;
          switch (flagsScan.typeflag) {
            case 'l':
              numUnsignedLongInt = va_arg(arg, unsigned long int *);
              break;
            case 'h':
              numUnsignedShortInt = va_arg(arg, unsigned short int *);
              break;
            case '\0':
              numUnsignedInt = va_arg(arg, unsigned int *);
              break;
          }
          if (end == 0) {
            long long int n = 0;
            convertDecimalScan(&n, str, &str_i, flagsScan.width, &counter,
                               &end);
            n = (unsigned long int)n;
            switch (flagsScan.typeflag) {
              case 'l':
                *numUnsignedLongInt = (unsigned long int)n;
                break;
              case 'h':
                *numUnsignedShortInt = (unsigned short int)n;
                break;
              case '\0':
                *numUnsignedInt = (unsigned int)n;
                break;
            }
          }
          break;
        case 'o':
        case 'i':
        case 'x':
        case 'X':
          parameters++;
          switch (flagsScan.typeflag) {
            case 'h':
              numShort = va_arg(arg, short int *);
              break;
            case 'l':
              numLong = va_arg(arg, long int *);
              break;
            case '\0':
              num = va_arg(arg, int *);
              break;
          }
          if (end == 0) {
            long int value = 0;
            smartConvertScan(&value, str, &str_i, flagsScan.width, &end,
                             format[format_i], &counter);
            switch (flagsScan.typeflag) {
              case 'h':
                *numShort = (short)value;
                break;
              case 'l':
                *numLong = (long)value;
                break;
              case '\0':
                *num = value;
                break;
            }
          }
          break;
        case 'p':
          parameters++;
          ptr = va_arg(arg, void **);
          smartConvertScan((long int *)ptr, str, &str_i, flagsScan.width, &end,
                           'p', &counter);
          break;
        case 'n':
          parameters++;
          num = va_arg(arg, int *);
          *num = str_i;
          if (str[str_i] == ' ') {
            *num += 1;
          }
          break;
        case '%':
          skipFunc(str, &str_i, format, &format_i, &end);
          break;
      }
      if (str[str_i] == '\0' && counter == 0 && parameters > 0) {
        counter = -1;
        break;
      }
      format_i++;
    }
  }
  va_end(arg);
  return counter;
}

void skipFunc(const char *str, int *pos, const char *format, int *format_i,
              int *end) {
  int spaceFlag = 0;
  while (str[*pos] == '\t' || str[*pos] == '\n') {
    *pos += 1;
  }
  while (format[*format_i] == '*') {
    *format_i += 1;
  }
  switch (format[*format_i]) {
    case '%':
      while (str[*pos] == ' ') {
        *pos += 1;
      }
      if (str[*pos] == '%') {
        *pos += 1;
      } else {
        *end = 1;
      }
      break;
    case 'e':
    case 'E':
    case 'g':
    case 'G':
    case 'f':
    case 'u':
    case 'd':
      while (str[*pos] == ' ') {
        *pos += 1;
      }
      if ((str[*pos] >= '0' && str[*pos] <= '9') || str[*pos] == '-' ||
          str[*pos] == '+') {
        while (str[*pos] != ' ' && str[*pos] != '\0') {
          *pos += 1;
        }
      }
      break;
    case 's':
      while (str[*pos] == ' ') {
        *pos += 1;
      }
      while (str[*pos] != ' ' && str[*pos] != '\0') {
        *pos += 1;
      }
      break;
    case 'c':
      for (int i = *format_i; format[i + 1] != '%'; i--) {
        if (format[i] == '%' && format[i - 1] == ' ') {
          spaceFlag = 1;
          break;
        }
        if (i == 0 && spaceFlag == 0) {
          break;
        }
      }
      if (spaceFlag == 1) {
        while (str[*pos] == ' ') {
          *pos += 1;
        }
        *pos += 1;
      } else {
        *pos += 1;
      }
      break;
  }
}

void smartConvertScan(long int *n, const char *str, int *pos, int numberSpec,
                      int *end, char specifier, int *counter) {
  char syntax[] = "0123456789ABCDEF";
  char string[50] = {'\0'};
  int size = 0;
  long int num = 0;
  long int coef = 1;
  int isZeroAtStart = 0;
  if (numberSpec < 1) {
    numberSpec = 50;
  }
  int base = 0;
  while ((str[*pos] == ' ' || str[*pos] == '\n' || str[*pos] == '\t') &&
         str[*pos] != '\0') {
    *pos += 1;
  }
  if (str[*pos] == '-' || str[*pos] == '+') {
    string[size] = str[*pos];
    size++;
    *pos += 1;
  }
  if (specifier == 'X' || specifier == 'x' ||
      ((str[*pos] == '0' && (str[*pos + 1] == 'X' || str[*pos + 1] == 'x')) &&
       (specifier == 'i' || specifier == 'p'))) {
    base = 16;
    if (str[*pos] == '0' && (str[*pos + 1] == 'X' || str[*pos + 1] == 'x')) {
      *pos += 2;
      isZeroAtStart = 1;
    }
  } else if (specifier == 'o' || (str[*pos] == '0' && specifier == 'i')) {
    base = 8;
    if (str[*pos] == '0') {
      *pos += 1;
      isZeroAtStart = 1;
    }
  } else if (specifier == 'p') {
    base = 16;
  } else {
    base = 10;
  }
  while (str[*pos] != '\0' && numberSpec > size) {
    if (str[*pos] == ' ') {
      string[size] = '\0';
      break;
    } else if (((str[*pos] >= '0' && str[*pos] <= '9') && base == 10) ||
               ((str[*pos] >= '0' && str[*pos] <= '7') && base == 8) ||
               (((str[*pos] >= '0' && str[*pos] <= '9') ||
                 (str[*pos] >= 'A' && str[*pos] <= 'F') ||
                 (str[*pos] >= 'a' && str[*pos] <= 'f')) &&
                base == 16)) {
      string[size] = str[*pos];
      size++;
      *pos += 1;
    } else {
      string[size] = '\0';
      break;
    }
  }
  if (string[size] != '\0') {
    string[size] = '\0';
  }
  if (string[0] == '\0') {
    *end = 1;
  }
  if (s21_strlen(string) == 1 && (string[0] == '+' || string[0] == '-')) {
    *end = 1;
    string[0] = '\0';
  }
  if (string[0] != '\0') {
    *n = 0;
    char *buf = (char *)s21_to_upper(string);
    for (int i = size - 1; i >= 0; i--) {
      if (i == 0 && buf[i] == '-') {
        *n *= -1;
        break;
      }
      if (i == 0 && buf[i] == '+') {
        break;
      }
      for (int j = 0; j < 16; j++) {
        if (buf[i] == syntax[j]) {
          num = j;
          break;
        }
      }
      *n += num * coef;
      coef *= base;
    }
    *counter += 1;
  } else if (isZeroAtStart) {
    *counter += 1;
  }
}

void convertDecimalScan(long long int *n, const char *str, int *pos,
                        int numberSpec, int *counter, int *end) {
  char string[50] = {'\0'};
  int size = 0;
  int hasStarted = 0;
  if (numberSpec < 1) {
    numberSpec = 50;
  }
  while (str[*pos] != '\0' && numberSpec != size) {
    if (str[*pos] == ' ' || str[*pos] == '\t' || str[*pos] == '\n') {
      if (hasStarted) {
        string[size] = '\0';
        break;
      } else {
        *pos += 1;
        continue;
      }
    } else if ((str[*pos] >= '0' && str[*pos] <= '9') ||
               ((str[*pos] == '+' || str[*pos] == '-') && size == 0)) {
      if (!hasStarted) {
        hasStarted = 1;
      }
      string[size] = str[*pos];
      size++;
      *pos += 1;
    } else {
      string[size] = '\0';
      break;
    }
  }
  if (string[size] != '\0') {
    string[size] = '\0';
  }
  if (string[0] == '\0') {
    *end = 1;
  }
  if (s21_strlen(string) == 1 && (string[0] == '+' || string[0] == '-')) {
    *end = 1;
    string[0] = '\0';
  }
  if (string[0] != '\0') {
    *n = s21_atoi(string);
    *counter += 1;
  }
}

void convertCharScan(char *n, const char *str, int *pos, const char *format,
                     int format_i) {
  int spaceFlag = 0;
  if (format[format_i - 2] == ' ') {
    spaceFlag = 1;
  }
  if (spaceFlag == 1) {
    while (str[*pos] == ' ' && str[*pos] != '\0') {
      *pos += 1;
    }
  }
  *n = str[*pos];
  *pos += 1;
}

void convertStringScan(char *aboba, const char *str, int *pos,
                       scanflags flagsScan, int *counter) {
  int j = 0;
  while (str[*pos] == ' ' || str[*pos] == '\t') {
    *pos += 1;
  }
  if (str[*pos] != '\0') {
    *counter += 1;
    if (flagsScan.iswidth) {
      for (int i = 0;
           i < flagsScan.width && str[*pos] != '\t' && str[*pos] != ' '; i++) {
        aboba[j] = str[*pos];
        *pos += 1;
        j++;
        if (str[*pos] == ' ' && str[*pos] == '\0') {
          break;
        }
      }
    } else {
      while (str[*pos] != ' ' && str[*pos] != '\t' && str[*pos] != '\0') {
        aboba[j] = str[*pos];
        *pos += 1;
        j++;
      }
      aboba[j] = '\0';
    }
  }
}

int convertFloatScan(long double *n, const char *str, int *pos, int *counter) {
  *n = 0.0;
  long int coeff = 1;
  int endFlag = 0;
  int mantissFlag = 0;
  int countOfInt = 0;
  int countOfDec = 0;
  int dotFlag = 0;
  int minusFlag = 0;
  int expFlag = 0;
  int negativeNumber = 0;
  double coeffDelDecimal = 0.1;
  while (str[*pos] == ' ' && str[*pos] != '\0') {
    *pos += 1;
  }
  if (str[*pos] == 'i' || str[*pos] == 'I') {
    if (str[*pos + 1] == 'n' || str[*pos + 1] == 'N') {
      if (str[*pos + 2] == 'f' || str[*pos + 2] == 'F') {
        *n = S21_INF;
        while (str[*pos] != ' ' && str[*pos] != '\0') {
          *pos += 1;
        }
        *counter += 1;
      }
    }
  } else if (str[*pos] == 'n' || str[*pos] == 'N') {
    if (str[*pos + 1] == 'a' || str[*pos + 1] == 'A') {
      if (str[*pos + 2] == 'n' || str[*pos + 2] == 'N') {
        *n = S21_NAN;
        while (str[*pos] != ' ' && str[*pos] != '\0') {
          *pos += 1;
        }
        *counter += 1;
      }
    }
  } else {
    if ((str[*pos] >= '0' && str[*pos] <= '9') || str[*pos] == '-' ||
        str[*pos] == '+') {
      if (str[*pos - 1] == 'e' && str[*pos] != '\0') {
        while (str[*pos] != ' ' && str[*pos] != '\0') {
          *pos += 1;
        }
      }
      if (str[*pos] == ' ') {
        *pos += 1;
      }
      if (str[*pos] == '-') {
        negativeNumber = 1;
        *pos += 1;
        if (str[*pos] < '0' || str[*pos] > '9') {
          endFlag = 1;
        }
      }
      if (str[*pos] == '+') {
        *pos += 1;
        if (str[*pos] < '0' || str[*pos] > '9') {
          endFlag = 1;
        }
      }
      for (int i = *pos; str[i] != ' ' && str[i] != '\0'; i++) {
        if (str[i] == '-') {
          minusFlag = 1;
        }
        if (str[i] == 'e') {
          expFlag = 1;
        }
      }
      for (int i = *pos; str[i] != '\0' && str[i] != ' '; i++) {
        if (str[i] == '.') {
          dotFlag = 1;
        }
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.' &&
            str[i + 1] == 'e') {
          mantissFlag = 1;
          endFlag = 1;
          break;
        }
        if (str[i] == 'e' || str[i] == '+' || str[i] == '-') {
          mantissFlag = 1;
          break;
        }
        if (dotFlag == 0 && str[i] >= '0' && str[i] <= '9') {
          countOfInt++;
          if (countOfInt > 1) {
            coeff *= 10;
          }
        } else if (dotFlag == 1 && str[i] >= '0' && str[i] <= '9') {
          countOfDec++;
        }
      }
      if (str[*pos] != '\0' && endFlag == 0) {
        *counter += 1;
      }
      for (int i = 0; i < countOfInt; i++) {
        *n += (str[*pos] - 48) * coeff;
        coeff /= 10.0;
        *pos += 1;
      }
      if (dotFlag == 1) {
        for (int i = 0; i < countOfDec; i++) {
          *pos += 1;
          *n += (str[*pos] - 48) * (long double)coeffDelDecimal;
          coeffDelDecimal /= 10.0;
        }
        if (countOfInt >= 1 && minusFlag == 0) {
          *n /= 10;
        }
      }
      if (dotFlag == 1 && minusFlag == 0 && endFlag == 0) {
        *n *= 10;
      } else if (expFlag == 1 && minusFlag == 1 && endFlag == 0) {
        *n /= 10;
      }
      *pos += 1;
      if (endFlag == 0 && mantissFlag == 1 && endFlag == 0) {
        convertMantissScan(n, str, pos, minusFlag, expFlag, negativeNumber);
      } else if (negativeNumber == 1 && endFlag == 0) {
        *n *= -1;
      } else if (endFlag == 1) {
        *n = 1.0;
      }
    }
  }
  return endFlag;
}

void convertMantissScan(long double *n, const char *str, int *pos,
                        int minusFlag, int expFlag, int negativeNumber) {
  int mantissCount = 0;
  int coeff = 1;
  int count = 0;
  while (str[*pos] == '+' || str[*pos] == '-' || str[*pos] == 'e' ||
         str[*pos] == '0') {
    *pos += 1;
  }
  for (int i = *pos; str[i] != ' ' && str[i] != '\0' && str[i] != '.'; i++) {
    if (count > 0) {
      coeff *= 10.0;
    }
    count++;
  }
  while (str[*pos] != ' ' && str[*pos] != '\0') {
    mantissCount += (str[*pos] - 48) * coeff;
    coeff /= 10.0;
    *pos += 1;
  }
  for (int i = 0; i < mantissCount; i++) {
    if (minusFlag == 0 && expFlag == 1) {
      *n *= 10.0;
    } else if (minusFlag == 1 && i > 0 && expFlag == 1) {
      *n /= 10.0;
    }
  }
  if (negativeNumber == 1) {
    *n *= -1;
  }
}
