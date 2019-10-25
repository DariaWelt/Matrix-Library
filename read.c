#include "header.h"
unsigned char* ReadString (FILE * stream, int* end, int* error) {
  unsigned char *string, *m;
  int symbol = 0;
  int i;
  if ((symbol = getc(stream)) == -1)
    *end = -1;
  string = (unsigned char*)calloc(10, sizeof(unsigned char));
  //string = 0;
  if (string == NULL) {
    //ERROR: not enough memory
    while (getc(stream) != '\n' && getc(stream) != -1);
    *error = 1;
    return 0;
  }
  string[0] = (unsigned char)symbol;
  for (i = 1; symbol != '\n' && symbol != -1; i++) {
    if ((i % 10) == 9) {
      m = (unsigned char*)realloc(string, (10 + i + 1) * sizeof(unsigned char));
      if (m != NULL)
        string = m;
      else {
        string[i] = 0;
        *error = 1;
        while (symbol != '\n' && symbol != -1)
          symbol = (int)getc(stream);
        return string;
      }
      m = NULL;
    }
    symbol = (int)getc(stream);
    string[i] = (unsigned char)symbol;
  }
  if (symbol == -1)
    *end = -1;
  string[i - 1] = 0;
  return string;
}
double BuildNumber(char const * string, int begin, int integer, int fract) {
  int i = 1, j = begin;
  double power, number = 0;
  if (string[integer + j - 1] == '.' || fract > 0)
    j--;
  while (i <= integer) {
    power = pow(10, integer - i);
    number += (string[j] - 48)*power;
    j++;
    i++;
  }

  //Прибавляем дробную часть числа
  i = 1;
  j++;
  while (i <= fract) {
    power = pow(10, -i);
    number += (string[j] - 48)*power;
    j++;
    i++;
  }
  return number;
}
double ReadNumber(char const * string, int *count) {
  int i = *count;
  int integer = 0, fract = 0;
  for (i, integer = 0; isdigit(string[i]); i++, integer++); //смотрим, сколько символов соответствует целой части
  if (string[i] == '.') {
    i++;
    for (i, fract = 0; isdigit(string[i]); i++, fract++); //считаем, сколько чисел соответствует дробной части
      //return TYRE_ERRORS_REAL_RECORD;
  }
  *count = i;
  return BuildNumber(string, i - integer - fract, integer, fract);
}
void ArrToMatrix (double * arr, matrix_t result, int size) {
  int i, j, k = 0;
  for (i = 0; i < result.width; i++) {
    for (j = 0; j < result.height; j++) {
      result.matrix[i][j] = arr[k];
      k++;
    }
  }
}
//функция добавляет 0 в недостающие места и сдвигает массив.
void Shift(double* arr,int k, int wigth, int count) {
  int size = count - wigth;
  int i, l, g;
  int start, start1;
  int heigth = (k - count) / wigth; //количество строк, в которые нужно добавить нули
  for (i = 0; i < size; i++) {
    start1 = wigth + i;             //откуда начинаем проставлять 0, размерность, которую постоянно прибавляем к текущему "началу"
    start = start1;
    for (g = 0; g < heigth; g++) {
      k++;
      for (l =  k; l > start; l--)
        arr[l] = arr[l - 1];
      arr[start] = 0;
      start +=  start1 + 1;
    }
  }
}
matrix_t MatrixParse(char* string) {
  int lenght = strlen (string);
  int i, k = 0, wigth = 0, height = 0, count;
  matrix_t result = {0, 0, 0};
  double * arr, * m;
  arr = (double*)malloc (lenght * sizeof (double));
  assert(string != NULL);
  for (i = 0; isspace(string[i]); i++); //пропускаем пробелы
  if (string[i++] != '{') {
    free(arr);
    //ERROR_INVALID_EXPRESSION
    return result;
  }
  for (i; i < lenght; i++) {
    for (i; isspace(string[i]); i++); //пропускаем пробелы
    if (string[i++] != '{') {
      free(arr);
      //ERROR_INVALID_EXPRESSION
      return result;
    }
    for (i; isspace(string[i]); i++); //пропускаем пробелы
    count = 0;
    while (string[i] != '}') {
      for (i; isspace(string[i]); i++); //пропускаем пробелы
      arr[k++] = ReadNumber(string, &i);
      for (i; isspace(string[i]); i++); //пропускаем пробелы
      if (string[i] == ',')
        i++;
      else if (string[i] != '}') {
        free(arr);
        //ERROR_INVALID_EXPRESSION
        return result;
      }
      count++;
    }
    if (height == 0)
      wigth = count;
    else if (wigth < count) {
      m = (double*) realloc (arr, ((lenght + (count-wigth)*height) * sizeof(double)));
      //m = 0;
      if (m != NULL) {
        arr = m;
        m = NULL;
      }
      else {
        free(arr);
        //ERROR_NOT_ENAUGH_MEMORY
        return result;
      }
      Shift(arr, k, wigth, count); //все предыдущие строки приводит к размеру count добавлением нулей
      k += (count - wigth)*height;
      wigth = count;
    }
    else if (wigth > count) {   //нынешнюю строку приводим к общему размеру, добивая нулями
      for (k, count; wigth != count; k++, count++)
        arr[k] = 0;
    }
    height++;
    for (i; isspace(string[i]); i++); //пропускаем пробелы
    if (string[i++] != '}') {
      free(arr);
      //ERROR_INVALID_EXPRESSION
      return result;
    }
    for (i; isspace(string[i]); i++); //пропускаем пробелы
    if (string[i] == '}')
      break;
    if (string[i] != ',') {
      free(arr);
      //ERROR_INVALID_EXPRESSION
      return result;
    }
  }
  result = MatrixCreate (wigth, height);
  ArrToMatrix (arr, result, k);
  free(arr);
  return result;
}
matrix_t MatrixRead(FILE * stream) {
  unsigned char *str;
  int error = 0;
  int end = 0;
  matrix_t a = { 0, 0, 0 };
  str = ReadString(stream, &end, &error);
  if (error == 0 && !end && str != NULL)
    a = MatrixParse(str);
  free(str);
  return a;
}
