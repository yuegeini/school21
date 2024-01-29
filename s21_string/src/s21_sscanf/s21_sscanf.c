#include "../s21_string.h"

int spaces(const char ***str) {
  int count = 0;
  while (***str == ' ') {
    (**str)++;
    count++;
  }
  return count;
}

int read_int(const char **str, int *num, int base) {
  int sign = 1;
  int count = spaces(&str);
  if (**str == '-') {
    count++;
    sign = -1;
    (*str)++;
  }
  if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    if (base == 10) base = 16;
    count += 2;
    *str += 2;
  } else if (**str == '0') {
    if (base == 10) base = 8;
    count += 1;
    *str += 1;
  }
  long long n = 0;
  while ((**str >= '0' && **str <= '9') || (**str >= 'a' && **str <= 'f') ||
         (**str >= 'A' && **str <= 'F')) {
    long long digit = 0;
    if (**str >= '0' && **str <= '9') {
      digit = **str - '0';
    } else if (**str >= 'a' && **str <= 'f') {
      digit = **str - 'a' + 10;
    } else if (**str >= 'A' && **str <= 'F') {
      digit = **str - 'A' + 10;
    }
    n = n * base + digit;
    count++;
    (*str)++;
  }
  n = n * sign;
  *num = n;
  return count;
}

int read_decimal(const char **str, int *num, int sym) {
  int n = 0;
  int count = spaces(&str);
  int sign = 1;
  if (**str == '-') {
    count++;
    sign = -1;
    (*str)++;
    sym--;
  } else if (**str == '+') {
    count++;
    (*str)++;
    sym--;
  }
  while ((**str >= '0' && **str <= '9') && sym != 0) {
    n = n * 10 + (**str - '0');
    (*str)++;
    count++;
    sym--;
  }
  *num = sign * n;
  return count;
}

int read_float(const char **str, float *num) {
  int mantissa = 0;
  int count = spaces(&str);
  int sign = 1;
  if (**str == '-') {
    count++;
    sign = -1;
    (*str)++;
  }
  while (**str >= '0' && **str <= '9') {
    mantissa = mantissa * 10 + (**str - '0');
    (*str)++;
    count++;
  }
  if (**str == '.') {
    (*str)++;
    count++;
  }
  long double exp = 0;
  int count2 = 0;
  while (**str >= '0' && **str <= '9') {
    exp = exp * 10 + (**str - '0');
    (*str)++;
    count2++;
  }
  exp = exp / pow(10, count2);
  float total = mantissa + (float)exp;
  if (**str == 'e') {
    (*str)++;
    count2++;
    if (**str == '+') {
      (*str)++;
      count2++;
    }
    int e = 0;
    while (**str >= '0' && **str <= '9') {
      e = e * 10 + (**str - '0');
      (*str)++;
      count2++;
    }
    total = total * pow(10, e);
  }
  *num = sign * total;
  return count + count2;
}

int read_char(const char **str, char *buf, int count) {
  int sp = 0;
  if (count != 0) sp = spaces(&str);
  if (count == -1) count = 1;
  for (int i = 0; i < count; i++) *(buf)++ = *(*str)++;
  return sp + count;
}

int read_string(const char **str, char *buf) {
  int count = spaces(&str);
  while (**str && **str != ' ') {
    *buf++ = *(*str)++;
    count++;
  }
  *buf = '\0';
  return count;
}

int read_oct(const char **str, int *num) {
  int n = 0;
  int count = spaces(&str);
  int sign = 1;
  if (**str == '-') {
    count++;
    sign = -1;
    (*str)++;
  }
  while ((**str >= '0' && **str <= '7')) {
    n = n * 8 + (**str - '0');
    (*str)++;
    count++;
  }
  *num = sign * n;
  return count;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int count = 0, count2 = 0, stop = 1;
  while (*format && stop) {
    if (*format == '%') {
      format++;
      int flag = 0;
      if (*format == '*') {
        format++;
        flag = 1;
      }
      int num = 0;
      while (*format >= '0' && *format <= '9') {
        num = num * 10 + (*format - '0');
        format++;
      }
      if (num == 0) num--;
      if (*format == 'd' || *format == 'u') {
        int *p;
        if (flag == 0)
          p = va_arg(args, int *);
        else
          p = malloc(sizeof(int) * 100);
        if ((count2 += read_decimal(&str, p, num)) > 0) flag == 0 ? count++ : 0;
        if (flag != 0) free(p);
      } else if (*format == 's') {
        char *s;
        if (flag == 0)
          s = va_arg(args, char *);
        else
          s = malloc(sizeof(char *) * 100);
        if ((count2 += read_string(&str, s)) > 0) flag == 0 ? count++ : 0;
        if (flag != 0) free(s);
      } else if (*format == 'c') {
        char *c;
        if (flag == 0)
          c = va_arg(args, char *);
        else
          c = malloc(sizeof(char) * 100);
        if ((count2 += read_char(&str, c, num)) > 0) flag == 0 ? count++ : 0;
        if (flag != 0) free(c);
      } else if (*format == 'e' || *format == 'E' || *format == 'f' ||
                 *format == 'g' || *format == 'G') {
        float *f;
        if (flag == 0)
          f = va_arg(args, float *);
        else
          f = malloc(sizeof(float) * 100);
        if ((count2 += read_float(&str, f)) > 0) flag == 0 ? count++ : 0;
        if (flag != 0) free(f);
      } else if (*format == 'i' || *format == 'X' || *format == 'x') {
        int *i;
        if (flag == 0)
          i = va_arg(args, int *);
        else
          i = malloc(sizeof(int) * 100);
        if ((count2 += read_int(
                 &str, i, (*format == 'X' || *format == 'x') ? 16 : 10)) > 0)
          flag == 0 ? count++ : 0;
        if (flag != 0) free(i);
      } else if (*format == 'o') {
        int *o;
        if (flag == 0)
          o = va_arg(args, int *);
        else
          o = malloc(sizeof(int) * 100);
        if ((count2 += read_oct(&str, o)) > 0) flag == 0 ? count++ : 0;
        if (flag != 0) free(o);
      } else if (*format == '%') {
        int spaces = 0;
        while (*str == ' ') {
          (str)++;
          spaces++;
        }
        count2 += spaces;
        if (*str == '%') {
          (str)++;
          count2++;
        } else
          stop = 0;
      } else if (*format == 'n') {
        int *n = va_arg(args, int *);
        int spaces = 0;
        while (*str == ' ') {
          (str)++;
          spaces++;
        }
        count2 += spaces;
        *n = count2;
      }
    } else {
      if (*str == *format && *str != ' ') {
        str++;
      }
    }
    format++;
  }

  va_end(args);
  return count;
}
