#include "big_integer.h"

using namespace std;

big_int* big_int_get(const int x) {
    big_int* num = (big_int*)malloc(sizeof(big_int));

    if (!num) return NULL;

    num->sign = false;

    if (x < 0) num->sign = true;

    int new_x = x < 0 ? -x : x;

    num->length = sizeof(int);

    num->number = (unsigned char*)malloc(num->length * sizeof(unsigned char));

    if (!num->number) {  
        free(num);
        return NULL;
    }

    for (size_t i = 0; i < num->length; i++) {
        num->number[i] = (new_x >> (i * 8)); 
    }

    big_int_remove_zeroes(num);
    return num;
}

big_int* big_int_get(const char* x) {
    if (!x) return NULL; // Не указывает ли x на NULL;

    big_int* num = (big_int*)malloc(sizeof(big_int));
    if (!num) return NULL; // Если не удалось выделить память для y

    size_t l = strlen(x);
    num->sign = false;
    const char* new_x = x;
    if (x[0] == '-') {
        num->sign = true;
        new_x++;
        l--;
    }

    num->length = (l + 7) >> 3;

    num->number = (unsigned char*)calloc(num->length, sizeof(unsigned char));
    if (!num->number) {  // Не удалось выделить память для y->number
        free(num);
        return NULL;
    }

    for (size_t i = 0; i < l; i++) {
        if (new_x[l - 1 - i] == '1') num->number[i >> 3] |= (1 << (i & 7));
        else if (new_x[l - 1 - i] != '0') {  // x[] не 1 и не 0
            //cout << new_x[l - 1 - i];
            big_int_free(num);
            return NULL;
        }
    }
    new_x = NULL;
    big_int_remove_zeroes(num);
    return num;
}

void big_int_print(const big_int* num) {
    if (!num) return;

    const size_t total_bits = num->length << 3;
    char bit;

    if (num->sign) putchar('-');

    bool flag = false;
    for (int i = ((total_bits)-1); i >= 0; --i) {
        bit = (num->number[i >> 3] & (1 << (i & 7))) ? '1' : '0';
        if (flag || bit == '1') {
            flag = true;
            putchar(bit);
        }
    }
    if (!flag) putchar('0');
    putchar('\n');
    return;
}

void big_int_free(big_int* num) {
    if (num == NULL) return;
    num->length = 0;
    if (num->number != NULL) {
        free(num->number);
        num->number = NULL;
    }
    free(num);
}

big_int* big_int_copy(const big_int* original) {
    if (!original) return NULL;

    big_int* copy = (big_int*)malloc(sizeof(big_int));
    if (!copy) return NULL;
    
    *copy = *original;

    copy->number = (unsigned char*)malloc(copy->length * sizeof(unsigned char));
    if (!copy->number) {
        big_int_free(copy);
        return NULL;
    }
    // Копирование данных из исходного массива чисел в копию
    memcpy(copy->number, original->number, copy->length * sizeof(unsigned char));

    return copy;
}

bool big_int_geq(const big_int* n1, const big_int* n2) {
    if (n1 == NULL || n2 == NULL) return false;

    //Знаки разные: n1 - положительно = возвращаем !false и наоборот
    if (n1->sign != n2->sign) return !n1->sign;

    // (>) && (+) = t, (>) && (-) = f, (<) && (+) = f, (<) && (-) = t
    if (n1->length != n2->length) return ((n1->length > n2->length) ^ n1->sign);

    for (int i = (n1->length - 1); i >= 0; i--) {
        if (n1->number[i] != n2->number[i]) return ((n1->number[i] > n2->number[i]) ^ n1->sign);
    }

    return true;
}

bool big_int_abs_geq(const big_int* n1, const big_int* n2) {
    if (!n1 || !n2) return false;

    if (n1->length != n2->length) return n1->length > n2->length;

    for (int i = (n1->length - 1); i >= 0; i--) {
        if (n1->number[i] != n2->number[i]) return n1->number[i] > n2->number[i];
    }
    return true;
}

big_int* big_int_add(const big_int* n1, const big_int* n2) {
    if (n1 == NULL || n2 == NULL) return NULL;

    if (n1->sign == n2->sign) {
        size_t new_length = (n1->length > n2->length ? n1->length : n2->length) + 1;
        big_int* result = (big_int*)malloc(sizeof(big_int));
        if (!result) return NULL;
        result->length = new_length;

        result->number = (unsigned char*)calloc(result->length, sizeof(unsigned char));
        if (!result->number) {
            free(result);
            return NULL;
        }

        result->sign = n1->sign;
        unsigned char carry = 0;

        for (size_t i = 0; i < new_length; i++) {
            unsigned int sum = carry;

            if (i < n1->length) sum += n1->number[i];
            if (i < n2->length) sum += n2->number[i];

            result->number[i] = sum;
            carry = (sum >> 8);
        }

        if (carry) result->number[new_length - 1] = carry;
        else {
            big_int_remove_zeroes(result);
        }
        return result;
    }
    else {
        ((big_int*)n2)->sign = !n2->sign;
        big_int* result = big_int_sub(n1, n2);
        ((big_int*)n2)->sign = !n2->sign;
        if (!result) return NULL;

        return result;
    }
}

big_int* big_int_sub(const big_int* n1, const big_int* n2) {
    if (!n1 || !n2) return NULL;

    if (n1->sign == n2->sign) {
        if (big_int_abs_geq(n1, n2)) {
            size_t new_length = n1->length;
            big_int* result = (big_int*)malloc(sizeof(big_int));
            if (!result) return NULL;

            result->length = new_length;
            result->number = (unsigned char*)calloc(result->length, sizeof(unsigned char));
            if (!result->number) {
                free(result);
                return NULL;
            }

            result->sign = n1->sign;
            unsigned char borrow = 0;
            for (size_t i = 0; i < new_length; i++) {
                int sub = n1->number[i] - borrow;
                if (i < n2->length) sub -= n2->number[i];

                if (sub >= 0) {
                    borrow = 0;
                    result->number[i] = sub;
                }
                else {
                    result->number[i] = 0x100 + sub; // 1 0000 0000
                    borrow = 1;
                }
            }
            big_int_remove_zeroes(result);
            return result;
        }
        else {
            big_int* result = big_int_sub(n2, n1);
            if (!result) return NULL;
            result->sign = !result->sign;
            return result;
        }
    }
    else {
        ((big_int*)n2)->sign = !n2->sign;
        big_int* result = big_int_add(n1, n2);
        ((big_int*)n2)->sign = !n2->sign;
        return result;
    }
    return NULL;
}

big_int* big_int_shift_right(const big_int* num, ll n) {
    if (!num || n < 0) return NULL;
    
    ll bytes_shift = n / 8;
    ll bits_shift = n % 8;

    if (bytes_shift >= num->length) {
        big_int* zero = big_int_get("0");
        if (!zero) return NULL;
        return zero;
    }

    big_int* new_num = big_int_copy(num);
    new_num->length -= bytes_shift;
    memmove(new_num->number, new_num->number + bytes_shift, new_num->length);

    if (bits_shift == 0) {
        return new_num;
    }

    unsigned char borrow = 0;
    unsigned char current;

    for (int i = new_num->length - 1; i >= 0; i--) {
        current = new_num->number[i];
        new_num->number[i] = (current >> bits_shift) | (borrow << (8 - bits_shift));
        borrow = current & ((1 << bits_shift) - 1);
    }
    big_int_remove_zeroes(new_num);
    return new_num;
}

big_int* big_int_shift_left(const big_int* num, ll n) {
    if (!num || n < 0) return big_int_get("0");

    ll bytes_shift = n / 8;
    ll bits_shift = n % 8;

    size_t new_length = num->length + bytes_shift + (bits_shift ? 1 : 0);

    big_int* new_num = big_int_copy(num);
    if (!new_num) return NULL;

    unsigned char* temp = (unsigned char*)realloc(new_num->number, new_length * sizeof(unsigned char));
    if (!temp) {
        big_int_free(new_num);
        return big_int_get("0");
    }
    new_num->number = temp;

    if (bits_shift > 0) {
        memset(new_num->number + num->length + bytes_shift, 0, sizeof(unsigned char));
    }   
    if (bytes_shift > 0) {
        memmove(new_num->number + bytes_shift, new_num->number, num->length);
        memset(new_num->number, 0, bytes_shift);
    }

    if (bits_shift > 0) {
        for (size_t i = new_length - 1; i > bytes_shift; i--) {
            new_num->number[i] = (new_num->number[i] << bits_shift) | (new_num->number[i - 1] >> (8 - bits_shift));
        }
        new_num->number[bytes_shift] <<= bits_shift;
    }
    new_num->length = new_length;

    big_int_remove_zeroes(new_num);
    return new_num;
    
}

void big_int_remove_zeroes(big_int* num) {
    if (!num) return;

    int zeroes = 0;
    for (int i = num->length - 1; i >= 0 && num->number[i] == 0; i--) zeroes++;

    if (!zeroes) return;

    if (zeroes == num->length) {
        num->length = 1;
        num->number[0] = 0;
        num->sign = false;
        return;
    }

    if (zeroes > 0) {
        size_t new_len = num->length - zeroes;
        unsigned char* new_num = (unsigned char*)realloc(num->number, new_len * sizeof(unsigned char));
        if (!new_num) {
            num->length = new_len;
            return;
        }
        num->number = new_num;
        num->length = new_len;
    }
}

big_int* big_int_abs(const big_int* n) {
    if (!n) return NULL;

    big_int* copy = big_int_copy(n);
    if (!copy) return NULL;

    copy->sign = false;

    return copy;
}

bool big_int_eq(const big_int* n1, const big_int* n2) {
    if (!n1 || !n2 || n1->sign != n2->sign || n1->length != n2->length) return false;

    for (size_t i = 0; i < n1->length; i++) {
        if (n1->number[i] != n2->number[i]) return false;
    }
    return true;
}

big_int* big_int_mul(const big_int* n1, const big_int* n2){
    if (!n1 || !n2) return big_int_get("0");

    size_t new_length = n1->length + n2->length;

    big_int* result = (big_int*)malloc(sizeof(big_int));
    if (!result) return NULL;
    result->length = new_length;

    result->number = (unsigned char*)calloc(result->length, sizeof(unsigned char));
    if (!result->number) {
        free(result);
        return big_int_get("0");
    }

    result->sign = n1->sign ^ n2->sign;
    for (size_t i = 0; i < n1->length; i++) {
        for (size_t j = 0; j < n2->length; j++) {
            unsigned short mult = n1->number[i] * n2->number[j];
            unsigned short carry = (result->number[i + j] + mult) >> 8;
            result->number[i + j] += mult;
            int k = 1;
            while (carry) {
                unsigned short new_carry = (result->number[i + j + k] + carry) >> 8;
                result->number[i + j + k] += carry;
                carry = new_carry;
                k++;
            }
        }
    }
    big_int_remove_zeroes(result);
    return result;
}

big_int* big_int_euclid_binary(const big_int* x, const big_int* y) {
    if (!x || !y) return big_int_get("0");

    big_int* a = big_int_abs(x);
    big_int* b = big_int_abs(y);
    if (!a || !b) {
        big_int_free(a);
        big_int_free(b);
        return big_int_get("0");
    }

    big_int* zero = big_int_get("0");
    if (!zero) {
        big_int_free(a);
        big_int_free(b);
        return big_int_get("0");
    }

    if (big_int_eq(a, zero)) {
        big_int_free(zero);
        big_int_free(a);
        return b;
    }
    if (big_int_eq(b, zero)) {
        big_int_free(zero);
        big_int_free(b);
        return a;
    }

    int power = 0;
    while (!(b->number[0] & 1) && !(a->number[0] & 1)) {
        big_int_shift_right_void(&a, 1);
        big_int_shift_right_void(&b, 1);
        if (!a || !b) {
            big_int_free(a);
            big_int_free(b);
            return zero;
        }
        power++;
    }


    while (!big_int_eq(zero, a)) {
        while (!(b->number[0] & 1)) {
            big_int_shift_right_void(&b, 1);
            if (!b) {
                big_int_free(a);
                return zero;
            }
        }
        while (!(a->number[0] & 1)) {
            big_int_shift_right_void(&a, 1);
            if (!a) {
                big_int_free(b);
                return zero;
            }
        }
        if (!big_int_geq(a, b)) {
            swap(a, b);
        }
        big_int_sub_void(&a, b);
        if (!a) {
            big_int_free(b);
            return zero;
        }
    }
    big_int_shift_left_void(&b, power);
    big_int_free(a);
    if (!b) {
        return zero;
    }
    big_int_free(zero);

    return b;
}

void big_int_div_by_sub(const big_int* n1, const big_int* n2, big_int** quotient, big_int** remainder) {
    if (!n1 || !n2 || big_int_eq(n2, big_int_get("0"))) {
        *quotient = big_int_get("0");
        *remainder = big_int_get("0");
        return;
    }

    big_int* r = big_int_abs(n1);
    big_int* q = big_int_get("0");
    q->sign = false;
    if (!r || !q) {
        big_int_free(r);
        big_int_free(q);
        return;
    }

    big_int* b = big_int_abs(n2);
    if (!b) {
        big_int_free(r);
        big_int_free(q);
        return;
    }

    big_int* one = big_int_get("1");
    if (!one) {
        big_int_free(r);
        big_int_free(q);
        big_int_free(b);
        return;
    }

    big_int* tmp_r = nullptr;
    big_int* tmp_q = nullptr;

    while (big_int_geq(r, b)) {
        big_int_sub_void(&r, b);
        big_int_add_void(&q, one);
        if (!r || !q) {
            big_int_free(r);
            big_int_free(q);
            big_int_free(b);
            return;
        }
    }

    if (n1->sign && !big_int_eq(r, big_int_get("0"))) {
        big_int_sub_void(&r, b);
        big_int_add_void(&q, one);
        if (!r || !q) {
            big_int_free(r);
            big_int_free(q);
            big_int_free(b);
            return;
        }
    }

    big_int_free(b);
    big_int_free(one);
    q->sign = !big_int_eq(q, big_int_get("0")) ? n1->sign ^ n2->sign : false;
    r->sign = false;
    *quotient = q;
    *remainder = r;
    return;
}

big_int* big_int_mod_pow(const big_int* base, const big_int* exponent, const big_int* mod) {
    if (!base || !exponent || !mod) return NULL;

    big_int* result = big_int_get("1");
    if (!result) return NULL;

    big_int* base_copy = big_int_copy(base);
    if (!base_copy) {
        big_int_free(result);
        return NULL;
    }

    big_int* exp_copy = big_int_copy(exponent);
    if (!exp_copy) {
        big_int_free(result);
        big_int_free(base_copy);
        return NULL;
    }

    big_int* rem = big_int_mod(base_copy, mod);
    if (!rem) {
        big_int_free(result);
        big_int_free(base_copy);
        big_int_free(exp_copy);
        return NULL;
    }
    base_copy = rem;
    
    while (!big_int_eq(exp_copy, big_int_get("0"))) {
        big_int* tmp = nullptr;

        if (exp_copy->number[0] & 1) {
            tmp = big_int_mul(result, base_copy);
            big_int* tmpmod = big_int_mod(tmp, mod);
            if (!tmpmod) {
                big_int_free(result);
                big_int_free(base_copy);
                big_int_free(exp_copy);
                return NULL;
            }
            big_int_free(result);
            result = tmpmod;
            big_int_free(tmp);
        }

        tmp = big_int_mul(base_copy, base_copy);
        big_int* tmpmod = big_int_mod(tmp, mod);
        if (!tmpmod) {
            big_int_free(result);
            big_int_free(base_copy);
            big_int_free(exp_copy);
            return NULL;
        }
        big_int_free(base_copy);
        base_copy = tmpmod;
        big_int_free(tmp);

        big_int_shift_right_void(&exp_copy, 1);
    }
    big_int_free(base_copy);
    big_int_free(exp_copy);

    return result;
}

void big_int_add_void(big_int** n1, const big_int* n2) {
    if (!n1 || !n2) return;

    big_int* temp = big_int_add(*n1, n2);
    if (!temp) return;

    big_int_free(*n1);
    *n1 = temp;
}

void big_int_sub_void(big_int** n1, const big_int* n2) {
    if (!n1 || !n2) return;

    big_int* temp = big_int_sub(*n1, n2);
    if (!temp) return;

    big_int_free(*n1);
    *n1 = temp;
}

void big_int_shift_right_void(big_int** num, ll n) {
    if (!num || n < 0) return;

    big_int* temp = big_int_shift_right(*num, n);
    if (!temp) return;

    big_int_free(*num);
    *num = temp;
}

void big_int_shift_left_void(big_int** num, ll n) {
    if (!num || n < 0) return;

    big_int* temp = big_int_shift_left(*num, n);
    if (!temp) return;

    big_int_free(*num);
    *num = temp;
}

void big_int_mul_void(big_int** n1, const big_int* n2) {
    if (!n1 || !n2) return;

    big_int* temp = big_int_mul(*n1, n2);
    if (!temp) return;

    big_int_free(*n1);
    *n1 = temp;
}

void big_int_set_length(big_int* num, const size_t new_length) {
    if (!num) return;

    unsigned char* resized_number = (unsigned char*)realloc(num->number, new_length * sizeof(unsigned char));

    if (!resized_number) {
        big_int_free(num);
        return;
    }

    if (new_length > num->length) {
        size_t fill_length = new_length - num->length;
        memset(resized_number + num->length, 0, fill_length);
    }

    num->number = resized_number;
    num->length = new_length;
}

void big_int_div(const big_int* num1, const big_int* num2, big_int** quotient, big_int** remainder) {
    if (!num1 || !num2) return;

    if (big_int_eq(num2, big_int_get("0"))) return;

    big_int* q = big_int_get("0");
    big_int* r = big_int_get("0");
    if (!q || !r) {
        big_int_free(q);
        big_int_free(r);
        return;
    }

    big_int_set_length(q, num1->length);

    const size_t total_bits = num1->length << 3;

    big_int* a = big_int_abs(num1);
    big_int* b = big_int_abs(num2);
    if (!a || !b) {
        big_int_free(a);
        big_int_free(b);
        big_int_free(q);
        big_int_free(r);
        return;
    }

    for (int i = total_bits - 1; i >= 0; --i) {
        big_int_shift_left_void(&r, 1);  
        if (!r) {
            big_int_free(a);
            big_int_free(b);
            big_int_free(q);
            return;
        }
        r->number[0] |= ((num1->number[i >> 3] >> (i & 7)) & 1);  

        if (big_int_geq(r, b)) {
            big_int_sub_void(&r, b);
            if (!r) {
                big_int_free(a);
                big_int_free(b);
                big_int_free(q);
                return;
            }
            q->number[i >> 3] |= (1 << (i & 7));
        }
    }

    if (num1->sign && !big_int_eq(r, big_int_get("0"))) {
        big_int_sub_void(&r, b);
        big_int_add_void(&q, big_int_get("1"));
        if (!r || !q) {
            big_int_free(a);
            big_int_free(b);
            big_int_free(q);
            big_int_free(r);
            return;
        }
    }
    q->sign = false;
    q->sign = !big_int_eq(q, big_int_get("0")) ? num1->sign ^ num2->sign : false;
    r->sign = false;
    big_int_free(a);
    big_int_free(b);
    big_int_remove_zeroes(q);
    big_int_remove_zeroes(r);
    *quotient = q;
    *remainder = r;
}

big_int* big_int_mod(const big_int* n1, const big_int* n2) {
    if (!n1 || !n2) return NULL;

    big_int* quotient = nullptr;
    big_int* reminder = nullptr;
    big_int_div(n1, n2, &quotient, &reminder);
    big_int_free(quotient);

    return reminder;
}

big_int* big_int_div_quotient(const big_int* n1, const big_int* n2) {
    if (!n1 || !n2) return NULL;

    big_int* quotient = nullptr;
    big_int* reminder = nullptr;
    big_int_div(n1, n2, &quotient, &reminder);
    big_int_free(reminder);
    
    return quotient;
}

big_int* big_int_bitwise_and(const big_int* n1, const big_int* n2) {
    if (!n1 || !n2) return NULL;

    size_t new_length = n1->length < n2->length ? n1->length : n2->length;

    big_int* result = (big_int*)malloc(sizeof(big_int));
    if (!result) return NULL;

    result->length = new_length;
    result->number = (unsigned char*)calloc(result->length, sizeof(unsigned char));
    if (!result->number) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < new_length; i++) {
        result->number[i] = n1->number[i] & n2->number[i];
    }
    result->sign = n1->sign && n2->sign;
    big_int_remove_zeroes(result);
    return result;
}

big_int* big_int_lr_mod_pow(const char base, const big_int* exponent, const big_int* mod) {
    if (!base || !exponent || !mod) return NULL;

    big_int* result = big_int_get(base - '0');
    if (!result) return NULL;
    big_int* zero = big_int_get("0");
    if (!zero) {
        big_int_free(result);
        return NULL;
    }
    const size_t total_bits = exponent->length << 3;
    bool c = false;
    for (int i = total_bits - 1; i >= 0; --i) {
        if (c) {
            big_int_mul_void(&result, result);
            big_int* rm = big_int_mod(result, mod);
            if (!rm) {
                big_int_free(result);
                return NULL;
            }
            big_int_free(result);
            result = rm;

            if ((exponent->number[i >> 3] >> (i & 7)) & 1) {
                big_int* tmp = big_int_get("0");
                for (char counter = 0; counter < base - 1 - '0'; counter++) {
                    big_int_add_void(&tmp, result);
                }
                big_int_add_void(&result, tmp);
                rm = big_int_mod(result, mod);
                if (!rm) {
                    big_int_free(result);
                    return NULL;
                }
                big_int_free(result);
                result = rm;
            }
            continue;;
        }
        if ((exponent->number[i >> 3] >> (i & 7)) & 1) c = true;
    }

    return result;
}

big_int* big_int_lr_mod_pow(const big_int* base, const big_int* exponent, const big_int* mod) {
    if (!base || !exponent || !mod) return NULL;

    big_int* result = big_int_mod(base, mod);
    if (!result) return NULL;
    big_int* zero = big_int_get("0");
    if (!zero) {
        big_int_free(result);
        return NULL;
    }
    const size_t total_bits = exponent->length << 3;
    bool c = false;
    for (int i = total_bits - 1; i >= 0; --i) {
        if (c) {
            big_int_mul_void(&result, result);
            big_int* rm = big_int_mod(result, mod);
            if (!rm) {
                big_int_free(result);
                return NULL;
            }
            big_int_free(result);
            result = rm;

            if ((exponent->number[i >> 3] >> (i & 7)) & 1) {
                big_int_mul_void(&result, base); // add result base times 
                rm = big_int_mod(result, mod);
                if (!rm) {
                    big_int_free(result);
                    return NULL;
                }
                big_int_free(result);
                result = rm;
            }
            continue;
        }
        if ((exponent->number[i >> 3] >> (i & 7)) &1) c = true;
    }

    return result;
}

void big_int_print_decimal(const big_int* num) {
    if (!num) return;

    if (num->length == 1 && num->number[0] == 0) {
        cout << ("0\n");
        return;
    }

    char* dec = (char*)calloc(num->length * 3, sizeof(char));
    if (!dec) return;
    big_int* copy = big_int_abs(num);
    if (!copy) {
        free(dec);
        return;
    }

    size_t dec_length = 0;
    big_int* zero = big_int_get("0");
    big_int* ten = big_int_get("1010");
    if (!zero || !ten) {
        big_int_free(copy);
        free(dec);
        return;
    }
    big_int* quotient;
    big_int* remainder;
    while (!big_int_eq(copy, zero)) {
        big_int_div(copy, ten, &quotient, &remainder);
        if (!quotient || !remainder) {
            big_int_free(copy);
            big_int_free(zero);
            big_int_free(ten);
            free(dec);
            return;
        }

        dec[dec_length++] = remainder->number[0] + '0';

        big_int_free(copy);
        big_int_free(remainder);
        copy = quotient;
    }

    if (num->sign) putchar('-');

    for (int i = dec_length - 1; i >= 0; i--) {
        putchar(dec[i]);
    }

    putchar('\n');

    big_int_free(copy);
    big_int_free(zero);
    big_int_free(ten);
    free(dec);
}

big_int* big_int_get_dec(const char* x) {
    if (!x) return NULL;

    big_int* res = big_int_get("0");
    if (!res) return NULL;

    big_int* ten = big_int_get("1010");
    if (!ten) {
        big_int_free(res);
        return NULL;
    }

    for (; *x; ++x) {
        if (*x == '-') {
            res->sign = true;
            continue;
        }

        if (!isdigit(*x)) {
            big_int_free(res);
            big_int_free(ten);
            return NULL;
        }

        unsigned char val = (unsigned char)(*x - '0');
        big_int* digit = big_int_get("0");
        digit->number[0] = val;

        big_int_mul_void(&res, ten);
        big_int_add_void(&res, digit);

        big_int_free(digit);
    }

    big_int_free(ten);
    return res;
}

big_int* big_int_slice(const big_int* n, size_t start, size_t end) {
    if (!n || end < start || end > n->length) return NULL;

    big_int* result = (big_int*)malloc(sizeof(big_int));
    if (!result) return NULL;

    result->length = end - start;
    result->number = (unsigned char*)calloc(result->length, sizeof(unsigned char));
    if (!result->number) {
        free(result);
        return NULL;
    }

    result->sign = n->sign;

    for (size_t i = 0; i < result->length; ++i) {
        result->number[i] = n->number[start + i];
    }

    return result;
}

big_int* big_int_mul_karatsuba(const big_int* n1, const big_int* n2) {
    if (!n1 || !n2) return NULL;

    if (n1->length + n2->length <= 100)  {
        return big_int_mul(n1, n2);
    }

    size_t x = (n1->length + n2->length) >> 2;
    big_int* a = big_int_shift_right(n1, x << 3);
    big_int* b = big_int_slice(n1, 0, x);
    big_int* c = big_int_shift_right(n2, x << 3);
    big_int* d = big_int_slice(n2, 0, x);

    big_int* ac = big_int_mul_karatsuba(a, c); /*(ac)*/

    big_int* bd = big_int_mul_karatsuba(b, d); /*(bd)*/
    big_int* sb = big_int_add(ac, bd); // (ac + bd)
    big_int_add_void(&a, b); // a + b
    big_int_add_void(&c, d); // c + d

    big_int* sm = big_int_mul_karatsuba(a, c); // (a + b) * (c + d)
    big_int_sub_void(&sm, sb); // sm = (a + b) * (c + d) - sb (sb = ac + bd)

    big_int_shift_left_void(&ac, 2 * (x << 3));
    big_int_shift_left_void(&sm, (x << 3));
    big_int_add_void(&sm, ac);
    big_int_add_void(&sm, bd);

    big_int_free(a);
    big_int_free(b);
    big_int_free(c);
    big_int_free(d);
    big_int_free(sb);
    big_int_free(ac);
    big_int_free(bd);

    sm->sign = !(big_int_eq(sm, big_int_get("0"))) ? n1->sign ^ n2->sign : false;
    return sm;
}

big_int* big_int_rnd(ll bytes_num) {
    big_int* x = (big_int*)malloc(sizeof(big_int));
    x->length = bytes_num;
    unsigned char* xnumber = (unsigned char*)malloc(x->length * sizeof(char));
    for (int i = 0; i < bytes_num; i++) {
        xnumber[i] = rand();
    }
    x->number = xnumber;
    x->sign = false;
    return x;
}
