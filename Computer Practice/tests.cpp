#include "tests.h"

using namespace std;

void test_euclid() {
	int a, b;
	cin >> a >> b;

    int resultEuclid = euclid(a, b);
    cout << "Наибольший общий делитель " << a << " и " << b << " с помощью обычного алгоритма Евклида равен " << resultEuclid << "\n";

    int resultEuclidRec = euclid_recursive(a, b);
    cout << "Наибольший общий делитель " << a << " и " << b << " с помощью рекурсивного алгоритма Евклида равен " << resultEuclidRec << "\n";

    int resultEuclidBinary = euclid_binary(a, b);
    cout << "Наибольший общий делитель " << a << " и " << b << " с помощью бинарного алгоритма Евклида равен " << resultEuclidBinary << "\n";
}

void test_mod_pow() {
    long long x, y, m;
    cin >> x >> y >> m;

    long long resultModPow = mod_pow(x, y, m);
    cout << "Результат возведения в степень по модулю " << x << "^" << y << " mod " << m << " с помощью функции mod_pow равен " << resultModPow << "\n";

    long long resultModPowRec = mod_pow_recursive(x, y, m);
    cout << "Результат возведения в степень по модулю " << x << "^" << y << " mod " << m << " с помощью функции mod_pow_recursive равен " << resultModPowRec << "\n";

    long long resultLrModPow = lr_mod_pow(x, y, m);
    cout << "Результат возведения в степень по модулю " << x << "^" << y << " mod " << m << " с помощью функции lr_mod_pow равен " << resultLrModPow << "\n";
}

void test_euclid_extended() {
    int a, b;
    cin >> a >> b;

    int x, y;

    int gcdEuclidExtended = euclid_extended_recursive(a, b, x, y);
    cout << "Наибольший общий делитель " << a << " и " << b << " с помощью расширенного алгоритма Евклида равен " << gcdEuclidExtended;
    cout << ", коэффициенты Безу: x = " << x << ", y = " << y << "\n";

    int gcdEuclidExtendedd = euclid_extended_iterative(a, b, x, y);
    cout << "Наибольший общий делитель " << a << " и " << b << " с помощью модифицированного расширенного алгоритма Евклида равен " << gcdEuclidExtendedd;
    cout << ", коэффициенты Безу: x = " << x << ", y = " << y << "\n";
}

void test_linear_diophantine() {
    int n;
    cin >> n;

    int* coefficients = new int[n];
    int* result = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> coefficients[i];
    }

    int target;
    cin >> target;

    int success = linear_diophantine(coefficients, n, result, target);
    if (success) {
        for (int j = 0; j < n; j++) {
            cout << "x" << j + 1 << " = " << result[j] << "\n";
        }
    }
    else {
        cout << "\\----\\\n";
    }

    delete[] coefficients;
    delete[] result;
}

void test_mul_inverse() {
    int num, mod_val;
    cin >> num >> mod_val;

    int result = mul_inverse(num, mod_val);

    if (result == 0) {
        cout << num << " ---- " << mod_val << "\n";
    }
    else {
        cout << "Inverse " << num << " mod " << mod_val << " = " << result << "\n";
    }
}

void test_chinese_reminder() {
    int num_equations;
    cin >> num_equations;

    int* remainders = (int*)malloc(num_equations * sizeof(int));
    int* modules = (int*)malloc(num_equations * sizeof(int));

    for (int i = 0; i < num_equations; i++) {
        cin >> remainders[i];
    }
    for (int i = 0; i < num_equations; i++) {
        cin >> modules[i];
    }

    int resultChineseReminderr = chinese_reminderr(remainders, modules, num_equations);
    cout << "Решение системы сравнений с помощью функции chinese_reminderr: " << resultChineseReminderr << "\n";

    int resultChineseReminder = chinese_reminder(remainders, modules, num_equations);
    if (resultChineseReminder == -1) {
        cout << "Система сравнений имеет неприводимые модули.\n";
    }
    else {
        cout << "Решение системы сравнений с помощью функции chinese_reminder: " << resultChineseReminder << "\n";
    }

    free(remainders);
    free(modules);
}

void test_big_int_functions() {
    char str1[1024];
    char str2[1024];
    cin >> str1;
    cin >> str2;

    big_int* num1 = big_int_get(str1);
    big_int* num2 = big_int_get(str2);

    cout << "Number 1: ";
    big_int_print(num1);
    cout << "Number 2: ";
    big_int_print(num2);

    big_int* abs1 = big_int_abs(num1);
    cout << "Absolute value of Number 1: ";
    big_int_print(abs1);

    big_int* abs2 = big_int_abs(num2);
    cout << "Absolute value of Number 2: ";
    big_int_print(abs2);

    big_int* copy1 = big_int_copy(num1);
    bool eq1 = big_int_eq(num1, copy1);
    cout << "Check for equality of Number 1 and its copy: " << (eq1 ? "Equal" : "Not equal") << endl;

    big_int* copy2 = big_int_copy(num2);
    bool eq2 = big_int_eq(num2, copy2);
    cout << "Check for equality of Number 2 and its copy: " << (eq2 ? "Equal" : "Not equal") << endl;

    big_int* sum = big_int_add(num1, num2);
    cout << "Sum: ";
    big_int_print(sum);

    big_int* difference = big_int_sub(num1, num2);
    cout << "Difference: ";
    big_int_print(difference);

    big_int* product = big_int_mul(num1, num2);
    cout << "Product: ";
    big_int_print(product);

    big_int* gcd = big_int_euclid_binary(num1, num2);
    cout << "GCD: ";
    big_int_print(gcd);

    big_int* shifted_left_num1 = big_int_shift_left(num1);
    cout << "Shift left for Number 1: ";
    big_int_print(shifted_left_num1);

    big_int* shifted_left_num2 = big_int_shift_left(num2);
    cout << "Shift left for Number 2: ";
    big_int_print(shifted_left_num2);

    big_int* shifted_right_num1 = big_int_shift_right(num1);
    cout << "Shift right for Number 1: ";
    big_int_print(shifted_right_num1);

    big_int* shifted_right_num2 = big_int_shift_right(num2);
    cout << "Shift right for Number 2: ";
    big_int_print(shifted_right_num2);

    bool geq = big_int_geq(num1, num2);
    cout << "Is big integer 1 greater than or equal to big integer 2? : " << (geq ? "Yes" : "No") << endl;
    bool geq_mod = big_int_abs_geq(num1, num2);
    cout << "Is absolute big integer 1 greater than or equal to absolute big integer 2? : " << (geq_mod ? "Yes" : "No") << endl;

    big_int_free(num1);
    big_int_free(num2);
    big_int_free(abs1);
    big_int_free(abs2);
    big_int_free(copy1);
    big_int_free(copy2);
    big_int_free(sum);
    big_int_free(difference);
    big_int_free(product);
    big_int_free(gcd);
    big_int_free(shifted_left_num1);
    big_int_free(shifted_left_num2);
    big_int_free(shifted_right_num1);
    big_int_free(shifted_right_num2);

    cout << "All tests completed." << endl;
}

void test_big_int_euclid_binary() {
    char str1[1024];
    char str2[1024];
    cin >> str1;
    cin >> str2;

    big_int* num1 = big_int_get(str1);
    big_int* num2 = big_int_get(str2);

    cout << "Number 1: ";
    big_int_print(num1);
    cout << "Number 2: ";
    big_int_print(num2);

    big_int* gcd = big_int_euclid_binary(num1, num2);
    cout << "GCD: ";
    big_int_print(gcd);

    big_int_free(num1);
    big_int_free(num2);
    big_int_free(gcd);

    cout << "Binary Euclidean algorithm test completed." << endl;
}

void subtraction_check() {
    std::ifstream in("input.txt");
    std::ifstream res("result.txt");

    std::string num1Str, num2Str, resStr;
    while (getline(in, num1Str, ' ') && getline(in, num2Str) && getline(res, resStr)) {
        big_int* num1 = big_int_get(num1Str.c_str());
        big_int* num2 = big_int_get(num2Str.c_str());
        big_int* expectedResult = big_int_get(resStr.c_str());

        big_int* actualResult = big_int_add(num1, num2);

        big_int_print(actualResult);
        std::cout << " = ";
        big_int_print(expectedResult);
        cout << '\n';

        big_int_free(num1);
        big_int_free(num2);
        big_int_free(actualResult);
        big_int_free(expectedResult);
    }

    in.close();
    res.close();
}

void test_big_int_shift_right() {
    // Открываем файлы input.txt и result.txt для чтения
    std::ifstream in("input.txt");
    std::ifstream res("result.txt");

    std::string numStr, resStr;

    // Проходим по каждой строке в файлах input.txt и result.txt
    while (getline(in, numStr) && getline(res, resStr)) {
        // Создаем представление big_int числа numStr и выполняем сдвиг вправо
        big_int* num = big_int_get(numStr.c_str());
        big_int* shiftedNum = big_int_shift_right(num);

        // Читаем верный результат из файла result.txt и создаем big_int представление этого результата
        big_int* expectedResult = big_int_get(resStr.c_str());

        big_int_print(shiftedNum);
        cout << " = ";
        big_int_print(expectedResult);
        cout << '\n';

        // Очищаем использованную память
        big_int_free(num);
        big_int_free(shiftedNum);
        big_int_free(expectedResult);
    }

    // Закрываем файлы
    in.close();
    res.close();
}

void test_big_int_shift_left() {
    // Открываем файлы input.txt и result.txt для чтения
    std::ifstream in("input.txt");
    std::ifstream res("result.txt");

    std::string numStr, resStr;

    // Проходим по каждой строке в файлах input.txt и result.txt
    while (getline(in, numStr) && getline(res, resStr)) {
        // Создаем представление big_int числа numStr и выполняем сдвиг вправо
        big_int* num = big_int_get(numStr.c_str());
        big_int* shiftedNum = big_int_shift_left(num);

        // Читаем верный результат из файла result.txt и создаем big_int представление этого результата
        big_int* expectedResult = big_int_get(resStr.c_str());

        cout << big_int_eq(shiftedNum, expectedResult) << '\n';
        // Очищаем использованную память
        big_int_free(num);
        big_int_free(shiftedNum);
        big_int_free(expectedResult);
    }

    // Закрываем файлы
    in.close();
    res.close();
}