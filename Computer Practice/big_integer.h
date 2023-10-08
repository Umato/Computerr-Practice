#pragma once

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <iostream>

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
big_int* big_int_shift_right(const big_int* num, int n);
/// <summary>
/// Performs a binary left shift on a big_int number.
/// </summary>
/// <param name="num">The number to be shifted.</param>
/// <param name="n">The number of positions to shift.</param>
/// <returns>Result of left shifting num by n positions, or NULL if memory allocation fails.</returns>
big_int* big_int_shift_left(const big_int* num, int n);
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
/// Divides n1 by n2 and returns the quotient and the remainder.
/// </summary>
/// <param name="n1">The dividend.</param>
/// <param name="n2">The divisor.</param>
/// <param name="quotient">The quotient pointer.</param>
/// <param name="remainder">The remainder pointer.</param>
/// <returns>None. The result is stored in the given quotient and remainder.</returns>
void big_int_div(const big_int* n1, const big_int* n2, big_int** quotient, big_int** remainder);

#endif // BIG_INT_H


