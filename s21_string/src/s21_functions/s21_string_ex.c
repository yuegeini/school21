#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  s21_size_t i = 0, j = s21_strlen(str);
  char *res = calloc(j, sizeof(char *));
  for (; i < j; i++) {
    if (str[i] != '\0' && str[i] > 96 && str[i] < 123)
      res[i] = str[i] - 32;
    else
      res[i] = str[i];
  }
  return res;
}

void *s21_to_lower(const char *str) {
  s21_size_t i = 0, j = s21_strlen(str);
  char *res = calloc(j, sizeof(char *));
  for (; i < j; i++) {
    if (str[i] != '\0' && str[i] > 64 && str[i] < 91)
      res[i] = str[i] + 32;
    else
      res[i] = str[i];
  }
  return res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int check = 0;
  char *temp = S21_NULL;
  if (src && str) {
    temp =
        (char *)malloc((s21_strlen(src) + s21_strlen(str)) * sizeof(char) + 1);
    if (temp && s21_strlen(src) >= start_index) {
      s21_size_t i = 0;
      while (*src) {
        if (i == start_index) {
          while (*str) {
            temp[i++] = *str++;
          }
        }
        temp[i++] = *src++;
      }
      temp[i] = '\0';
      check = 1;
    } else {
      if (temp) free(temp);
      temp = S21_NULL;
    }
  }

  return check ? temp : S21_NULL;
}
