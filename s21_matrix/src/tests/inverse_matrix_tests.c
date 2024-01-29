#include "unit_tests.h"

START_TEST(inverse_matrix_test_1) {
  matrix_t matrix_A, matrix_temp, matrix_result;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_result);
  double k = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = k++;
    }
  }
  matrix_result.matrix[0][0] = -2;
  matrix_result.matrix[0][1] = 1;
  matrix_result.matrix[1][0] = 1.5;
  matrix_result.matrix[1][1] = -0.5;
  int result = s21_inverse_matrix(&matrix_A, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(inverse_matrix_test_2) {
  matrix_t matrix_A, matrix_temp, matrix_result;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_result);
  double k = 4;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = k--;
    }
  }
  matrix_result.matrix[0][0] = -0.5;
  matrix_result.matrix[0][1] = 1.5;
  matrix_result.matrix[1][0] = 1;
  matrix_result.matrix[1][1] = -2;
  int result = s21_inverse_matrix(&matrix_A, &matrix_temp);
  ck_assert_int_eq(s21_eq_matrix(&matrix_result, &matrix_temp), 1);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_result);
  s21_remove_matrix(&matrix_temp);
}
END_TEST

START_TEST(inverse_matrix_test_3) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(2, 2, &matrix_A);
  matrix_A.rows = -1;
  int result = s21_inverse_matrix(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 1);
  matrix_A.rows = 2;
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(inverse_matrix_test_4) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(2, 2, &matrix_A);
  matrix_A.columns = -1;
  int result = s21_inverse_matrix(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(inverse_matrix_test_5) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(2, 3, &matrix_A);
  int result = s21_inverse_matrix(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(inverse_matrix_test_6) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(3, 2, &matrix_A);
  int result = s21_inverse_matrix(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(inverse_matrix_test_7) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(3, 3, &matrix_A);
  double k = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_A.matrix[i][j] = k++;
    }
  }
  int result = s21_inverse_matrix(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(inverse_matrix_test_8) {
  matrix_t matrix_A, matrix_temp;
  s21_create_matrix(3, 3, &matrix_A);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_A.matrix[i][j] = 0;
    }
  }
  int result = s21_inverse_matrix(&matrix_A, &matrix_temp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
}
END_TEST

Suite *test_inverse_matrix(void) {
  Suite *s = suite_create("s21_inverse_matrix");
  TCase *tc = tcase_create("inverse_matrix_tc");

  tcase_add_test(tc, inverse_matrix_test_1);
  tcase_add_test(tc, inverse_matrix_test_2);
  tcase_add_test(tc, inverse_matrix_test_3);
  tcase_add_test(tc, inverse_matrix_test_4);
  tcase_add_test(tc, inverse_matrix_test_5);
  tcase_add_test(tc, inverse_matrix_test_6);
  tcase_add_test(tc, inverse_matrix_test_7);
  tcase_add_test(tc, inverse_matrix_test_8);

  suite_add_tcase(s, tc);
  return s;
}