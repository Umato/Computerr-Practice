#pragma once

#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include "Algorithms.h"
#include "big_integer.h"
#include <fstream>
#include <vector>
#include <string>

typedef long long ll;

void test_euclid();
void test_mod_pow();
void test_euclid_extended();
void test_linear_diophantine();
void test_mul_inverse();
void test_chinese_reminder();
void test_big_int_functions();
void subtraction_check();
void test_big_int_euclid_binary();
void test_big_int_shift_right();
void test_big_int_shift_left();
void test_big_int_multiplication();
void test_big_int_euclid_binary_from_file();
void test_big_int_div();
void test_big_int_mod_pow();
void test_big_mod_pow_file();
void test_big_int_functions_decimal();
void test_big_int_mod_pow_decimal();
void big_int_test_loop(ll n);
big_int* big_int_rnd(int bytes_num);

#endif // TESTS_H