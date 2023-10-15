#include <iostream>
#include "big_integer.h"
#include "Algorithms.h"
#include "tests.h"
//#include <vld.h>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");


	big_int* r = generate_big_int_prime(1000);
	big_int_print_decimal(r);
	return 0;
}

