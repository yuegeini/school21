#include "unit_tests.h"

START_TEST(transpose_test_1) {
  matrix_t matrix_A, matrix_temp, matrix_result;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_result);
  double k = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = k;
      matrix_result.matrix[j][i] = k++;
    }
  }
  int result = s21_transpose(&matrix_A, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_temp);
  s21_remove_matrix(&matrix_result);
}
END_TEST

START_TEST(transpose_test_2) {
  matrix_t matrix_A, matrix_temp, matrix_result;
  s21_create_matrix(3, 3, &matrix_A);
  s21_create_matrix(3, 3, &matrix_result);
  double k = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = k;
      matrix_result.matrix[j][i] = k++;
    }
  }
  int result = s21_transpose(&matrix_A, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_temp);
  s21_remove_matrix(&matrix_result);
}
END_TEST

START_TEST(transpose_test_3) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(3, 3, &matrix_A);
  matrix_A.columns = -1;
  int result = s21_transpose(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(transpose_test_4) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(3, 3, &matrix_A);
  matrix_A.rows = -1;
  int result = s21_transpose(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 1);
  matrix_A.rows = 3;
  s21_remove_matrix(&matrix_A);
}
END_TEST

Suite *test_transpose(void) {
  Suite *s = suite_create("s21_transpose");
  TCase *tc = tcase_create("transpose_tc");

  tcase_add_test(tc, transpose_test_1);
  tcase_add_test(tc, transpose_test_2);
  tcase_add_test(tc, transpose_test_3);
  tcase_add_test(tc, transpose_test_4);

  suite_add_tcase(s, tc);
  return s;
}