#include "header.h"
matrix_t MatrixCreate(int height, int width) {
  double **arr;
  int i;
  matrix_t c = { 0, height, width };
  arr = (double**)malloc(width * sizeof(double));
  for (i = 0; i < width; i++)
    arr[i] = (double*)malloc(height * sizeof(double));
  c.matrix = arr;
  return c;
}
void MatrixDestroy(matrix_t a) {
  int i;
  for (i = 0; i < a.width; i++) {
    free(a.matrix[i]);
  }
  free(a.matrix);
}
matrix_t MatrixAdd(matrix_t a, matrix_t b) {
  int i, j;
  matrix_t c;
  c = MatrixCreate (a.height, a.width);
  //assert (a.height == b.height && a.width == b.width);
  if (a.height != b.height || a.width != b.width){
	  c.matrix = NULL;
	  return c;
  }
  for (i = 0; i < a.width; i++) {
    for (j = 0; j < b.height; j++) {
      c.matrix ELEMENT(i,j) = a.matrix ELEMENT(i,j) + b.matrix ELEMENT(i,j);
    }
  }
  return c;
}
matrix_t MatrixSub(matrix_t a, matrix_t b) {
  int i, j;
  matrix_t c;
  c = MatrixCreate(a.height, a.width);
  //assert(a.height == b.height && a.width == b.width);
  if (a.height != b.height || a.width != b.width){
	  c.matrix = NULL;
	  return c;
  }
  for (i = 0; i < a.width; i++) {
    for (j = 0; j < b.height; j++) {
      c.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
    }
  }
  return c;
}
matrix_t MatrixMul (matrix_t a, matrix_t b) {
  int i, j, k;
  matrix_t c;
  c = MatrixCreate(a.height, b.width);
  //assert(a.width == b.height);
  if (a.width != b.height){
	  c.matrix = NULL;
	  return c;
  }
  for (i = 0; i < a.height; i++) {
    for (j = 0; j < b.width; j++) {
      c.matrix[i][j] = 0;
      for(k = 0; k < a.width; k++)
        c.matrix[i][j] += b.matrix[i][k] * a.matrix[k][j];
    }
  }
  return c;
}
matrix_t MatrixMulDouble(matrix_t a, double number) {
  int i, j;
  matrix_t c;
  c = MatrixCreate(a.height, a.width);
  for (i = 0; i < a.width; i++) {
    for (j = 0; j < a.height; j++) {
      c.matrix[i][j] = a.matrix[i][j] * number;
    }
  }
  return c;
}

double MatrixTrance(matrix_t a) {
  double result = 0;
  int i;
  //assert(a.height == a.width);
  if (a.height != a.width)
	  return 0;
  for (i = 0; i < a.height; i++)
    result += a.matrix[i][i];
  return result;
}
matrix_t MatrixTranspose(matrix_t a) {
  int i, j;
  matrix_t c = MatrixCreate (a.width, a.height);
  for (i = 0; i < a.height; i++) {
    for (j = 0; j < a.width; j++)
      c.matrix[i][j] = a.matrix[j][i];
  }
  return c;
}
void MatrixSetZero(matrix_t a) {
  int i, j;
  for (i = 0; i < a.width; i++) {
    for (j = 0; j < a.height; j++)
      a.matrix[i][j] = 0;
  }
}
void MatrixSetIdentity(matrix_t a) {
  int i;
  //assert(a.height == a.width);
  if (a.height != a.width){
	  a.matrix = NULL;
	  return;
  }
  MatrixSetZero(a);
  for (i = 0; i < a.height; i++)
    a.matrix[i][i] = 1;
}
