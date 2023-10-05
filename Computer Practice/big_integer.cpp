#include "big_integer.h"

using namespace std;

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
            big_int_free(num);
            return NULL;
        }
    }
    big_int_remove_zeroes(num);
    return num;
}

void big_int_print(const big_int* num) {
    if (!num) return;

    const int total_bits = num->length << 3;
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

big_int* big_int_shift_right(const big_int* num, int n) {
    if (!num || n <= 0) return NULL;
    
    int bytes_shift = n / 8;
    int bits_shift = n % 8;

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

big_int* big_int_shift_left(const big_int* num, int n) {
    if (!num || n <= 0) return NULL;
    
    int bytes_shift = n / 8;
    int bits_shift = n % 8;

    big_int* new_num = big_int_copy(num);
    if (!new_num) return NULL;

    new_num->length += bytes_shift;
    new_num->number = (unsigned char*)realloc(new_num->number, new_num->length * sizeof(unsigned char));))
    if (!new_num->number) {
        big_int_free(new_num);
        return big_int_get("0");
    }

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

big_int* big_int_mul(const big_int* n1, const big_int* n2)
{
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
        big_int* tmp_a = big_int_shift_right(a,1);
        big_int* tmp_b = big_int_shift_right(b,1);
        if (!tmp_a || !tmp_b) {
            big_int_free(a);
            big_int_free(b);
            big_int_free(tmp_a);
            big_int_free(tmp_b);
            return zero;
        }
        big_int_free(a);
        big_int_free(b);
        a = tmp_a;
        b = tmp_b;
        power++;
    }


    while (!big_int_eq(zero, a)) {
        while (!(b->number[0] & 1)) {
            big_int* tmp_b = big_int_shift_right(b,1);
            if (!tmp_b) {
                big_int_free(a);
                big_int_free(b);
                return zero;
            }
            big_int_free(b);
            b = tmp_b;
        }
        while (!(a->number[0] & 1)) {
            big_int* tmp_a = big_int_shift_right(a,1);
            if (!tmp_a) {
                big_int_free(a);
                big_int_free(b);
                return zero;
            }
            big_int_free(a);
            a = tmp_a;
        }
        if (!big_int_geq(a, b)) {
            swap(a, b);
        }
        big_int* tmp = big_int_sub(a, b);
        if (!tmp) {
            big_int_free(a);
            big_int_free(b);
            return zero;
        }
        big_int_free(a);
        a = tmp;
    }
    for (size_t i = 0; i < power; i++) {
        big_int* tmp = big_int_shift_left(b,1);
        if (!tmp) {
            big_int_free(a);
            big_int_free(b);
            return zero;
        }
        big_int_free(b);
        b = tmp;
    }
    big_int_free(zero);
    big_int_free(a);

    return b;
}

void big_int_div(const big_int* n1, const big_int* n2, big_int* quotient, big_int* remainder){

}   



//big_int* big_int_from_decimal(const char* str) {
//    if (!str) return NULL;
//
//    big_int* num = big_int_get("0");
//    if (!num) return NULL;
//
//    size_t l = strlen(str);
//
//}

