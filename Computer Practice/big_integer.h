#pragma once

typedef struct big_int {
	size_t length;
	unsigned char* number;
	bool sign;
} big_int;

// ���� ����� � ������ � big_int
big_int* big_int_get(const char* x); 
// ����� ����������� num.
void big_int_print(const big_int* num); 
// ����������� ������
void big_int_free(big_int* num);
// ������� � ���������� ����� big_int. 
big_int* big_int_copy(const big_int* original);
// ���������� ��������� n1>=n2
bool big_int_geq(const big_int* n1, const big_int* n2);
//��������� ��� ����� big_int ���������.
big_int* big_int_add(const big_int* n1, const big_int* n2);
// �������� n2 �� n1 � ���������� ���������. 
big_int* big_int_sub(const big_int* n1, const big_int* n2);
// ����� ����� >>. �� ������� �������� ������ - NULL
big_int* big_int_shift_right(const big_int* num);
// ����� ����� <<. �� ������� �������� ������ - NULL
big_int* big_int_shift_left(const big_int* num);
//���������� ��� ���� ����� x � y.
big_int* big_int_euclid_binary(const big_int* x, const big_int* y);
// ���������� ��������� |n1| >= |n2|
bool big_int_abs_geq(const big_int* n1, const big_int* n2);
// ������� ��� ���������� ���� �� big_int. ���� ����� = 0, ������ �� ������. �������� ���� � ����� ��� ����� �� 0, ���� ���������
void big_int_remove_zeroes(big_int* num);
// ���������� ������ ��������� �����.
big_int* big_int_abs(const big_int* n);
// ���������� n1 == n2
bool big_int_eq(const big_int* n1, const big_int* n2);
// ���������
big_int* big_int_mul(const big_int* n1, const big_int* n2);

// ��������.
// ������� � �������� (���������� ����� ����� � �������)
void big_int_div_remainder(const big_int* n1, const big_int* n2, int* quotient, int* remainder);
// ���������� � �������
big_int* big_int_pow(const big_int* base, int exponent);
// ������� �� 10 � 2 big_int
big_int* big_int_from_decimal(const char* str);




