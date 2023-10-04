#include <iostream>
#include "big_integer.h"
#include "Algorithms.h"
#include "tests.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	//subtraction_check();
	test_big_int_euclid_binary();
	//cout << euclid_binary(1, 3);
	//test_big_int_functions();
	//test_big_int_shift_left();
	//big_int_print(big_int_sub(big_int_get("10111"), big_int_get("10101")));
}
