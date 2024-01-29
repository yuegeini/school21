#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (rows < 1 || columns < 1) {
    error = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A->columns != B->columns || A->rows != B->rows) {
    result = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (A->matrix[i][j] != B->matrix[i][j]) {
          result = FAILURE;
          break;
        }
      }
    }
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A->columns < 1 || B->columns < 1 || A->rows < 1 || B->rows < 1) {
    error = 1;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    error = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A->columns < 1 || B->columns < 1 || A->rows < 1 || B->rows < 1) {
    error = 1;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    error = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (A->columns < 1 || A->rows < 1) {
    error = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A->columns < 1 || B->columns < 1 || A->rows < 1 || B->rows < 1) {
    error = 1;
  } else if (A->columns != B->rows) {
    error = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        double sum = 0;
        for (int h = 0; h < A->columns; h++) {
          sum += A->matrix[i][h] * B->matrix[h][j];
        }
        result->matrix[i][j] = sum;
      }
    }
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A->columns < 1 || A->rows < 1) {
    error = 1;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A->columns < 1 || A->rows < 1) {
    error = 1;
  } else if (A->columns != A->rows) {
    error = 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t newA;
        s21_get_minor(A, &newA, i, j);
        int degree = 1;
        if ((i + j) % 2) degree = -1;
        result->matrix[i][j] = degree * s21_determinant_rec(&newA);
        s21_remove_matrix(&newA);
        degree = -degree;
      }
    }
  }
  return error;
}

void s21_get_minor(matrix_t *A, matrix_t *result, int nrow, int ncol) {
  s21_create_matrix(A->rows - 1, A->columns - 1, result);
  int offsetRow = 0;
  for (int i = 0; i < A->rows - 1; i++) {
    if (i == nrow) {
      offsetRow = 1;
    }
    int offsetCol = 0;
    for (int j = 0; j < A->rows - 1; j++) {
      if (j == ncol) {
        offsetCol = 1;
      }
      result->matrix[i][j] = A->matrix[i + offsetRow][j + offsetCol];
    }
  }
}

double s21_determinant_rec(matrix_t *A) {
  double det = 0;
  double degree = 1;

  if (A->rows == 1) {
    return A->matrix[0][0];
  } else if (A->rows == 2) {
    return A->matrix[0][0] * A->matrix[1][1] -
           A->matrix[0][1] * A->matrix[1][0];
  } else {
    matrix_t newA;
    for (int j = 0; j < A->rows; j++) {
      s21_get_minor(A, &newA, 0, j);
      det = det + (degree * A->matrix[0][j] * s21_determinant_rec(&newA));
      degree = -degree;
      s21_remove_matrix(&newA);
    }
  }
  return det;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (A->columns < 1 || A->rows < 1) {
    error = 1;
  } else if (A->rows != A->columns) {
    error = 2;
  } else {
    *result = s21_determinant_rec(A);
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A->columns < 1 || A->rows < 1) {
    error = 1;
  } else if (A->rows != A->columns) {
    error = 2;
  } else {
    double det = s21_determinant_rec(A);
    if (det == 0) {
      error = 2;
    } else {
      matrix_t newA, newA1;

      s21_calc_complements(A, &newA);
      s21_transpose(&newA, &newA1);
      s21_mult_number(&newA1, 1 / det, result);

      s21_remove_matrix(&newA);
      s21_remove_matrix(&newA1);
    }
  }
  return error;
}