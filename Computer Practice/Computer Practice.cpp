#include <iostream>
#include "big_integer.h"
#include "Algorithms.h"
#include "tests.h"
//#include <vld.h>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));


	big_int* m = big_int_rnd(200);
	big_int* r = big_int_rnd(200);
	big_int* r1 = big_int_rnd(100);

	ll start = clock();
	//
	//big_int* q = big_int_lr_mod_pow2(r, r1, m);
	big_int_add_void(m, r);
	//
	ll end = clock();
	double execution_time = double(end - start) / CLOCKS_PER_SEC;
	cout << "Total Time: " << execution_time << endl;
	big_int_print(m);
	cout << m->length << " " << m->sign;

	big_int_free(r);
	big_int_free(r1);
	//big_int_free(m);
	//big_int_free(q);

	return 0;
}
