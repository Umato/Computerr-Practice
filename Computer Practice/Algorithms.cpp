#include "Algorithms.h"

using namespace std;

ll euclid(ll a, ll b) {
    ll temp;
    while (b != 0) {
        temp= b;
        b = a % b;
        a = temp;
    }
    return (a < 0) ? -a : a;
}

ll euclid_recursive(const ll a, const ll b) {
    return a ? euclid_recursive(abs(b % a), abs(a)) : b;
}

ll euclid_binary(ll x, ll y) {
    if (x == 0) return y;
    if (y == 0) return x;
    ll power = 0;
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

ll mod_pow(ll x, ll y, ll m) {
    if (y == 0) return 1;

    ll ans = 1;
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

ll mod_pow_recursive(const ll x, const ll y, const ll m) {
    if (y == 0) return 1;

    ll h = mod_pow_recursive(x, y >> 1, m);
    h = (h * h) % m;
    if ((y & 1) == 0) {
        return h;
    }
    else {
        return (x % m * h) % m;
    }
}

ll lr_mod_pow(const ll x, const ll y, const ll m) {
    if (y == 0) return 1;

    ll pow = 1;
    while (pow < y) pow <<= 1;
    ll result = x % m;
    for (pow >>= 2; pow; pow >>= 1) {
        result = (result * result) % m;
        if (pow & y)
            result = (result * x) % m;
    }
    return result;
}

ll euclid_extended_recursive(const ll a, const ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        if (a < 0) x = -1;
        y = 0;
        return a;
    }
    ll g = euclid_extended_recursive(b, a % b, x, y);
    x = x - (a / b) * y;
    swap(x, y);
    return g;
}

ll euclid_extended_iterative(ll a, ll b, ll& x, ll& y) {
    ll x_next = 0, y_next = 1;
    x = 1;
    y = 0;
    while (b != 0) {
        ll q = a / b;
        ll tmp = b;
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

ll linear_diophantine(const ll* coefficients, const ll n, ll* result, const ll target) {
    ll gcd = *coefficients, x;

    *result = 1;
    for (size_t i = 1; i < n; i++) {
        gcd = euclid_extended_iterative(gcd, coefficients[i], x, result[i]);
        for (size_t j = 0; j < i; j++) {
            result[j] *= x;
        }
    }
    if (target % gcd) {
        return 0;
    }
    else {
        ll mult = target / gcd;
        for (int j = 0; j < n; j++) {
            result[j] *= mult;
        }
        return 1;
    }
}

ll mul_inverse(ll num, ll mod_val) {
    ll inverse, temp;
    ll gcd = euclid_extended_iterative(num, mod_val, inverse, temp);
    if (gcd > 1) return 0;

    return ((inverse % mod_val) + mod_val) % mod_val;
}

ll chinese_reminder(const ll* remainders, const ll* modules, const ll num_equations) {
    ll total_mod = 1;
    ll gcd = 1;

    for (size_t i = 0; i < num_equations; i++) {
        gcd = euclid(gcd, modules[i]);
        if (gcd != 1) {
            return -1;
        }
        total_mod *= modules[i];
    }
    ll solution = 0;
    for (size_t i = 0; i < num_equations; i++) {
        ll mod_division = total_mod / modules[i];
        ll inverse = mul_inverse(mod_division, modules[i]);
        solution += (remainders[i] * mod_division * inverse);
    }
    return solution % total_mod;
}

ll chinese_remainder_iterative(const ll* remainders, const ll* modules, const ll n) {
    ll coeff1, coeff2;
    ll prev_module = *modules;
    ll prev_remainder = *remainders;
    ll solution = 0;
    ll module;
    for (size_t i = 1; i < n; i++) {
        module = modules[i];
        euclid_extended_iterative(prev_module, module, coeff1, coeff2);

        solution = remainders[i] * prev_module * coeff1 + prev_remainder * module * coeff2;
        prev_module *= module;
        prev_remainder = solution % prev_module;
    }
    return ((solution % prev_module) + prev_module) % prev_module;
}

ll cti(const char* ch) {
    ll result = 0;
    ll sign = 1;

    if (*ch == '-') {
        sign = -1;
        ch++;
    }

    while (*ch >= '0' && *ch <= '9') {
        result = result * 10 + (*ch - '0');
        ch++;
    }

    return result * sign;
}

bool is_prime(ll num) {
    if (num <= 2) return num == 2;
    ull d = 3;
    while (d * d < num && (num % d)) d += 1;
    return d * d >= num;
}