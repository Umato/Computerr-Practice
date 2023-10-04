#pragma once

typedef struct big_int {
	size_t length;
	unsigned char* number;
	bool sign;
} big_int;

// Ввод числа и запись в big_int
big_int* big_int_get(const char* x); 
// Вывод содержимого num.
void big_int_print(const big_int* num); 
// Освобождает память
void big_int_free(big_int* num);
// Создает и возвращает копию big_int. 
big_int* big_int_copy(const big_int* original);
// Возвращает результат n1>=n2
bool big_int_geq(const big_int* n1, const big_int* n2);
//Суммирует два числа big_int результат.
big_int* big_int_add(const big_int* n1, const big_int* n2);
// Вычитает n2 из n1 и возвращает результат. 
big_int* big_int_sub(const big_int* n1, const big_int* n2);
// Сдвиг право >>. Не удается выделить память - NULL
big_int* big_int_shift_right(const big_int* num);
// Сдвиг влево <<. Не удается выделить память - NULL
big_int* big_int_shift_left(const big_int* num);
//Возвращает НОД двух чисел x и y.
big_int* big_int_euclid_binary(const big_int* x, const big_int* y);
// Возвращает результат |n1| >= |n2|
bool big_int_abs_geq(const big_int* n1, const big_int* n2);
// Удаляет все лидирующие нули из big_int. Если число = 0, ничего не делает. Проблема если в числе два байта из 0, надо исправить
void big_int_remove_zeroes(big_int* num);
// Возвращает модуль исходного числа.
big_int* big_int_abs(const big_int* n);
// Возвращает n1 == n2
bool big_int_eq(const big_int* n1, const big_int* n2);
// Умножение
big_int* big_int_mul(const big_int* n1, const big_int* n2);

// Написать.
// Деление с остатком (возвращает целую часть и остаток)
void big_int_div_remainder(const big_int* n1, const big_int* n2, int* quotient, int* remainder);
// Возведение в степень
big_int* big_int_pow(const big_int* base, int exponent);
// Перевод из 10 в 2 big_int
big_int* big_int_from_decimal(const char* str);




