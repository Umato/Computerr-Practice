#include <iostream>
#include "big_integer.h"
#include "Algorithms.h"
#include "tests.h"
//#include <vld.h>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	big_int_test_loop(1000);
	//system("color 2");
	//big_int* a = big_int_get("1");
	//big_int* m = big_int_rnd(200);
	//big_int* r = big_int_rnd(200);
	//big_int* r1 = big_int_rnd(50);
	////big_int* b = big_int_get("1");50
	//ll start = clock();
	////big_int_test_loop(1000);
	////big_int* q = big_int_mod(r, r1);
	////big_int* q = generate_big_int_prime(200);
	////big_int* q = big_int_mod(m, r);
	//big_int* q = big_int_lr_mod_pow(r, r1, m);
	////big_int* q = big_int_mul_karatsuba(a, b);
	////big_int* q = big_int_mul_karatsuba(r, r1);
	//ll end = clock();
	//double execution_time = double(end - start) / CLOCKS_PER_SEC;
	//cout /*<< "Total Time: "*/ << execution_time << endl;
	//ll start1 = clock();
	//big_int_lr_mod_pow2(r, r1, m);
	//ll end1 = clock();
	//double execution_time1 = double(end1 - start1) / CLOCKS_PER_SEC;
	//cout /*<< "Total Time: "*/ << execution_time1 << endl;
	//big_int_free(r);
	//big_int_free(r1);
	//big_int_free(m);
	//big_int_free(q);
	//big_int_free(2, r, r1);
	//big_int_print(r);
	//big_int_print(r1);

	return 0;
}
