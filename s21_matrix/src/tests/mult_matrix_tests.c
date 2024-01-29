#include "unit_tests.h"

START_TEST(mult_matrix_test_1) {
  matrix_t matrix_A, matrix_B, matrix_result, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(1, 1, &matrix_B);
  s21_create_matrix(1, 1, &matrix_result);
  matrix_A.matrix[0][0] = 5;
  matrix_B.matrix[0][0] = 3;
  matrix_result.matrix[0][0] = 15;
  int result = s21_mult_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  matrix_t matrix_A, matrix_B, matrix_result, matrix_temp;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  s21_create_matrix(2, 2, &matrix_result);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = i + j;
      matrix_B.matrix[i][j] = i + j;
    }
  }
  matrix_result.matrix[0][0] = 1;
  matrix_result.matrix[0][1] = 2;
  matrix_result.matrix[1][0] = 2;
  matrix_result.matrix[1][1] = 5;
  int result = s21_mult_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(mult_matrix_test_3) {
  matrix_t matrix_A, matrix_B, matrix_result, matrix_temp;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  s21_create_matrix(2, 2, &matrix_result);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = 2 * (i + j);
      matrix_B.matrix[i][j] = 2 * (i + j);
    }
  }
  matrix_result.matrix[0][0] = 4;
  matrix_result.matrix[0][1] = 8;
  matrix_result.matrix[1][0] = 8;
  matrix_result.matrix[1][1] = 20;
  int result = s21_mult_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(mult_matrix_test_4) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  matrix_A.columns = -1;
  int result = s21_mult_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(mult_matrix_test_5) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  matrix_A.rows = -1;
  int result = s21_mult_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 1);
  matrix_A.rows = 2;
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(mult_matrix_test_6) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(2, 1, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  int result = s21_mult_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(mult_matrix_test_7) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(2, 5, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  int result = s21_mult_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

Suite *test_mult_matrix(void) {
  Suite *s = suite_create("s21_mult_matrix");
  TCase *tc = tcase_create("mult_matrix_tc");

  tcase_add_test(tc, mult_matrix_test_1);
  tcase_add_test(tc, mult_matrix_test_2);
  tcase_add_test(tc, mult_matrix_test_3);
  tcase_add_test(tc, mult_matrix_test_4);
  tcase_add_test(tc, mult_matrix_test_5);
  tcase_add_test(tc, mult_matrix_test_6);
  tcase_add_test(tc, mult_matrix_test_7);

  suite_add_tcase(s, tc);
  return s;
}