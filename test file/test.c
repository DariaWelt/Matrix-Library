#include <locale.h>
#include "header.h"
#pragma warning (disable: 4996)

int main() {
  matrix_t a;
  matrix_t b;
  matrix_t c;
  FILE * stream = stdin;
  setlocale(LC_CTYPE, "Russian");
  
  printf("Вызываем функцию MatrixSetIdentity \nВ данном примере - заполнение единичной матрицы 4х4:\n");
  a = MatrixCreate(4, 4);
  MatrixSetIdentity (a);
  MatrixWrite((FILE*)stdout, a);
  MatrixDestroy(a);

  printf("Вызываем функцию MatrixSetZero \nВ данном примере заполнение нулевой матрицы 4х4:\n");
  a = MatrixCreate(4, 4);
  MatrixSetZero (a);
  MatrixWrite((FILE*)stdout, a);
  MatrixDestroy(a);

  printf("Введите первую матрицу произвольного размера в формате {{a, b},{c, d}}\n");
  a = MatrixRead(stream);
  printf("Вызываем функцию MatrixTranspose\nВ данном примере транспонирование исходной матрицы:\n");
  b = MatrixTranspose(a);
  MatrixWrite((FILE*)stdout, b);

  printf("Введите вторую матрицу того же размера в формате {{a, b},{c, d}}\n");
  c = MatrixRead(stream);
  MatrixDestroy(a);
  printf("Вызываем функцию MatrixMul\n");
  printf("В данном примере результат умножения первой транспонированной матрицы на вторую, только что введенную:\n");
  a = MatrixMul ( b, c);
  MatrixWrite((FILE*)stdout, a);
  MatrixDestroy(b);
  MatrixDestroy(c);

  printf("Вызываем функцию MatrixDeterminant\n");
  printf("Определитель матрицы - результата выражения = ");
  printf("%lf\n", MatrixDeterminant(a));
  MatrixWrite((FILE*)stdout, a);

  printf("Вызываем функцию MatrixMulDouble\n");
  printf("В данном примере умножаем на число 5 матрицу - результат умножения:\n");
  b = MatrixMulDouble(a, 5);
  MatrixWrite((FILE*)stdout, b);

  MatrixDestroy(b);
  MatrixDestroy(a);
  printf("Введите первую матрицу произвольного размера в формате {{a, b},{c, d}}\n");
  a = MatrixRead(stream);
  printf("Введите вторую матрицу того же размера в формате {{a, b},{c, d}}\n");
  b = MatrixRead(stream);

  printf("\nВызываем функцию MatrixAdd\n");
  printf("В данном примере складываем две введенные матрицы:\n");
  c = MatrixAdd(a, b);
  MatrixWrite((FILE*)stdout, c);
  MatrixDestroy(c);

  printf("Вызываем функцию MatrixSub\n");
  printf("В данном примере вычитаем из второй матрицы первую:\n");
  c = MatrixSub(b, a);
  MatrixWrite((FILE*)stdout, c);
  MatrixDestroy(a);
  MatrixDestroy(b);
  MatrixDestroy(c);
  return 0;
}
