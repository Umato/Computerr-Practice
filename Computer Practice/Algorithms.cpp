#include "Algorithms.h"
#include <iostream>

using namespace std;

int euclid(int a, int b) {
    int temp;
    while (b != 0) {
        temp= b;
        b = a % b;
        a = temp;
    }
    return (a < 0) ? -a : a;
}

int euclid_recursive(int a, int b) {
    return a ? euclid_recursive(abs(b % a), abs(a)) : b;
}

int euclid_binary(int x, int y) {
    if (x == 0) return y;
    if (y == 0) return x;
    int power = 0;
    while (((x | y) & 1) == 0) {
        ++power;
        x >>= 1;
        y >>= 1;
    }
    while (x) {
        while ((y & 1) == 0) y >>= 1;
        while ((x & 1) == 0) x >>= 1;
        if (y > x) swap(x, y);
        x -= y;
    }
    return y << power;
}

long long mod_pow(long long x, long long y, long long m) {
    if (y == 0) return 1;
    long long ans = 1;
    x %= m;
    while (y) {
        if (y & 1) {
            ans = (ans * x) % m;
        }
        x = (x * x) % m;
        y >>= 1;
    }
    return ans;
}

long long mod_pow_recursive(long long x, long long y, long long m) {
    if (y == 0) return 1;

    long long h = mod_pow_recursive(x, y >> 1, m);
    h = (h * h) % m;
    if ((y & 1) == 0) {
        return h;
    }
    else {
        return (x % m * h) % m;
    }
}

// Õ≈ –¿¡Œ“¿≈“
long long lr_mod_pow(long long x, long long y, long long m) {
    int pow = 1;
    while (pow < y) pow <<= 1;
    long long result = 1;
    for (pow >>= 1; (pow & 1) == 0; pow >>= 1) {
        result = (result * result) % m;
        if (pow & y)
            result = (result * x) % m;
    }
    return result;
}

int euclid_extended_recursive(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        if (a < 0) x = -1;
        y = 0;
        return a;
    }
    int g = euclid_extended_recursive(b, a % b, x, y);
    x = x - (a / b) * y;
    swap(x, y);
    return g;
}

int euclid_extended_iterative(int a, int b, int& x, int& y) {
    int x_next = 0, y_next = 1;
    x = 1;
    y = 0;
    while (b != 0) {
        int q = a / b;
        int tmp = b;
        b = a % b;
        a = tmp;
        
        tmp = x_next;
        x_next = x - q * x_next;
        x = tmp;

        tmp = y_next;
        y_next = y - q * y_next;
        y = tmp;
    }
    return a;
}

int linear_diophantine(int* coefficients, const int n, int* result, int target) {
    int gcd = *coefficients, x;

    *result = 1;
    for (int i = 1; i < n; i++) {
        gcd = euclid_extended_iterative(gcd, coefficients[i], x, result[i]);
        for (int j = 0; j < i; j++) {
            result[j] *= x;
        }
    }
    if (target % gcd) {
        return 0;
    }
    else {
        int mult = target / gcd;
        for (int j = 0; j < n; j++) {
            result[j] *= mult;
        }
        return 1;
    }
}

int mul_inverse(int num, int mod_val) {
    int inverse, temp;
    int gcd = euclid_extended_iterative(num, mod_val, inverse, temp);
    if (gcd > 1) return 0;

    return ((inverse % mod_val) + mod_val) % mod_val;
}

int chinese_reminder(const int* remainders, const int* modules, const int num_equations) {
    int total_mod = 1;
    int gcd = 1;

    for (int i = 0; i < num_equations; i++) {
        gcd = euclid(gcd, modules[i]);
        if (gcd != 1) {
            return -1;
        }
        total_mod *= modules[i];
    }
    int solution = 0;
    for (int i = 0; i < num_equations; i++) {
        int mod_division = total_mod / modules[i];
        int inverse = mul_inverse(mod_division, modules[i]);
        solution += (remainders[i] * mod_division * inverse);
    }
    return solution % total_mod;
}

int chinese_reminderr(const int* remainders, const int* modules, int n) {
    int coeff1, coeff2;
    int prev_module = *modules;
    int prev_remainder = *remainders;
    int solution = 0;

    for (int i = 1; i < n; i++) {
        euclid_extended_iterative(prev_module, modules[i], coeff1, coeff2);

        solution = remainders[i] * prev_module * coeff1 + prev_remainder * modules[i] * coeff2;
        prev_module *= modules[i];
        prev_remainder = solution % prev_module;
    }
    return ((solution % prev_module) + prev_module) % prev_module;
}
