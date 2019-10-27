#include "header.h"
unsigned char* MatrixFormat(matrix_t matrix) {
  unsigned char * string = 0, * m = 0;
  char number[100] = { 0 };
  int i = 0, k = 0, numberSize, height = 1, j;
  // запятые между скобками + запятые между числами + количество внутренних скобок +крайние скобки + количество чисел 
  //далее если число > 1 цифры - перевыделяем дополнительную память
  int length = (matrix.width - 1) + (matrix.height - 1) * matrix.width + (matrix.width * 2) + 2 + 1;
  string = (unsigned char*)malloc(length + 1 * sizeof(unsigned char)); // +1 на символ \0
  string[k++] = '{';
  for (i = 0, k; i < matrix.width; i++) {
    string[k++] = '{';
    for (j = 0; j < matrix.height; j++) {
      numberSize = sprintf_s(number, 100, "%g", matrix.matrix[i][j]);
      m = (unsigned char*)realloc(string, length + numberSize);
        if (m == NULL) {
          free(string);
          return 0;
        }
        string = m;
        m = NULL;
        length += numberSize;
        memcpy(string + k, number, numberSize);
        k += numberSize;
        if (j < matrix.height - 1)
          string[k++] = ',';
    }
    string[k++] = '}';
    if (i < matrix.width - 1)
      string[k++] = ',';
  }
  string[k++] = '}';
  string[k++] = 0;
  return string;
}
void MatrixWrite(FILE * stream, matrix_t matrix) {
  unsigned char * string = NULL;
  string = MatrixFormat(matrix);
  if (string == NULL)
    return;
  fprintf(stream, "%s\n", string);
  free(string);
}
void MatrixPrint(matrix_t a) {
  int i, j;
  for (i = 0; i < a.width; i++) {
    for (j = 0; j < a.height; j++) {
      printf("%lf ", a.matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}