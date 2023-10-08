#pragma once

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>

typedef long long ll;
/// <summary>
/// Compute the greatest common divisor (GCD) of two numbers using the Euclidean algorithm.
/// </summary>
/// <param name="a">The first input number.</param>
/// <param name="b">The second input number.</param>
/// <returns>The GCD of a and b.</returns>
ll euclid(ll a, ll b);
/// <summary>
/// Compute the GCD of two numbers using the Euclidean algorithm in a recursive manner.
/// </summary>
/// <param name="a">The first input number.</param>
/// <param name="b">The second input number.</param>
/// <returns>The GCD of a and b.</returns>
ll euclid_recursive(const ll a, const ll b);
/// <summary>
/// Compute the GCD of two numbers using the binary Euclidean algorithm.
/// </summary>
/// <param name="x">The first input number.</param>
/// <param name="y">The second input number.</param>
/// <returns>The GCD of x and y.</returns>
ll euclid_binary(ll x, ll y);
/// <summary>
/// Calculate the exponentiation of a number modulo another number.
/// </summary>
/// <param name="x">The base.</param>
/// <param name="y">The exponent.</param>
/// <param name="m">The modulus.</param>
/// <returns>The result of (x^y) mod m.</returns>
ll mod_pow(ll x, ll y, ll m);
/// <summary>
/// Recursive algorithm for raised power calculation modulo m.
/// </summary>
/// <param name="x">The base.</param>
/// <param name="y">The exponent.</param>
/// <param name="m">The modulus.</param>
/// <returns>The result of (x^y) mod m.</returns>
ll mod_pow_recursive(const ll x, const ll y, const ll m);
/// <summary>
/// Compute x raised to the power y modulo m in logarthmic time complexity.
/// </summary>
/// <param name="x">The base of the power.</param>
/// <param name="y">The exponent of the power.</param>
/// <param name="m">The modulus.</param>
/// <returns>The result of (x^y) mod m, using fast exponentiation (also known as exponentiation by squaring).</returns>
ll lr_mod_pow(const ll x, const ll y, const ll m);
/// <summary>
/// Extended Euclidean algorithm to find an solution for Diophantine equations. Recursive version.
/// </summary>
/// <param name="a">Value a.</param>
/// <param name="b">Value b.</param>
/// <param name="x">First Bezout's coeff.</param>
/// <param name="y">Second Bezout's coeff.</param>
/// <returns>GCD of a and b.</returns>
ll euclid_extended_recursive(const ll a, const ll b, ll& x, ll& y);
/// <summary>
/// Extended Euclidean algorithm to find an solution for Diophantine equation. Iterative version.
/// </summary>
/// <param name="a">Value a.</param>
/// <param name="b">Value b.</param>
/// <param name="x">First Bezout's coeff.</param>
/// <param name="y">Second Bezout's coeff.</param>
/// <returns>GCD of a and b.</returns>
ll euclid_extended_iterative(ll a, ll b, ll& x, ll& y);
/// <summary>
/// Solve a Diophantine equation.
/// </summary>
/// <param name="coefficients">Coefficients in the equation.</param>
/// <param name="n">Number of equations.</param>
/// <param name="result">Array to store the solution.</param>
/// <param name="target">Target number.</param>
/// <returns>True if solution exists, False otherwise.</returns>
ll linear_diophantine(const ll* coefficients, const ll n, ll* result, const ll target);
/// <summary>
/// Find the multiplicative inverse of a number modulo m.
/// </summary>
/// <param name="x">Value for which to find the multiplicative inverse modulo m.</param>
/// <param name="m">The modulus.</param>
/// <returns>The multiplicative inverse of x modulo m.</returns>
ll mul_inverse(ll x, ll m);
/// <summary>
/// Solve a system of simultaneous congruences using the Chinese Remainder Theorem (CRT).
/// </summary>
/// <param name="remainders">Remainders of the equations.</param>
/// <param name="modules">Moduli of the equations.</param>
/// <param name="num_equations">Number of equations in the system.</param>
/// <returns>A number x such that x modulo modules[i] equals to remainders[i] for every i from 0 to num_equations.</returns>
ll chinese_reminder(const ll* remainders, const ll* modules, const ll num_equations);
/// <summary>
/// Solve a system of simultaneous congruences using the Chinese Remainder Theorem (CRT) iteratively.
/// </summary>
/// <param name="remainders">Remainders of the equations.</param>
/// <param name="modules">Moduli of the equations.</param>
/// <param name="n">Number of equations in the system.</param>
/// <returns>A number x such that x modulo modules[i] equals to remainders[i] for every i from 0 to n.</returns>
ll chinese_remainder_iterative(const ll* remainders, const ll* modules, const ll n);

#endif // ALGORITHMS_H
