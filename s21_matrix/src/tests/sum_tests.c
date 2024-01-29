#include "unit_tests.h"

START_TEST(sum_matrix_test_1) {
  matrix_t matrix_A, matrix_B, matrix_result, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(1, 1, &matrix_B);
  s21_create_matrix(1, 1, &matrix_result);
  matrix_A.matrix[0][0] = 92457.23;
  matrix_B.matrix[0][0] = 3131.3131;
  matrix_result.matrix[0][0] = 95588.5431;
  int result = s21_sum_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(sum_matrix_test_2) {
  matrix_t matrix_A, matrix_B, matrix_result, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(1, 1, &matrix_B);
  s21_create_matrix(1, 1, &matrix_result);
  matrix_A.matrix[0][0] = 1;
  matrix_B.matrix[0][0] = 1;
  matrix_result.matrix[0][0] = 2;
  int result = s21_sum_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(sum_matrix_test_3) {
  matrix_t matrix_A, matrix_B, matrix_result, matrix_temp;
  s21_create_matrix(3, 3, &matrix_A);
  s21_create_matrix(3, 3, &matrix_B);
  s21_create_matrix(3, 3, &matrix_result);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_A.matrix[i][j] = i + j;
      matrix_B.matrix[i][j] = (i + j) * 2;
      matrix_result.matrix[i][j] = i + j + (i + j) * 2;
    }
  }
  int result = s21_sum_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(sum_matrix_test_4) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  int result = s21_sum_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(sum_matrix_test_5) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(2, 3, &matrix_A);
  s21_create_matrix(5, 6, &matrix_B);
  int result = s21_sum_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(sum_matrix_test_6) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(3, 3, &matrix_A);
  s21_create_matrix(7, 7, &matrix_B);
  int result = s21_sum_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(sum_matrix_test_7) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  matrix_A.columns = -1;
  int result = s21_sum_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(sum_matrix_test_8) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  matrix_B.columns = -1;
  int result = s21_sum_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(sum_matrix_test_9) {
  matrix_t matrix_A, matrix_B, matrix_temp;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  matrix_A.rows = 0;
  matrix_B.rows = 0;
  int result = s21_sum_matrix(&matrix_A, &matrix_B, &matrix_temp);
  ck_assert_int_eq(result, 1);
  matrix_A.rows = 1;
  matrix_B.rows = 2;
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

Suite *test_sum_matrix(void) {
  Suite *s = suite_create("s21_sum_matrix");
  TCase *tc = tcase_create("sum_matrix_tc");

  tcase_add_test(tc, sum_matrix_test_1);
  tcase_add_test(tc, sum_matrix_test_2);
  tcase_add_test(tc, sum_matrix_test_3);
  tcase_add_test(tc, sum_matrix_test_4);
  tcase_add_test(tc, sum_matrix_test_5);
  tcase_add_test(tc, sum_matrix_test_6);
  tcase_add_test(tc, sum_matrix_test_7);
  tcase_add_test(tc, sum_matrix_test_8);
  tcase_add_test(tc, sum_matrix_test_9);

  suite_add_tcase(s, tc);
  return s;
}