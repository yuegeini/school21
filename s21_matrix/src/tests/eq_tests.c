#include "unit_tests.h"

START_TEST(eq_matrix_test_1) {
  matrix_t matrix_A, matrix_B;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(1, 1, &matrix_B);
  matrix_A.matrix[0][0] = 1;
  matrix_B.matrix[0][0] = 1;
  ck_assert_int_eq(s21_eq_matrix(&matrix_A, &matrix_B), 1);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(eq_matrix_test_2) {
  matrix_t matrix_A, matrix_B;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = i + j;
      matrix_B.matrix[i][j] = i + j;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix_A, &matrix_B), 1);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(eq_matrix_test_3) {
  matrix_t matrix_A, matrix_B;
  s21_create_matrix(3, 4, &matrix_A);
  s21_create_matrix(3, 4, &matrix_B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      matrix_A.matrix[i][j] = i + j;
      matrix_B.matrix[i][j] = i + j;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix_A, &matrix_B), 1);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(eq_matrix_test_4) {
  matrix_t matrix_A, matrix_B;
  s21_create_matrix(1, 1, &matrix_A);
  s21_create_matrix(1, 1, &matrix_B);
  matrix_A.matrix[0][0] = 2;
  matrix_B.matrix[0][0] = 1;
  ck_assert_int_eq(s21_eq_matrix(&matrix_A, &matrix_B), 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(eq_matrix_test_5) {
  matrix_t matrix_A, matrix_B;
  s21_create_matrix(2, 2, &matrix_A);
  s21_create_matrix(2, 2, &matrix_B);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_A.matrix[i][j] = i + j;
      matrix_B.matrix[i][j] = i + j;
    }
  }
  matrix_B.matrix[1][1] = 0;
  ck_assert_int_eq(s21_eq_matrix(&matrix_A, &matrix_B), 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

START_TEST(eq_matrix_test_6) {
  matrix_t matrix_A, matrix_B;
  s21_create_matrix(2, 3, &matrix_A);
  s21_create_matrix(3, 2, &matrix_B);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      matrix_A.matrix[i][j] = i + j;
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      matrix_B.matrix[i][j] = i + j;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix_A, &matrix_B), 0);
  s21_remove_matrix(&matrix_A);
  s21_remove_matrix(&matrix_B);
}
END_TEST

Suite *test_eq_matrix(void) {
  Suite *s = suite_create("s21_eq_matrix");
  TCase *tc = tcase_create("eq_matrix_tc");

  tcase_add_test(tc, eq_matrix_test_1);
  tcase_add_test(tc, eq_matrix_test_2);
  tcase_add_test(tc, eq_matrix_test_3);
  tcase_add_test(tc, eq_matrix_test_4);
  tcase_add_test(tc, eq_matrix_test_5);
  tcase_add_test(tc, eq_matrix_test_6);

  suite_add_tcase(s, tc);
  return s;
}
