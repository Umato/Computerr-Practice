#pragma once

int euclid(int a, int b);
int euclid_recursive(int a, int b);
int euclid_binary(int x, int y);
long long mod_pow(long long x, long long y, long long m);
long long mod_pow_recursive(long long x, long long y, long long m);
long long lr_mod_pow(long long x, long long y, long long m);
int euclid_extended_recursive(int a, int b, int& x, int& y);
int euclid_extended_iterative(int a, int b, int& x_0, int& y_0);
int linear_diophantine(int* a, const int n, int* res, int res_c);
int mul_inverse(int x, int m);
int chinese_reminder(const int* a, const int* m, int n);
int chinese_reminderr(const int* a, const int* m, int n);
