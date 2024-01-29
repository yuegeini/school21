#include "unit_tests.h"

int main(void) {
  int failed = 0;
  Suite *matrix_tests[] = {test_eq_matrix(),
                           test_sum_matrix(),
                           test_sub_matrix(),
                           test_mult_number(),
                           test_mult_matrix(),
                           test_transpose(),
                           test_det(),
                           test_calc_complements(),
                           test_inverse_matrix(),
                           NULL};
  for (int i = 0; matrix_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(matrix_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
