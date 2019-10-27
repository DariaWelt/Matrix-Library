#include "header.h"

typedef struct {
  long double ** first;
  long double ** change;
  int size;
} doubleMatrix_t;
long double NOK(long double a, long double b); 
static long double Subtract(doubleMatrix_t p, int i, int j) {
  long double b, c, nok;
  int k;
  nok = NOK(p.first[i][j], p.first[j][j]);
  b = nok / p.first[i][j];
  c = nok / p.first[j][j];
  for (k = 0; k < p.size; k++) {
    p.first[i][k] = b * p.first[i][k] - c * p.first[j][k];
    p.change[i][k] = b * p.change[i][k] - c * p.change[j][k];
  }
  return b;
}
static void Construct(doubleMatrix_t p , int i, int i2) {
  int k;
  long double count;
  for (k = 0; k < p.size; k++) {
    count = p.first[i][k];
    p.first[i][k] = p.first[i2][k];
    p.first[i2][k] = count;

    count = p.change[i][k];
    p.change[i][k] = p.change[i2][k];
    p.change[i2][k] = count;
  }
}
void Reduce(doubleMatrix_t a, int i) {
  int j;
  long double number = a.first[i][i];
  for (i; i < a.size; i++) {
    for (j = 0; j < a.size; j++) {
      a.first[i][j] /= number;
      a.change[i][j] /= number;
    }
  }
}
void ChangeMatrix(doubleMatrix_t* a) {
  int i, j, schet, i2;
  long double koeff = 1;
  for (j = 0; j < (a->size - 1); j++) {
    for (i = j + 1; i < a->size; i++) {
      if (a->first[i][j] != 0) {
        schet = 0;
        i2 = i;
        while ((a->first[j][j] == 0) && (schet < a->size)) {
          Construct(*a, j, i2);
          koeff *= -1;
          schet++;
          i2++;
        }
      }
      if (a->first[i][j] != 0)
        koeff = koeff * Subtract(*a, i, j);
    }
  }
  for (i = 0; i < (a->size - 1); i++) {
    for (j = i + 1; j < a->size; j++) {
      if (a->first[i][j] != 0) {
        schet = 0;
        i2 = i;
        while ((a->first[j][j] == 0) && (schet < a->size)) {
          Construct(*a, j, i2);
          koeff *= -1;
          schet++;
          i2++;
        }
      }

      if (a->first[i][j] != 0)
        koeff = koeff * Subtract(*a, i, j);
    }
  }
  for (i = 0; i < a->size; i++) {
    if (a->first[i][i] == 0) {
		a->size = 0;
		return;
    }
    if (a->first[i][i] != 1)
      Reduce(*a, i);

  }
}
matrix_t ReverseMatrix(matrix_t a) {
  matrix_t arg = {0};
  long double** identity = NULL;
  long double** tmp = NULL;
  int i, j;
  doubleMatrix_t matrix = {NULL, NULL, a.height};
  if (a.height != a.width)
	  return a;
  arg = MatrixCreate(a.width, a.width);
  for (i = 0; i < a.width; ++i){
	  for (j = 0; j < a.width; ++j)
		  arg.matrix[i][j] = a.matrix[i][j];
  }
  matrix.first = arg.matrix;
  identity = (long double**)malloc(a.height * sizeof(long double*));
  for (i = 0; i < a.height; i++)
      identity[i] = (long double*)malloc(a.height * sizeof(long double));
  for (i = 0; i < a.height; i++) {
	  for (j = 0; j < a.height; j++)
		  identity[i][j] = 0;
	  identity[i][i] = 1;
  }
  matrix.change = identity;
  ChangeMatrix(&matrix);
  if (matrix.size != 0){
	tmp = a.matrix;
  }
  for (i = 0; i < a.height; i++) {
    free (tmp[i]);
  }
  free (tmp);
  MatrixDestroy(arg);
  a.matrix = matrix.change;
  return a;
}