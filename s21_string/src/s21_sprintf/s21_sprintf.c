
#include "s21_sprintf.h"
// прототип : %[flags][width][.precision][length]specifier
int s21_sprintf(char *str, const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  str = s21_strcpy(str, "");
  int zero_str = 0, zero_str_flag = 0;  // счетчики 0 и \0
  while (*format) {
    struct s_struct formats = {0};
    formats.Precision = -1;
    if (*format != '%') add_char(str, format, &zero_str_flag, &formats);
    if (*format == '%') {
      format++;
      while (check_flags(format)) {
        set_flags(&formats, format++);
      }
      while (check_dig(format) || *format == '*') {
        set_width_Precision(&formats.Width, format++, &arg);
        if (formats.Width < 0) {
          formats.Width *= -1;
          formats.flag_Minus = 1;
        }
      }
      if (*format == '.') {
        format++;
        formats.point = 1;
        formats.Precision = 0;
        while (check_dig(format) || *format == '*')
          set_width_Precision(&formats.Precision, format++, &arg);
      }
      if (check_lenght(format)) {
        formats.flag_length = *format;
        format++;
      }
      if (check_specf(&formats, format)) s21_default_precision(&formats);
      s21_check(format, str, &formats, &arg, &zero_str_flag);
    }
    format++;
    zero_str += formats.zero_simbol;
  }
  va_end(arg);
  return (int)s21_strlen(str) + zero_str;
}

void s21_check(const char *format, char *str, struct s_struct *formats,
               va_list *arg, int *zero_str_flag) {
  char *p_str = S21_NULL;
  p_str = calloc(1024, sizeof(char));
  switch (*format) {
    case 'c':
      s21_c(p_str, arg, formats, zero_str_flag);
      break;
    case 's':
      s21_s(p_str, arg, formats);
      break;
    case 'd':
      s21_d(p_str, arg, formats);
      break;
    case 'f':
      s21_f(p_str, arg, formats);
      break;
    case 'o':
      s21_o(p_str, arg, formats);
      break;
    case 'u':
      s21_u(p_str, arg, formats);
      break;
    case 'x':
    case 'X':
      s21_xX(p_str, arg, formats);
      break;
    case '%':
      s21_percent(p_str, formats);
      break;
    default:
      break;
  }
  s21_strcat(str, p_str);
  free(p_str);
}

void s21_delete_zero(char *tmp_str, struct s_struct *formats) {
  int len_str = s21_strlen(tmp_str) - 1;
  if (formats->Precision > 0)
    while (tmp_str[len_str] == '0') {
      tmp_str[len_str] = '\0';
      len_str--;
    }
}

void s21_mantis(char *tmp_str, struct s_struct *formats, int notation,
                char *str_notat, int flag) {
  s21_strcat(tmp_str, s21_strchr("eg", formats->specifier) ? "e" : "E");
  s21_strcat(tmp_str, flag == -1 ? "-" : "+");
  if (abs(notation) > 9) {
    s21_int_to_str(formats, str_notat, notation);
    s21_strcat(tmp_str, str_notat);
  } else {
    s21_int_to_str(formats, str_notat, notation);
    s21_strcat(tmp_str, "0");
    s21_strcat(tmp_str, str_notat);
  }
}

void s21_xX(char *tmp_str, va_list *arg, struct s_struct *formats) {
  unsigned short sd_number = 0;
  unsigned int number = 0;
  switch (formats->flag_length) {
    case 'h':
      sd_number = (unsigned short)va_arg(*arg, unsigned int);
      s21_xX_to_str(formats, tmp_str, sd_number);
      break;
    default:
      number = va_arg(*arg, unsigned int);
      s21_xX_to_str(formats, tmp_str, number);
      break;
  }
  s21_string_precision(formats, tmp_str);
  s21_string_flags(formats, tmp_str);
  s21_string_width(formats, tmp_str);
}
void s21_u(char *tmp_str, va_list *arg, struct s_struct *formats) {
  unsigned long ul_number = 0;
  unsigned short us_number = 0;
  unsigned int number = 0;
  switch (formats->flag_length) {
    case 'l':
      ul_number = va_arg(*arg, unsigned long);
      s21_u_to_str(formats, tmp_str, ul_number);
      break;
    case 'h':
      us_number = (unsigned short)va_arg(*arg, unsigned int);
      s21_u_to_str(formats, tmp_str, us_number);
      break;
    default:
      number = va_arg(*arg, unsigned int);
      s21_u_to_str(formats, tmp_str, number);
      break;
  }
  s21_string_precision(formats, tmp_str);
  s21_string_flags(formats, tmp_str);
  s21_string_width(formats, tmp_str);
}

void s21_o(char *tmp_str, va_list *arg, struct s_struct *formats) {
  unsigned long int ld_number = 0;
  unsigned short int sd_number = 0;
  unsigned int number = 0;
  switch (formats->flag_length) {
    case 'l':
      ld_number = va_arg(*arg, unsigned long int);
      s21_o_to_str(formats, tmp_str, ld_number);
      break;
    case 'h':
      sd_number = (unsigned short)va_arg(*arg, unsigned int);
      s21_o_to_str(formats, tmp_str, sd_number);
      break;
    default:
      number = va_arg(*arg, unsigned int);
      s21_o_to_str(formats, tmp_str, number);
      break;
  }
  s21_string_precision(formats, tmp_str);
  s21_string_flags(formats, tmp_str);
  s21_string_width(formats, tmp_str);
}

void s21_s(char *p_str, va_list *arg, struct s_struct *formats) {
  char *string = S21_NULL;
  string = va_arg(*arg, char *);
  // "%s Test %3.s Test %5.7s TEST %10s %#s %-s %+s %.s % .s"
  if (string == S21_NULL) {
    if (formats->Precision > 6 || formats->point == !1)
      s21_strcat(p_str, "(null)");
    else
      s21_strcat(p_str, "");
  } else {
    if (formats->Precision > -1)
      s21_strncat(p_str, string, formats->Precision);
    else
      s21_strcat(p_str, string);
  }
  s21_string_precision(formats, p_str);
  s21_string_flags(formats, p_str);
  s21_string_width(formats, p_str);
}

void s21_f(char *tmp_str, va_list *arg, struct s_struct *formats) {
  double d_number = 0;
  long double l_number = 0;
  switch (formats->flag_length) {
    case 'L':
      l_number = va_arg(*arg, long double);
      s21_float_to_str(formats, tmp_str, l_number);
      break;
    case 'l':
    default:
      d_number = va_arg(*arg, double);
      s21_float_to_str(formats, tmp_str, d_number);
      break;
  }
  add_for_fdeEfgG(formats, tmp_str);
}

void s21_d(char *tmp_str, va_list *arg, struct s_struct *formats) {
  int number = 0;
  long int li_number = 0;
  short int sh_number = 0;
  switch (formats->flag_length) {
    case 'l':
      li_number = va_arg(*arg, long int);
      s21_int_to_str(formats, tmp_str, li_number);
      break;
    case 'h':
      sh_number = (short)va_arg(*arg, int);
      s21_int_to_str(formats, tmp_str, sh_number);
      break;
    default:
      number = va_arg(*arg, int);
      s21_int_to_str(formats, tmp_str, number);
      break;
  }
  s21_string_precision(formats, tmp_str);
  add_for_fdeEfgG(formats, tmp_str);
}

void s21_xX_to_str(struct s_struct *formats, char *tmp_str,
                   unsigned long long number) {
  char *point = S21_NULL;
  int flag = 1, x_or_X = 0;
  point = tmp_str;
  x_or_X = formats->specifier == 'x' ? 32 : 0;
  if (formats->point == 1 && number == 0) {
    s21_strcat(tmp_str, " ");
  } else
    while (flag) {
      unsigned int digit;
      if (number >= 16) {
        digit = number % 16;
        number = (number - digit) / 16;
      } else {
        digit = number;
        flag = 0;
      }
      if (digit < 10)
        *(point++) = (digit + '0');
      else
        *(point++) = (digit + 'A' + x_or_X - 10);
    }
  *point = '\0';
  if (number == 0) formats->flag_Sharp = 0;
  s21_reverse_string(tmp_str);
}

void s21_u_to_str(struct s_struct *formats, char *tmp_str,
                  unsigned long long number) {
  char *point = S21_NULL;
  int flag = 1;
  point = tmp_str;
  if (formats->point == 1 && number == 0) {
    s21_strcat(tmp_str, " ");
  } else
    while (flag) {
      unsigned int digit;
      if (number >= 10) {
        digit = number % 10;
        number = (number - digit) / 10;
      } else {
        digit = number;
        flag = 0;
      }
      *(point++) = digit + '0';
    }

  *point = '\0';
  s21_reverse_string(tmp_str);
}

void s21_o_to_str(struct s_struct *formats, char *tmp_str, long long number) {
  char *point = S21_NULL;
  int flag = 1;
  point = tmp_str;
  long long check_number = number;
  if (formats->point == 1 && number == 0) {
    s21_strcat(tmp_str, " ");
  } else
    while (flag) {
      unsigned int digit;
      if (number > 7) {
        digit = number % 8;
        number = (number - digit) / 8;
      } else {
        digit = number;
        flag = 0;
      }
      *(point++) = (char)(digit + '0');
    }
  if (formats->flag_Sharp == 1 && check_number != 0) *(point++) = '0';
  *point = '\0';
  s21_reverse_string(tmp_str);
}

void s21_default_precision(struct s_struct *formats) {
  if (formats->point && formats->Precision <= 0) {
    formats->Precision = 0;
  }
  if (!formats->point && s21_strchr("eEfgG", formats->specifier)) {
    formats->Precision = 6;
  }
}

void s21_float_to_str(struct s_struct *formats, char *tmp_str,
                      long double number) {
  char result[256] = {0};
  formats->sign = number < 0 ? -1 : 1;
  number *= formats->sign;
  int local_sign = formats->sign;
  if (formats->Precision <= 0) {
    s21_int_to_str(formats, tmp_str, roundl(number));
  } else {
    long double left = 0, right = 0, check = 1;
    right = modfl(number, &left);
    left = roundl(left);
    for (int i = 0; i < formats->Precision; i++) {
      right *= 10, check *= 10;
    }
    if (roundl(right) == check) left += 1;
    s21_int_to_str(formats, tmp_str, left);
    s21_strcat(tmp_str, ".");
    if (roundl(right) != check) s21_int_to_str(formats, result, roundl(right));
    s21_string_precision(formats, result);

    s21_strcat(tmp_str, result);
  }
  formats->sign = local_sign;
}

void s21_int_to_str(struct s_struct *formats, char *tmp_str,
                    long double number) {
  char *point = tmp_str;
  int flag = 1;
  formats->sign = number < 0 ? -1 : 1;
  number *= formats->sign;
  if (formats->point == 1 && number == 0 && formats->Precision == 0 &&
      formats->specifier == 'd') {
    if (formats->Width == 0)
      s21_strcat(tmp_str, "");
    else
      s21_strcat(tmp_str, " ");
  } else
    while (flag) {
      int digit = 0;
      if (number >= 10) {
        digit = fmodl(number, 10);
        number = (number - digit) / 10;
      } else {
        digit = number;
        flag = 0;
      }
      *point = digit + '0';
      point++;
    }
  s21_reverse_string(tmp_str);
}

// точность
void s21_string_precision(struct s_struct *formats, char *tmp_str) {
  char *string_precision = S21_NULL;
  string_precision = calloc(1024, sizeof(char));
  int pos = 0;
  int len_tmp = s21_strlen(tmp_str);
  if (s21_strchr("feEpdouxX", formats->specifier)) {
    if (formats->specifier == 'p') {
      s21_strcpy(string_precision, tmp_str);
      for (int i = len_tmp; i < formats->Precision; i++) {
        string_precision[i] = '0';
      }
      s21_strcpy(tmp_str, string_precision);
    } else {
      while (pos < formats->Precision - len_tmp) {
        string_precision[pos++] = '0';
      }
      for (int i = 0; tmp_str[i] != '\0'; i++) {
        string_precision[pos++] = tmp_str[i];
      }
      s21_strcpy(tmp_str, string_precision);
    }
  }
  free(string_precision);
}

void s21_string_flags(struct s_struct *formats, char *tmp_str) {
  int pos = 0;
  if (!s21_strchr("cuo\%", formats->specifier)) {
    if (formats->sign < 0) {
      s21_move_string(tmp_str);
      tmp_str[pos++] = '-';
      formats->sign = 0;
    }
    if (formats->flag_Plus && formats->sign != 0) {
      s21_move_string(tmp_str);
      tmp_str[pos] = (formats->sign > 0) ? '+' : '-';
      formats->sign = 0;
    }
    if (formats->flag_Space && formats->sign != 0) {
      s21_move_string(tmp_str);
      tmp_str[pos] = (formats->sign > 0) ? ' ' : '-';
      formats->sign = 0;
    }
    if (formats->flag_Sharp) {
      s21_sharp_flag(formats, tmp_str);
    }
  }
  if (formats->flag_Minus) {
    pos = (int)s21_strlen(tmp_str);
    while (pos < formats->Width) {
      tmp_str[pos++] = ' ';
    }
  }
}

// обработка флага #
void s21_sharp_flag(struct s_struct *formats, char *tmp_str) {
  int pos = 0;
  if (s21_strchr("oxX", formats->specifier)) {
    if (formats->specifier == 'x' || formats->specifier == 'X') {
      s21_move_string(tmp_str);
    }
    formats->specifier == 'o' ? 1 : s21_move_string(tmp_str);
    tmp_str[pos++] = '0';

    if (formats->specifier != 'o')
      tmp_str[pos] = formats->specifier == 'x' ? 'x' : 'X';
  }

  if (s21_strchr("eEf", formats->specifier)) {
    if (!s21_strchr(tmp_str, '.')) {
      tmp_str[s21_strlen(tmp_str)] = '.';
    }
  }
}
// повторяющийся модуль
void add_for_fdeEfgG(struct s_struct *formats, char *tmp_str) {
  if (formats->flag_Zero == 1 && formats->flag_Minus != 1 &&
      (formats->sign == -1 || formats->flag_Space ||
       (formats->sign == 1 && formats->flag_Plus == 1))) {
    formats->Width -= 1;
    s21_string_width(formats, tmp_str);
    s21_string_flags(formats, tmp_str);
  } else {
    s21_string_flags(formats, tmp_str);
    s21_string_width(formats, tmp_str);
  }
}

// ширина выводимой строки
void s21_string_width(struct s_struct *formats, char *tmp_str) {
  int pos_str = (int)s21_strlen(tmp_str);
  if (formats->Width > pos_str) {
    tmp_str[formats->Width + 1] = '\0';
    while (pos_str >= 0) {
      tmp_str[formats->Width--] = tmp_str[pos_str--];
    }
    for (pos_str = 0; pos_str <= formats->Width; pos_str++) {
      if (s21_strchr("dopuxX", formats->specifier)) {
        tmp_str[pos_str] = (formats->flag_Zero && !formats->point) ? '0' : ' ';
      }
      if (s21_strchr("feEgGcs", formats->specifier)) {
        tmp_str[pos_str] = (formats->flag_Zero) ? '0' : ' ';
      }
    }
  }
}

int check_specf(struct s_struct *formats, const char *format) {
  return *format == 'c' || *format == 'd' || *format == 'e' || *format == 'E' ||
                 *format == 'f' || *format == 'g' || *format == 'G' ||
                 *format == 'o' || *format == 'p' || *format == 's' ||
                 *format == 'u' || *format == 'x' || *format == 'X' ||
                 *format == '%'
             ? 1 && (formats->specifier = *format)
             : 0;
}

void set_flags(struct s_struct *formats, const char *format) {
  if (*format == ' ') formats->flag_Space = 1;
  if (*format == '+') formats->flag_Plus = 1;
  if (*format == '-') formats->flag_Minus = 1;
  if (*format == '0') formats->flag_Zero = 1;
  if (*format == '#') formats->flag_Sharp = 1;
}

void set_width_Precision(int *number, const char *format, va_list *arg) {
  if (*format == '*') {
    *number = va_arg(*arg, int);
    format++;
  } else
    *number = *number * 10 + (int)*format - 48;
}

void add_char(char *str, const char *format, int *zero_str_flag,
              struct s_struct *formats) {
  if (*zero_str_flag == 0) {
    char add[2] = {0};
    add[0] = *format;
    s21_strcat(str, add);
  } else
    formats->zero_simbol++;
}

void s21_move_string(char *tmp_str) {
  int pos = s21_strlen(tmp_str);
  tmp_str[pos + 1] = '\0';
  while (pos > 0) {
    tmp_str[pos] = tmp_str[pos - 1];
    pos--;
  }
}

void s21_reverse_string(char *str) {
  char c = 0;
  s21_size_t length = s21_strlen(str);
  for (s21_size_t i = 0; i < length / 2; i++) {
    c = str[i];
    str[i] = str[length - 1 - i];
    str[length - 1 - i] = c;
  }
}

void s21_percent(char *tmp_str, struct s_struct *formats) {
  s21_strcat(tmp_str, "%");
  s21_string_precision(formats, tmp_str);
  s21_string_flags(formats, tmp_str);
  s21_string_width(formats, tmp_str);
}

void s21_c(char *p_str, va_list *arg, struct s_struct *formats,
           int *zero_str_flag) {
  if (*zero_str_flag == 0) {
    p_str[0] = va_arg(*arg, int);
    if (p_str[0] == 0) {
      formats->zero_simbol++;
      *zero_str_flag = 1;
    }
    p_str[1] = '\0';
  } else {
    formats->zero_simbol++;
    p_str[0] = '\0';
  }
  s21_string_flags(formats, p_str);
  s21_string_width(formats, p_str);
}

int check_flags(const char *format) {
  return *format == ' ' || *format == '-' || *format == '+' || *format == '0' ||
                 *format == '#'
             ? 1
             : 0;
}

int check_lenght(const char *format) {
  return *format == 'l' || *format == 'h' || *format == 'L' ? 1 : 0;
}

int check_dig(const char *format) {
  return (int)(*format) >= 48 && (int)(*format) <= 57 ? 1 : 0;
}