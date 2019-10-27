#include "header.h"
long double NOK(long double a, long double b) {
  double A = a, B = b;
  if (a < 0)
    a = -a;
  if (b < 0)
    b = -b;
  while ((int)a * 1000000 != (int)b*1000000) {
    if (a > b)
      a -= b;
    else
      b -= a;
  }

  return (A*(B / a));
}
static long double Subtract(long double **p, int i, int j, int size) {
  long double b, c, nok;
  int k;
  nok = NOK(p[i][j], p[j][j]);
  b = nok / p[i][j];
  c = nok / p[j][j];
  for (k = 0; k < size; k++)
    p[i][k] = b * p[i][k] - c * p[j][k];
  return b;
}
static void Construct(long double ** p, int i, int i2, int size){
  int k;
  long double count;
  for (k = 0; k < size; k++){
    count = p[i][k];
    p[i][k] = p[i2][k];
    p[i2][k] = count;
  }
}
long double MatrixDeterminant(matrix_t argument) {
  matrix_t a;
  int i, j, schet, i2;
  long double koeff = 1, rez = 1;
  if(argument.height != argument.width)
	  return 0;//NAN;
  a = MatrixCreate(argument.width, argument.width);
  for (i = 0; i < argument.width; ++i){
	  for (j = 0; j < argument.width; ++j)
		  a.matrix[i][j] = argument.matrix[i][j];
  }
  for (j = 0; j < (argument.width - 1); j++) {
    for (i = j + 1; i < argument.width; i++) {
      if (a.matrix[i][j] != 0) {
        schet = 0;
        i2 = i;
        while ((a.matrix[j][j] == 0) && (schet < a.width)) {
          Construct(a.matrix, j, i2, a.width);
          koeff *= -1;
          schet++;
          i2++;
        }
      }
      if (a.matrix[i][j] != 0)
        koeff = koeff * Subtract(a.matrix, i, j, a.width);
    }
  }
  for (i = 0; i < argument.width; i++)
    rez = rez * a.matrix[i][i];
  rez = rez / koeff;
  MatrixDestroy(a);
  return rez;
}
