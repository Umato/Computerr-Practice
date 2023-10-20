#pragma once

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

//#define NDEBUG 

#include <iostream>
#include <cassert>
#include <cstdarg>
//#include <cmath>


typedef unsigned long long ull;
typedef long long ll;

/// <summary>
/// A typedef struct that represents a large integer value.
/// The 'length' field represents the number of digits in the integer.
/// The 'number' field is a pointer to an allocated array of unsigned chars, each representing a single digit of the integer in binary form.
/// The 'sign' field is a boolean representing the sign of the integer - a true value implies a negative number.
/// </summary>
typedef struct big_int {
	size_t length;
	unsigned char* number;
	bool sign;
} big_int;

big_int* big_int_get(const int x);
/// <summary>
/// Read string in binary format and create big_int object from it. 
/// </summary>
/// <param name="x">Binary string input.</param>
/// <returns>Pointer to newly created big_int number or NULL if allocation failed.</returns>
big_int* big_int_get(const char* x);
/// <summary>
/// Print the binary big_int number.
/// </summary>
/// <param name="num">Big_int object to be printed.</param>
/// <returns>None.</returns>
void big_int_print(const big_int* num);
/// <summary>
/// Free memory allocated for the big_int number.
/// </summary>
/// <param name="num">Pointer to be freed from memory.</param>
/// <returns>None.</returns>
void big_int_free(big_int* original);
/// <summary>
/// Makes a copy of a big_int number.
/// </summary>
/// <param name="original">The number to be copied.</param>
/// <returns>A copy of the input number, or NULL if memory allocation fails.</returns>
big_int* big_int_copy(const big_int* original);
/// <summary>
/// Checks if n1 is greater than or equal to n2. 
/// </summary>
/// <param name="n1">The first big_int number.</param>
/// <param name="n2">The second big_int number.</param>
/// <returns>true if n1 is greater than or equal to n2, false otherwise.</returns>
bool big_int_geq(const big_int* n1, const big_int* n2);
/// <summary>
/// Add two big_int numbers.
/// </summary>
/// <param name="n1">The first big_int number.</param>
/// <param name="n2">The second big_int number.</param>
/// <returns>Sum of n1 and n2, or NULL if memory allocation fails.</returns>
big_int* big_int_add(const big_int* n1, const big_int* n2);
/// <summary>
/// Subtract n2 from n1. 
/// </summary>
/// <param name="n1">The big_int number to be subtracted from.</param>
/// <param name="n2">The big_int number to be subtracted.</param>
/// <returns>Difference of n1 and n2, or NULL if memory allocation fails.</returns>
big_int* big_int_sub(const big_int* n1, const big_int* n2);
/// <summary>
/// Performs a binary right shift on a big_int number.
/// </summary>
/// <param name="num">The number to be shifted.</param>
/// <param name="n">The number of positions to shift.</param>
/// <returns>Result of right shifting num by n positions, or NULL if memory allocation fails.</returns>
big_int* big_int_shift_right(const big_int* num, ll n);
/// <summary>
/// Performs a binary left shift on a big_int number.
/// </summary>
/// <param name="num">The number to be shifted.</param>
/// <param name="n">The number of positions to shift.</param>
/// <returns>Result of left shifting num by n positions, or NULL if memory allocation fails.</returns>
big_int* big_int_shift_left(const big_int* num, ll n);
/// <summary>
/// Finds the Greatest Common Divisor of two big_int numbers using binary Euclidean algorithm.
/// </summary>
/// <param name="x">The first big_int number.</param>
/// <param name="y">The second big_int number.</param>
/// <returns>Greatest Common Divisor of x and y, or NULL if memory allocation fails.</returns>
big_int* big_int_euclid_binary(const big_int* x, const big_int* y);
/// <summary>
/// Checks if the absolute value of n1 is greater than or equal to the absolute value of n2. 
/// </summary>
/// <param name="n1">The first big_int number.</param>
/// <param name="n2">The second big_int number.</param>
/// <returns>true if |n1| is greater than or equal to |n2|, false otherwise.</returns>
bool big_int_abs_geq(const big_int* n1, const big_int* n2);
/// <summary>
/// Remove all leading zeroes from a big_int number.
/// </summary>
/// <param name="num">The big_int number to be altered.</param>
/// <returns>None.</returns>
void big_int_remove_zeroes(big_int* num);
/// <summary>
/// Get the absolute value of a big_int number.
/// </summary>
/// <param name="n">The big_int number from which the absolute value is to be calculated.</param>
/// <returns>Absolute value of the big_int number.</returns>
big_int* big_int_abs(const big_int* n);
/// <summary>
/// Checks if n1 is equal to n2. 
/// </summary>
/// <param name="n1">The first big_int number.</param>
/// <param name="n2">The second big_int number.</param>
/// <returns>true if n1 is equal to n2, false otherwise.</returns>
bool big_int_eq(const big_int* n1, const big_int* n2);
/// <summary>
/// Multiplies two big_int numbers.
/// </summary>
/// <param name="n1">The first big_int number.</param>
/// <param name="n2">The second big_int number.</param>
/// <returns>Product of n1 and n2, or NULL if memory allocation fails.</returns>
big_int* big_int_mul(const big_int* n1, const big_int* n2);
/// <summary>
/// Raise a number to the power modulo another number.
/// </summary>
/// <param name="base">The base number.</param>
/// <param name="exponent">The exponent.</param>
/// <param name="mod">The modulating number.</param>
/// <returns>The calculated power modulo, or NULL if memory allocation fails.</returns>
big_int* big_int_mod_pow(const big_int* base, const big_int* exponent, const big_int* mod);
/// <summary>
/// Sets a new length (in number of bytes) to a big_int object and reallocates memory accordingly.
/// </summary>
/// <param name="num">Pointer to the big_int object.</param>
/// <param name="new_length">The new length (in number of bytes).</param>
void big_int_set_length(big_int* num, const size_t new_length);
/// <summary>
/// Performs the division of two big integers (n1 and n2) by repeated subtraction and computes the quotient and remainder.
/// </summary>
/// <param name="n1">Pointer to the first big_int object (dividend).</param>
/// <param name="n2">Pointer to the second big_int object (divisor).</param>
/// <param name="quotient">Pointer to a pointer storing the result of quotient after division.</param>
/// <param name="remainder">Pointer to a pointer storing the result of remainder after division.</param>
void big_int_div_by_sub(const big_int* n1, const big_int* n2, big_int** quotient, big_int** remainder);
/// <summary>
/// Sets a new length (in number of bytes) to a big_int object and reallocates memory accordingly.
/// </summary>
/// <param name="num">Pointer to the big_int object.</param>
/// <param name="new_length">The new length (in number of bytes).</param>
void big_int_set_length(big_int* num, const size_t new_length);
/// <summary>
/// Performs the division of two big integers (n1 and n2) by repeated subtraction and computes the quotient and remainder.
/// </summary>
/// <param name="n1">Pointer to the first big_int object (dividend).</param>
/// <param name="n2">Pointer to the second big_int object (divisor).</param>
/// <param name="quotient">Pointer to a pointer storing the result of quotient after division.</param>
/// <param name="remainder">Pointer to a pointer storing the result of remainder after division.</param>
void big_int_div_by_sub(const big_int* n1, const big_int* n2, big_int** quotient, big_int** remainder);
/// <summary>
/// Add the second big_int (n2) to the first one (n1). The result is stored in n1.
/// </summary>
/// <param name="n1">Pointer to the first big_int object. It also stores the result of the addition.</param>
/// <param name="n2">Pointer to the second big_int object to be added.</param>
void big_int_add_void(big_int** n1, const big_int* n2);
/// <summary>
/// Subtracts the second big_int (n2) from the first one (n1). The result is stored in n1.
/// </summary>
/// <param name="n1">Pointer to the first big_int object. It also stores the result of the subtraction.</param>
/// <param name="n2">Pointer to the second big_int object to be subtracted.</param>
void big_int_sub_void(big_int** n1, const big_int* n2);
/// <summary>
/// Shifts a big_int right by a certain number of bits.
/// </summary>
/// <param name="num">Pointer to the big_int object to be shifted.</param>
/// <param name="n">The number of bits to shift right.</param>
void big_int_shift_right_void(big_int** num, ll n);
/// <summary>
/// Shifts a big_int left by a certain number of bits.
/// </summary>
/// <param name="n1">Pointer to the big_int object to be shifted.</param>
/// <param name="n">The number of bits to shift left.</param>
void big_int_shift_left_void(big_int** n1, ll n);
/// <summary>
/// Multiplies the first big_int (n1) with the second one (n2). The result is stored in n1.
/// </summary>
/// <param name="n1">Pointer to the first big_int object. It also stores the result of multiplication.</param>
/// <param name="n2">Pointer to the second big_int object to be multiplied.</param>
void big_int_mul_void(big_int** n1, const big_int* n2);
/// <summary>
/// Performs the division of two big integers (N and D) and computes the quotient and remainder.
/// </summary>
/// <param name="num1">Pointer to the first big_int object (dividend).</param>
/// <param name="num2">Pointer to the second big_int object (divisor).</param>
/// <param name="quotient">Pointer to a pointer storing the result of quotient after division.</param>
/// <param name="remainder">Pointer to a pointer storing the result of remainder after division.</param>
void big_int_div(const big_int* num1, const big_int* num2, big_int** quotient, big_int** remainder);
/// <summary>
/// Raise a number to the power modulo another number.
/// </summary>
/// <param name="base">The base number.</param>
/// <param name="exponent">The exponent.</param>
/// <param name="mod">The modulating number.</param>
/// <returns>The calculated power modulo, or NULL if memory allocation fails.</returns>
big_int* big_int_lr_mod_pow(const char base, const big_int* exponent, const big_int* mod);

big_int* big_int_lr_mod_pow(const big_int* base, const big_int* exponent, const big_int* mod);
/// <summary>
/// Performs the modulo operation on two big integers (n1 and n2), returning the remainder after division of n1 by n2.
/// </summary>
/// <param name="n1">Pointer to the first big_int object (dividend).</param>
/// <param name="n2">Pointer to the second big_int object (divisor).</param>
/// <returns>Remainder of the division of n1 by n2, or NULL if memory allocation fails.</returns>
big_int* big_int_mod(const big_int* num1, const big_int* num2);
/// <summary>
/// Performs division of two big integers (n1 and n2) and returns only quotient.
/// </summary>
/// <param name="n1">Pointer to the first big_int object (dividend).</param>
/// <param name="n2">Pointer to the second big_int object (divisor).</param>
/// <returns>Quotient of the division of n1 by n2, or NULL if memory allocation fails.</returns>
big_int* big_int_div_quotient(const big_int* n1, const big_int* n2);

big_int* big_int_bitwise_and(const big_int* n1, const big_int* n2);

void big_int_print_decimal(const big_int* num);

big_int* big_int_get_dec(const char* x);

big_int* big_int_mul_karatsuba(const big_int* n1, const big_int* n2);

big_int* big_int_slice(const big_int* n, size_t start, size_t end);

big_int* generate_big_int_prime(size_t bytes_num);



void big_int_add_void(big_int* n1, const big_int* n2);
void big_int_sub_void(big_int* n1, const big_int* n2);



bool miller_rabin_test_big_int(const big_int* num, size_t iterations);

big_int* big_int_rnd(size_t n);

size_t big_int_length(const big_int* num);

big_int* big_int_generate(const big_int* num);

big_int* big_int_rnd_odd(size_t bytes_num);

big_int* big_int_generate_range(const big_int* n1, const big_int* n2);

void big_int_free(size_t count, ...);

big_int* big_int_lr_mod_pow2(big_int* x, big_int* n, big_int* m);
#endif // BIG_INT_H


