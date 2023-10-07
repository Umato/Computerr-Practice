#pragma once

#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include "Algorithms.h"
#include "big_integer.h"
#include <fstream>
#include <vector>
#include <string>

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

#endif // TESTS_H