#include <iostream>
#include "big_integer.h"
#include "Algorithms.h"
#include "tests.h"
#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	//big_int* n1 = big_int_get("1111111111111111111111111111");
	//big_int* n2 = big_int_get("1111111111111110111111111111");
	////big_int_mul_karatsuba(n1, n2);
	//big_int* r;
	//big_int* q;
	//big_int_div(n1, n2, &r, &q);
	//big_int_print(r);
	//big_int_print(q);
	//char x = 3;
	//big_int* n1 = big_int_get(x);
	//big_int_print(n1);


	//test_big_int_mod_pow_decimal();
	//test_big_int_functions_decimal();
	//big_int* n1 = big_int_get("10101011110101010101010101111111111101010101");
	//big_int* n2 = big_int_get("101010101010111111111101010101");
	//for (size_t i = 0; i < 100000000; ++i) {
	//	big_int* res = big_int_mul_karatsuba(n1, n2);
	//	big_int_free(res);
	//}
	//test_big_int_mod_pow();
	for (int i = 0; i < 10; ++ i) big_int_test_loop(100);

	_CrtDumpMemoryLeaks();
	return 0;
}

