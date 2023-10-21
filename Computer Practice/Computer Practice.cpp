#include <iostream>
#include "big_integer.h"
#include "Algorithms.h"
#include "tests.h"
#include <vld.h>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));


	//big_int* m = big_int_rnd(200);
	//big_int* r = big_int_rnd(200);
	big_int* r1 = big_int_rnd(100);
	big_int* m = big_int_get("1111111111111111111111111111111");
	big_int* r = big_int_get("1111111111111111111111111111111");
	big_int* q = big_int_get("1111111111111111111111111111111");
	ll start = clock();
	//
	//big_int* q = big_int_mul_karatsuba(r, r1);
	//big_int* q = big_int_mul(r, r1);
	miller_rabin_test_big_int(m, 10);
	//big_int* q = big_int_lr_mod_pow(r1, m, r);
	//big_int_mul_void(r1, m);
	//big_int_add_void(m, r);
	//
	ll end = clock();
	double execution_time = double(end - start) / CLOCKS_PER_SEC;
	cout << "Total Time: " << execution_time << endl;
	big_int_print(m);
	cout << m->length << " " << m->sign << "\n";

	big_int_free(4, r, r1, m, q);

	return 0;
}
