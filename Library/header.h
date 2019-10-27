#ifndef LIB_H
#define LIB_H
#define ELEMENT(a,b) [a][b]

#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>

/**
 * @mainpage Introduction

 LibMatrix - ���������� ��� ������ � ��������� ������������� �������.
 ��� ������������� matrix_t ����� ������� � ������ - �� ��������� ������� ������, 
 ���� ����������� �������������������� �������, �� ��������� ������ ������.
 */


/**
 * @defgroup Matrix_functions Create
 *
 * ������� �������� � �������� �������.
 *
 * @{
 */

/// ��������� ������������� �������.
typedef struct {
  double ** matrix;	///< ��������� ������������ ������ �� ���������� �������
  int height;		///< ���������� ����� � �������
  int width;		///< ���������� ��������� � �������
} matrix_t;
/**
 * @brief ������� �������.
 *
 * ����� ������� � ��������, ���������� ������� ��. 
 * ��� ���� ����������� ���������
 * 
 * @param height ���������� ����� �������
 * @param width ���������� �������� �������
 * 
 * @return ��������� ������� (���������)
 * @see MatrixDestroy
 */
matrix_t MatrixCreate(int height, int width);
/**
 * @brief ������� �������.
 *
 * ����� ������ � ��������, ���������� ������� ��. 
 * ��� ���� ��������� ���������� ��� ��� ������� ������
 * 
 * @param a ��������� �������
 * 
 * @return ��������� ������� (���������)
 * @see MatrixCreate
 */
void MatrixDestroy(matrix_t a);
/**
 * @defgroup Matrix_functions Operations
 *
 * ������� ��� ������ � ��������, ����� ��� ��������, ����������,
 * ��������� (�� �������, �� �����), ���������� (���������, �������),
 * ������������ ����� ������� ���������, ����������������.
 *
 * @{
 */

/**
 * @brief �������� ������.
 *
 * ��� �������� ��������� ������ � ������ ������ ������ ���������,
 * ��� ������������ ������� �������� ������.
 * 
 * @param a ������ ������� ��� ��������
 * @param b ������ ������� ��� ��������
 * 
 * @return ����� ������� - ��������� �������� ���� ������. ���� 
 * �������� �� ������� - ������� ������� (��������� �� ������
 * �������� ������� ����� == NULL)
 * @see MatrixSub, MatrixMul, MatrixMulDouble, MatrixTrance
 */
matrix_t MatrixAdd(matrix_t a, matrix_t b);
/**
 * @brief ��������� ������.
 * 
 * ��� ��������� ���������� �������� ������ ������� ������ ���������
 * ���������� ����� ������ (������������ ��������� ��������� ������).
 * 
 * @param a ������ ������� ��� ���������
 * @param b ������ ������� ��� ���������
 * 
 * @return ����� ������� - ��������� ������������ ���� ������ 
 * @param a * @param b. ���� ��������� �� ������� - ������� �������
 * (��������� �� ������ �������� ������� ����� == NULL)
 * @see MatrixAdd, MatrixSub, MatrixMulDouble, MatrixTrance
 */
matrix_t MatrixMul(matrix_t a, matrix_t b);
/**
 * @brief ��������� ������.
 *
 * ��� ��������� ��������� ������ � ������ ������ ������ ���������,
 * ��� ������������ ������� �������� ������.
 * 
 * @param a �������, �� ������� ��������
 * @param b ���������� �������
 * 
 * @return ����� ������� - ��������� �������� ���� ������. ���� 
 * ��������� �� ������� - ������� ������� (��������� �� ������
 * �������� ������� ����� == NULL)
 * @see MatrixSub, MatrixMul, MatrixMulDouble, MatrixTrance
 */
matrix_t MatrixSub(matrix_t a, matrix_t b);
/**
 * @brief ��������� ������� �� �����.
 * 
 * @param a �������
 * @param number ������������ �����, �� ������� ���������� �������
 * 
 * @return ����� ������� - ��������� ��������� ������� �� �����.
 * @see MatrixSub, MatrixMul, MatrixAdd, MatrixTrance
 */
matrix_t MatrixMulDouble(matrix_t a, double number);
/**
 * @brief ������������ ����� ������� ��������� �������.
 *
 * ��������� ������ � ������ ������� ������ ���� �����
 * (���������� �������).
 * 
 * @param a �������
 * 
 * @return ������������ ����� - ��������� ������������.
 * @see MatrixSub, MatrixMul, MatrixMulDouble, MatrixAdd
 */
double MatrixTrance(matrix_t a);
/**
 * @brief ���������������� �������.
 * 
 * @param a �������
 * 
 * @return ����� ������� - ��������� ���������������� ��������.
 * @see MatrixSetZero, MatrixSetIdentity
 */
matrix_t MatrixTranspose(matrix_t a);
/**
 * @brief ���������� ������� ������.
 * 
 * ���������� �� ���� ������� ����������� ������. ��� ���� ������ 
 * �������� ����� ������
 * 
 * @param a �������
 * 
 * @see MatrixTranspose, MatrixSetIdentity
 */
void MatrixSetZero(matrix_t a);
/**
 * @brief ���������� ��������� �������.
 * 
 * ���������� �� ���� ������� ����������� ��� ���������. ��� ���� 
 * ������ �������� ����� ������. ������������ ������� - ������� 
 * ������ ���� ����������. ���� ������� �� ����� ���������� - ����������
 * �� ���� ������� ������ ������� (��������� �� ������ �������� ������� 
 * ����� == NULL)
 * 
 * @param a �������
 * 
 * @see MatrixTranspose, MatrixSetIdentity
 */
void MatrixSetIdentity(matrix_t a);
/**
 * @brief ������������ �������.
 * 
 * ������� ������� ������������ ���������� �� ���� ������� ������������
 * ������� - ������� ������ ���� ����������. 
 * 
 * @param a �������
 * 
 * @return ������������ ����� - ������������ �������
 *
 * @see MatrixDeterminant
 */
long double MatrixDeterminant(matrix_t argument);
/**
 * @brief �������� �������.
 * 
 * ������� ��������� �������� �������, ���� ��� ����. ����
 * �������� ������� ��� - ������� �� ���� ������� �� ����������.
 * 
 * @param a �������
  * @return �������� ������� � a
 * 
 * @see ReverseMatrix
 */
matrix_t ReverseMatrix(matrix_t a);
/**
 * @defgroup Matrix_functions Write-Read
 *
 * ������� ��� ���������� � ������ ������. ������ ���������� 
 * � ���������� �������.
 *
 * @{
 */
/**
 * @brief ����� �������.
 * 
 * ������� ������� ������� � ����������� �������, � ���� {{a,b},{c,d}}
 * ��� ������ � ���� �������� ���� ������� �����, � ������� �� ����� 
 * ��������. ��� ���� ����, ������� ������������ �������������� ������ ��� ������,
 * ���� ����������� �����, � ����� ������ ���������� <code>stream = stdout</code>.
 * 
 * @param stream ����� ��� ������
 * @param matrix �������
 *
 * @see MatrixRead, MatrixPrint
 */
void MatrixWrite(FILE * stream, matrix_t matrix);
/**
 * @brief ���������� �������.
 * 
 * ������� ��������� ������� � ����������� �������, � ���� {{a,b},{c,d}}, �����������
 * ���������� �������.��� ������ � ���� �������� ���� ������� �����, � ������� �� ����� 
 * ��������. ��� ���� ����, ������� ������������ �������������� ������ ��� ������,
 * ���� ����������� �����, � ����� ������ ���������� <code>stream = stdin</code>.
 * 
 * @param stream ����� ��� �����
 *
 * @return �������. ���� ��������� ���� ���������� ��� ��������� �����-�� ������ ��������,
 * �������� ������� ������ (��������� ������� ��������� ����� == NULL)
 * @see MatrixWrite, MatrixPrint
 */
matrix_t MatrixRead(FILE * stream);
/**
 * @brief ���������� �������.
 * 
 * ������� ������� ������� � ������� ��������� �����, ��� �� ��������, � �������
 * 
 * @param a �������
 *
 * @see MatrixWrite, MatrixRead
 */
void MatrixPrint(matrix_t a);

#endif