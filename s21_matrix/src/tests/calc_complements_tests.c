#include "unit_tests.h"

START_TEST(calc_complements_test_1) {
  matrix_t matrix_A, matrix_temp, matrix_result;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_result);
  double k = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = k++;
    }
  }
  matrix_result.matrix[0][0] = 4;
  matrix_result.matrix[0][1] = -3;
  matrix_result.matrix[1][0] = -2;
  matrix_result.matrix[1][1] = 1;
  int result = s21_calc_complements(&matrix_A, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_temp);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(calc_complements_test_2) {
  matrix_t matrix_A, matrix_temp, matrix_result;
  s21_create_matrix(3, 3, &matrix_A);
  s21_create_matrix(3, 3, &matrix_result);
  double k = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_A.matrix[i][j] = k++;
    }
  }
  matrix_A.matrix[2][2] = 0;
  matrix_result.matrix[0][0] = -48;
  matrix_result.matrix[0][1] = 42;
  matrix_result.matrix[0][2] = -3;
  matrix_result.matrix[1][0] = 24;
  matrix_result.matrix[1][1] = -21;
  matrix_result.matrix[1][2] = 6;
  matrix_result.matrix[2][0] = -3;
  matrix_result.matrix[2][1] = 6;
  matrix_result.matrix[2][2] = -3;
  int result = s21_calc_complements(&matrix_A, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_temp);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(calc_complements_test_3) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(2, 2, &matrix_A);
  matrix_A.rows = -1;
  int result = s21_calc_complements(&matrix_A, &matrix_temp);
  matrix_A.rows = 2;
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(calc_complements_test_4) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(2, 2, &matrix_A);
  matrix_A.columns = -1;
  int result = s21_calc_complements(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(calc_complements_test_5) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(3, 2, &matrix_A);
  int result = s21_calc_complements(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
}
END_TEST

Suite *test_calc_complements(void) {
  Suite *s = suite_create("s21_calc_complements");
  TCase *tc = tcase_create("calc_complements_tc");

  tcase_add_test(tc, calc_complements_test_1);
  tcase_add_test(tc, calc_complements_test_2);
  tcase_add_test(tc, calc_complements_test_3);
  tcase_add_test(tc, calc_complements_test_4);
  tcase_add_test(tc, calc_complements_test_5);

  suite_add_tcase(s, tc);
  return s;
}