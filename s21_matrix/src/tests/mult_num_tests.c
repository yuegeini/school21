#include "unit_tests.h"

START_TEST(mult_number_test_1) {
  matrix_t matrix_A, matrix_result, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(1, 1, &matrix_result);
  matrix_A.matrix[0][0] = 5;
  matrix_result.matrix[0][0] = 15;
  int result = s21_mult_number(&matrix_A, 3, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(mult_number_test_2) {
  matrix_t matrix_A, matrix_result, matrix_temp;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_result);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = i + j;
      matrix_result.matrix[i][j] = (i + j) * 2;
    }
  }
  int result = s21_mult_number(&matrix_A, 2, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(mult_number_test_3) {
  matrix_t matrix_A, matrix_result, matrix_temp;
  s21_create_matrix(3, 4, &matrix_A);
  s21_create_matrix(3, 4, &matrix_result);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_A.matrix[i][j] = i + j;
      matrix_result.matrix[i][j] = (i + j) * 10.5;
    }
  }
  int result = s21_mult_number(&matrix_A, 10.5, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(mult_number_test_4) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  matrix_A.columns = 0;
  int result = s21_mult_number(&matrix_A, 5, &matrix_temp);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(mult_number_test_5) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  matrix_A.rows = -50;
  int result = s21_mult_number(&matrix_A, 5, &matrix_temp);
  ck_assert_int_eq(result, 1);
  matrix_A.rows = 1;
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(mult_number_test_6) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  matrix_A.columns = -100;
  matrix_A.rows = -1;
  int result = s21_mult_number(&matrix_A, 5, &matrix_temp);
  ck_assert_int_eq(result, 1);
  matrix_A.rows = 1;
  s21_remove_matrix(&matrix_A);
}
END_TEST

Suite *test_mult_number(void) {
  Suite *s = suite_create("s21_mult_number");
  TCase *tc = tcase_create("mult_number_tc");

  tcase_add_test(tc, mult_number_test_1);
  tcase_add_test(tc, mult_number_test_2);
  tcase_add_test(tc, mult_number_test_3);
  tcase_add_test(tc, mult_number_test_4);
  tcase_add_test(tc, mult_number_test_5);
  tcase_add_test(tc, mult_number_test_6);

  suite_add_tcase(s, tc);
  return s;
}