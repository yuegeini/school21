#include "unit_tests.h"

START_TEST(det_test_1) {
  matrix_t matrix_A;
  s21_create_matrix(2, 2, &matrix_A);
  double k = 1;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = k++;
    }
  }
  double res = -2;
  double tmp;
  int result = s21_determinant(&matrix_A, &tmp);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq(res, tmp);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(det_test_2) {
  matrix_t matrix_A;
  s21_create_matrix(3, 3, &matrix_A);
  double k = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_A.matrix[i][j] = k++;
    }
  }
  double res = 0;
  double tmp;
  int result = s21_determinant(&matrix_A, &tmp);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq(res, tmp);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(det_test_3) {
  matrix_t matrix_A;
  s21_create_matrix(3, 2, &matrix_A);
  double tmp;
  int result = s21_determinant(&matrix_A, &tmp);
  ck_assert_int_eq(result, 2);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(det_test_4) {
  matrix_t matrix_A;
  s21_create_matrix(3, 2, &matrix_A);
  matrix_A.columns = -1;
  double tmp;
  int result = s21_determinant(&matrix_A, &tmp);
  ck_assert_int_eq(result, 1);
  s21_remove_matrix(&matrix_A);
}
END_TEST

START_TEST(det_test_5) {
  matrix_t matrix_A;
  s21_create_matrix(3, 2, &matrix_A);
  matrix_A.rows = -1;
  double tmp;
  int result = s21_determinant(&matrix_A, &tmp);
  ck_assert_int_eq(result, 1);
  matrix_A.rows = 3;
  s21_remove_matrix(&matrix_A);
}
END_TEST

Suite *test_det(void) {
  Suite *s = suite_create("s21_det");
  TCase *tc = tcase_create("det_tc");

  tcase_add_test(tc, det_test_1);
  tcase_add_test(tc, det_test_2);
  tcase_add_test(tc, det_test_3);
  tcase_add_test(tc, det_test_4);
  tcase_add_test(tc, det_test_5);

  suite_add_tcase(s, tc);
  return s;
}