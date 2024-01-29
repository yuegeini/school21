#ifndef UNIT_H
#define UNIT_H

#include <check.h>
#include <stdio.h>

#include "../s21_matrix.h"

Suite *test_eq_matrix(void);
Suite *test_sum_matrix(void);
Suite *test_sub_matrix(void);
Suite *test_mult_number(void);
Suite *test_mult_matrix(void);
Suite *test_transpose(void);
Suite *test_det(void);
Suite *test_calc_complements(void);
Suite *test_inverse_matrix(void);

#endif