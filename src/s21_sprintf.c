#include "s21_string.h"

void convertNonDecimal(char *value, long int n, int base, int isUP,
                       printflags flags, int precision, int isshort,
                       int isaddress, int size) {
  char syntax[] = "0123456789abcdef";
  char syntaxUP[] = "0123456789ABCDEF";
  int minusflag = 0;
  char *buf = malloc(100 * sizeof(char));
  if (n < 0) {
    minusflag = 1;
    n *= -1;
  }
  int iszero = 0;
  if (n == 0) {
    iszero = 1;
  }
  if (flags.isprecision) {
    flags.fillzero = 0;
  }
  int count = 0;
  int length = 0;
  if (flags.issharp && (!iszero || isaddress)) {
    if (base == 16) {
      length += 2;
    } else {
      length += 1;
    }
  }
  buf[99] = '\0';
  int i = 99;
  if (!flags.isprecision) {
    precision = 1;
  }
  if (precision != 0 || n != 0) {
    if (minusflag) {
      if (isshort) {
        n = 65536 - n;
      } else {
        n = 4294967296 - n;
      }
    }
    do {
      i--;
      count++;
      if (isUP) {
        buf[i] = syntaxUP[n % base];
      } else {
        buf[i] = syntax[n % base];
      }
      n /= base;
    } while (n != 0);
    while (count < precision) {
      i--;
      buf[i] = '0';
      count++;
    }
    length += count;
    if (length < size && !flags.leftflag && flags.fillzero) {
      while (length < size) {
        i--;
        buf[i] = '0';
        length++;
      }
    }
    if (flags.issharp && (!iszero || isaddress) &&
        (buf[i] != '0' || base != 8)) {
      if (isUP) {
        i--;
        buf[i] = 'X';
        length++;
      } else if (base == 16) {
        i--;
        buf[i] = 'x';
        length++;
      }
      i--;
      buf[i] = '0';
      length++;
    }
  }
  int ind = 0;
  while (buf[i] != '\0') {
    value[ind] = buf[i];
    i++;
    ind++;
  }
  free(buf);
  value[ind] = '\0';
#ifdef __linux__
  if (isaddress && !s21_strcmp(value, "0x0")) {
    s21_strcpy(value, "(nil)");
  }
#endif
}

void convert(char *value, long int n, printflags flags, int precision,
             int size) {
  char syntax[] = "0123456789";
  char *buf = malloc(100 * sizeof(char));
  int i = 99;
  int minusflag = 0;
  if (n < 0) {
    minusflag = 1;
    n *= -1;
  }
  buf[i] = '\0';
  if (flags.isprecision) {
    flags.fillzero = 0;
  }
  if (!flags.isprecision) {
    precision = 1;
  }
  int count = 0;
  if (precision != 0 || n != 0) {
    do {
      count++;
      i--;
      buf[i] = syntax[n % 10];
      n /= 10;
    } while (n != 0);
    while (count < precision) {
      i--;
      buf[i] = '0';
      count++;
    }
    if (count < size && !flags.leftflag && flags.fillzero) {
      while (count < size) {
        i--;
        buf[i] = '0';
        count++;
        if (minusflag && (size - count == 1)) {
          break;
        }
      }
    }
    if (minusflag) {
      i--;
      buf[i] = '-';
    } else if (flags.signflag) {
      i--;
      buf[i] = '+';
    } else if (flags.spaceflag) {
      i--;
      buf[i] = ' ';
    }
  }
  int ind = 0;
  while (buf[i] != '\0') {
    value[ind] = buf[i];
    i++;
    ind++;
  }
  value[ind] = '\0';
  free(buf);
}

void roundFloats(char *ptr, char ending, int isE) {
  int end = s21_strlen(ptr) - 1;
  if (isE) {
    end -= 4;
  }
  if (ending >= '5' && ending <= '9') {
    while (end + 1) {
      if (ptr[end] < '9' && ptr[end] >= '0') {
        ptr[end] = ptr[end] + 1;
        break;
      } else if (ptr[end] != '.') {
        ptr[end] = '0';
      }
      end--;
    }
  }
}

void noTrailing(char *value, int isE) {
  char *mantiss = malloc(5 * sizeof(char));
  char *buf = malloc(100 * sizeof(char));
  s21_strcpy(buf, value);
  int end = s21_strlen(buf) - 1;
  if (isE) {
    for (int i = 0; i < 4; i++) {
      mantiss[3 - i] = buf[end - i];
    }
    end -= 4;
    mantiss[4] = '\0';
  }
  for (int i = end; i > -1; i--) {
    if (buf[i] != '0') {
      if (buf[i] == '.') {
        buf[i] = '\0';
      } else {
        buf[i + 1] = '\0';
      }
      break;
    }
  }
  int j = s21_strlen(buf);
  int i = 0;
  if (isE) {
    for (int q = 4; q > 0; q--) {
      buf[j] = mantiss[i];
      j++;
      i++;
    }
    buf[j] = '\0';
  }
  free(mantiss);
  s21_strcpy(value, buf);
  free(buf);
}

void convertMantiss(char *value, long double n, int precision, printflags flags,
                    int isUP, int size) {
  char syntax[] = "0123456789";
  int length = 4;
  char *buf = malloc(100 * sizeof(char));
  int i = 99;
  buf[i] = '\0';
  char ending = '\0';
  int minusflag = 0;
  long double copy = 0;
  if (n < 0) {
    minusflag = 1;
    n *= -1;
  }
  int mantiss = 0;
  int less = 0;
  if (n < 1 && n != 0) {
    less = 1;
    while (n + 0.000000000000001 < 1) {
      n *= 10;
      mantiss++;
    }
  } else {
    while (n > 10) {
      mantiss++;
      n /= 10;
    }
  }
  do {
    i--;
    buf[i] = syntax[mantiss % 10];
    mantiss /= 10;
    if (mantiss == 0 && i == 98) {
      i--;
      buf[i] = '0';
    }
  } while (mantiss > 0);
  i--;
  if (less) {
    buf[i] = '-';
  } else {
    buf[i] = '+';
  }
  i--;
  if (isUP) {
    buf[i] = 'E';
  } else {
    buf[i] = 'e';
  }
  if (!flags.isprecision) {
    precision = 6;
  }
  if (precision > 0) {
    char *endbuf = malloc(50 * sizeof(char));
    int j = 0;
    endbuf[j] = '.';
    j++;
    copy = n;
    while (precision) {
      copy = copy - (int)copy;
      copy *= 10;
      endbuf[j] = syntax[(int)copy];
      j++;
      precision--;
      if (precision == 0) {
        copy = copy - (int)copy;
        copy *= 10;
        ending = syntax[(int)copy];
        if (ending == '5' && syntax[(int)((copy - (int)copy) * 10)] == '9') {
          ending = '6';
        }
      }
    }
    endbuf[j] = '\0';
    do {
      j--;
      i--;
      length++;
      buf[i] = endbuf[j];
    } while (j);
    free(endbuf);
  } else {
    if (flags.issharp) {
      i--;
      length++;
      buf[i] = '.';
    }
    copy = ((n - (int)n) * 10);
    ending = syntax[(int)copy];
    if (ending == '5' && syntax[(int)((copy - (int)copy) * 10)] == '9') {
      ending = '6';
    }
  }
  int nn = (int)n;
  do {
    i--;
    length++;
    buf[i] = syntax[nn % 10];
    nn /= 10;
  } while (nn > 0);
  if (length < size && !flags.leftflag && flags.fillzero) {
    while (length < size) {
      i--;
      buf[i] = '0';
      length++;
      if (minusflag && (size - length == 1)) {
        break;
      }
    }
  }
  if (minusflag) {
    i--;
    buf[i] = '-';
  } else if (flags.signflag) {
    i--;
    buf[i] = '+';
  } else if (flags.spaceflag) {
    i--;
    buf[i] = ' ';
  }
  int ind = 0;
  while (buf[i] != '\0') {
    value[ind] = buf[i];
    i++;
    ind++;
  }
  value[ind] = '\0';
  free(buf);
  roundFloats(value, ending, 1);
}

void convertFloat(char *value, long double n, int precision, printflags flags,
                  int size) {
  char syntax[] = "0123456789";
  char *buf = malloc(100 * sizeof(char));
  int i = 99;
  buf[i] = '\0';
  int length = 0;
  char ending = '\0';
  long double copy = 0;
  int minusflag = 0;
  if (n < 0) {
    minusflag = 1;
    n *= -1;
  }
  if (!flags.isprecision) {
    precision = 6;
  }
  if (precision > 0) {
    char *endbuf = malloc(50 * sizeof(char));
    int j = 0;
    endbuf[j] = '.';
    j++;
    copy = n;
    while (precision) {
      copy = copy - (long long int)copy;
      copy *= 10;
      endbuf[j] = syntax[(int)copy];
      j++;
      precision--;
      if (precision == 0) {
        copy = copy - (int)copy;
        copy *= 10;
        ending = syntax[(int)copy];
        if (ending == '5' && syntax[(int)((copy - (int)copy) * 10)] == '9') {
          ending = '6';
        }
      }
    }
    endbuf[j] = '\0';
    do {
      j--;
      i--;
      length++;
      buf[i] = endbuf[j];
    } while (j);
    free(endbuf);
  } else {
    if (flags.issharp) {
      i--;
      length++;
      buf[i] = '.';
    }
    copy = ((n - (int)n) * 10);
    ending = syntax[(int)copy];
    if (ending == '5' && syntax[(int)((copy - (int)copy) * 10)] == '9') {
      ending = '6';
    }
  }
  long int nn = (long int)n;
  do {
    i--;
    length++;
    buf[i] = syntax[nn % 10];
    nn /= 10;
  } while (nn > 0);
  if (length < size && !flags.leftflag && flags.fillzero) {
    while (length < size) {
      i--;
      buf[i] = '0';
      length++;
      if (minusflag && (size - length == 1)) {
        break;
      }
    }
  }
  if (minusflag) {
    i--;
    buf[i] = '-';
  } else if (flags.signflag) {
    i--;
    buf[i] = '+';
  } else if (flags.spaceflag) {
    i--;
    buf[i] = ' ';
  }
  int ind = 0;
  while (buf[i] != '\0') {
    value[ind] = buf[i];
    i++;
    ind++;
  }
  value[ind] = '\0';
  free(buf);
  roundFloats(value, ending, 0);
}

void specG(char *value, long double n, int precision, printflags flags,
           int isUP, int size) {
  long double copy = n;
  int less = 0;
  int X = 0;
  if (copy < 0) {
    copy *= -1;
  }
  if (copy < 1 && copy != 0) {
    less = 1;
    while (copy + 0.000000000000001 < 1) {
      copy *= 10;
      X++;
    }
  } else {
    while (copy > 10) {
      X++;
      copy /= 10;
    }
  }
  if (less) {
    X *= -1;
  }
  int P = 0;
  if (precision != 0 && flags.isprecision) {
    P = precision;
  } else if (!flags.isprecision) {
    P = 6;
  } else {
    P = 1;
  }
  flags.isprecision = 1;
  int precise = 0;
  if (P > X && X >= -4) {
    precise = P - (X + 1);
    convertFloat(value, n, precise, flags, size);
  } else {
    precise = P - 1;
    convertMantiss(value, n, precise, flags, isUP, size);
  }
  if (!flags.issharp) {
    if (P > X && X >= -4) {
      noTrailing(value, 0);
    } else {
      noTrailing(value, 1);
    }
  }
}

void convertChar(char *value, int n) {
  value[0] = (char)n;
  value[1] = '\0';
}

void convertString(char *value1, char *str, int precision, printflags flags) {
  if (!flags.isprecision) {
    precision = s21_strlen(str);
  }
  int i = 0;
  while (precision && str[i] != '\0') {
    value1[i] = str[i];
    i++;
    precision--;
  }
  value1[i] = '\0';
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list arg;
  int size = 0;
  char width[10] = {'\0'};
  int widthsize = 0;
  int format_i = 0;
  int str_i = 0;
  int precision = 0;
  char acc[10] = {'\0'};
  int accsize = 0;
  long int num = 0;
  int isshort = 0;
  short int shorttmp = 0;
  int *address = s21_NULL;
  long double numdouble = 0;
  char value[100];
  int ind = 0;
  va_start(arg, format);
  while (format[format_i] != '\0') {
    if (format[format_i] != '%') {
      str[str_i] = format[format_i];
      format_i++;
      str_i++;
    } else if (format[format_i + 1] == '%') {
      str[str_i] = format[format_i + 1];
      format_i += 2;
      str_i++;
    } else {
      printflags flags = {'\0', 0, 0, 0, 0, 0, 0};
      for (int i = 0; i < 10; i++) {
        width[i] = '\0';
        acc[i] = '\0';
      }
      precision = 0;
      size = 0;
      isshort = 0;
      format_i++;
      while (format[format_i] == '+' || format[format_i] == '-' ||
             format[format_i] == ' ' || format[format_i] == '#' ||
             format[format_i] == '0') {
        switch (format[format_i]) {
          case '+':
            flags.signflag = 1;
            break;
          case '-':
            flags.leftflag = 1;
            break;
          case ' ':
            flags.spaceflag = 1;
            break;
          case '#':
            flags.issharp = 1;
            break;
          case '0':
            flags.fillzero = 1;
        }
        format_i++;
      }
      if ((format[format_i] >= 48 && format[format_i] <= 57) ||
          format[format_i] == '*') {
        if (format[format_i] == '*') {
          size = va_arg(arg, int);
          format_i++;
        } else {
          widthsize = 0;
          while (format[format_i] >= 48 && format[format_i] <= 57) {
            width[widthsize] = format[format_i];
            widthsize++;
            format_i++;
          }
          width[widthsize] = '\0';
          size = s21_atoi(width);
        }
      }
      if (format[format_i] == '.') {
        flags.isprecision = 1;
        format_i++;
        if (format[format_i] == '*') {
          precision = va_arg(arg, int);
          format_i++;
        } else {
          accsize = 0;
          if (format[format_i] == '-') {
            acc[accsize] = format[format_i];
            accsize++;
            format_i++;
          }
          while (format[format_i] >= 48 && format[format_i] <= 57) {
            acc[accsize] = format[format_i];
            accsize++;
            format_i++;
          }
          acc[accsize] = '\0';
          precision = s21_atoi(acc);
        }
      }
      if (format[format_i] == 'h' || format[format_i] == 'l' ||
          format[format_i] == 'L') {
        flags.typeflag = format[format_i];
        format_i++;
      }
      switch (format[format_i]) {
        case 'c':
          convertChar(value, va_arg(arg, int));
          break;
        case 'd':
          switch (flags.typeflag) {
            case 'h':
              num = va_arg(arg, int);
              shorttmp = num;
              num = shorttmp;
              break;
            case 'l':
              num = va_arg(arg, long);
              break;
            case '\0':
              num = va_arg(arg, int);
              break;
          }
          convert(value, num, flags, precision, size);
          num = shorttmp = 0;
          break;
        case 'i':
          switch (flags.typeflag) {
            case 'h':
              num = va_arg(arg, int);
              shorttmp = num;
              num = shorttmp;
              break;
            case 'l':
              num = va_arg(arg, long);
              break;
            case '\0':
              num = va_arg(arg, int);
              break;
          }
          convert(value, num, flags, precision, size);
          num = shorttmp = 0;
          break;
        case 's':
          convertString(value, va_arg(arg, char *), precision, flags);
          break;
        case 'f':
          if (flags.typeflag == 'L') {
            numdouble = va_arg(arg, long double);
          } else {
            numdouble = va_arg(arg, double);
          }
          convertFloat(value, numdouble, precision, flags, size);
          break;
        case 'u':
          switch (flags.typeflag) {
            case 'h':
              num = va_arg(arg, unsigned int);
              shorttmp = num;
              num = shorttmp;
              break;
            case 'l':
              num = va_arg(arg, unsigned long);
              break;
            case '\0':
              num = va_arg(arg, unsigned int);
              break;
          }
          flags.signflag = 0;
          flags.spaceflag = 0;
          convert(value, num, flags, precision, size);
          break;
        case 'x':
          switch (flags.typeflag) {
            case 'h':
              num = va_arg(arg, int);
              shorttmp = num;
              num = shorttmp;
              isshort = 1;
              break;
            case 'l':
              num = va_arg(arg, long);
              break;
            case '\0':
              num = va_arg(arg, int);
              break;
          }
          convertNonDecimal(value, num, 16, 0, flags, precision, isshort, 0,
                            size);
          break;
        case 'X':
          switch (flags.typeflag) {
            case 'h':
              num = va_arg(arg, int);
              shorttmp = num;
              num = shorttmp;
              isshort = 1;
              break;
            case 'l':
              num = va_arg(arg, long);
              break;
            case '\0':
              num = va_arg(arg, int);
              break;
          }
          convertNonDecimal(value, num, 16, 1, flags, precision, isshort, 0,
                            size);
          break;
          break;
        case 'g':
          if (flags.typeflag == 'L') {
            numdouble = va_arg(arg, long double);
          } else {
            numdouble = va_arg(arg, double);
          }
          specG(value, numdouble, precision, flags, 0, size);
          break;
        case 'G':
          if (flags.typeflag == 'L') {
            numdouble = va_arg(arg, long double);
          } else {
            numdouble = va_arg(arg, double);
          }
          specG(value, numdouble, precision, flags, 1, size);
          break;
        case 'e':
          if (flags.typeflag == 'L') {
            numdouble = va_arg(arg, long double);
          } else {
            numdouble = va_arg(arg, double);
          }
          convertMantiss(value, numdouble, precision, flags, 0, size);
          break;
        case 'E':
          if (flags.typeflag == 'L') {
            numdouble = va_arg(arg, long double);
          } else {
            numdouble = va_arg(arg, double);
          }
          convertMantiss(value, numdouble, precision, flags, 1, size);
          break;
        case 'o':
          switch (flags.typeflag) {
            case 'h':
              num = va_arg(arg, unsigned int);
              shorttmp = num;
              num = shorttmp;
              isshort = 1;
              break;
            case 'l':
              num = va_arg(arg, unsigned long);
              break;
            case '\0':
              num = va_arg(arg, unsigned int);
              break;
          }
          convertNonDecimal(value, num, 8, 0, flags, precision, isshort, 0,
                            size);
          break;
        case 'n':
          address = va_arg(arg, int *);
          *address = str_i;
          break;
        case 'p':
          flags.issharp = 1;
          convertNonDecimal(value, va_arg(arg, long int), 16, 0, flags,
                            precision, isshort, 1, size);
          break;
      }
      if (format[format_i] != 'n') {
        int realsize = s21_strlen(value);
        if (!flags.leftflag && (realsize < size)) {
          for (int i = 0; i < (size - realsize); i++) {
            str[str_i] = ' ';
            str_i++;
          }
        }
        ind = 0;
        while (value[ind] != '\0') {
          str[str_i] = value[ind];
          ind++;
          str_i++;
        }
        if (flags.leftflag && (realsize < size)) {
          for (int i = 0; i < (size - realsize); i++) {
            str[str_i] = ' ';
            str_i++;
          }
        }
      }
      format_i++;
    }
  }
  str[str_i] = '\0';
  va_end(arg);
  return str_i;
}
