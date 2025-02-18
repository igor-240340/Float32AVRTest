﻿#pragma warning(disable : 4996)

#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <math.h>
#include <chrono>
#include <ctime>

void ftoae_v2(float num, char* str, bool debug);

void print_float_as_hex(float* a) {
    uint32_t intRep = *(uint32_t*)a;
    std::cout << std::hex << std::setfill('0') << std::setw(8) << intRep << std::endl;
}

void hex_to_float() {
    uint32_t x = 0x3f9d70a4;
    float f = *((float*)&x);
    std::cout << std::fixed << std::setprecision(200) << f << std::endl;

    float t1 = 1.1327648162841796875f;
    uint32_t t2 = *((uint32_t*)&t1);
    std::cout << std::hex << t2 << std::endl;
}

void loop_through_normalized_float() {
    float min = powf(2, -126);
    uint32_t minIntRep32 = *((uint32_t*)&min);
    std::cout << std::hex << std::setfill('0') << std::setw(8) << minIntRep32 << std::endl;

    float max = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 127);
    uint32_t maxIntRep32 = *((uint32_t*)&max);
    std::cout << std::hex << std::setfill('0') << std::setw(8) << maxIntRep32 << std::endl;

    std::cout << std::endl;

    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::cout << "started at " << std::ctime(&start_time);

    uint32_t cur = min;
    do {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << cur << std::endl;
    } while (++cur <= max);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished at " << std::ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s"
        << std::endl;
}

// Деление.
// Частное: бесконечная периодическая денормализованная дробь.
// Округление в большую.
void div_case_1() {
    float a = 1.0f;
    float b = (powl(2, 24) - 1) * powl(2, -23);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление
// Частное: бесконечная периодическая нормализованная дробь.
// Округление в меньшую.
void div_case_2() {
    float a = 1.688541412353515625f;
    float b = 1.00885009765625f;
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: конечная денормализованная дробь.
void div_case_3() {
    float a = 1.3125f;
    float b = 1.75f;
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: конечная нормализованная дробь.
void div_case_4() {
    float a = 1.6875f;
    float b = 1.5f;
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: единица, как результат деления делимого на себя.
void div_case_5() {
    float a = (powl(2, 24) - 1) * powl(2, -23);
    float b = a;
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: конечная нормализованная дробь (исходное значение делимого).
void div_case_6() {
    float a = (powl(2, 24) - 1) * powl(2, -23);
    float b = 1.0f;
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: нормализованная дробь.
// Разность экспонент: переполнение.
void div_case_7() {
    float a = 1.688541412353515625f * powl(2, 97);
    float b = 1.00885009765625f * powl(2, -95);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: нормализованная дробь.
// Разность экспонент: антипереполнение.
void div_case_8() {
    float a = 1.688541412353515625f * powl(2, -116);
    float b = 1.00885009765625f * powl(2, 20);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: денормализованная дробь.
// Разность экспонент: нет (анти)переполнение.
// Нормализация.
// Есть антипереполнение.
void div_case_9() {
    float a = 1.0f * powl(2, -96);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, 30);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: денормализованная дробь.
// Разность экспонент: есть переполнение.
// Нормализация.
// Нет переполнения.
void div_case_10() {
    float a = 1.0f * powl(2, 20);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, -108);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: нормализованная дробь.
// Разность экспонент: нет (анти)переполнения.
void div_case_11() {
    float a = 1.688541412353515625f * powl(2, 3);
    float b = 1.00885009765625f * powl(2, 106);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: денормализованная дробь.
// Разность экспонент: нет (анти)переполнение.
// Нормализация.
// Нет (анти)переполнения.
void div_case_12() {
    float a = 1.0f * powl(2, 3);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, 106);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: денормализованная дробь.
// Разность экспонент: есть переполнение.
// Нормализация.
// Есть переполнение.
void div_case_13() {
    float a = 1.0f * powl(2, 20);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, -109);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Деление.
// Частное: денормализованная дробь.
// Разность экспонент: есть антипереполнение.
// Нормализация.
// Есть антипереполнение.
void div_case_14() {
    float a = 1.0f * powl(2, -115);
    float b = (powl(2, 24) - 1) * powl(2, -23) * powl(2, 12);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Пример для случая, когда после денормализации мантиссы вправо на 1 разряд в случае антипереполнения
// последующее округление даёт бит переноса и возвращение в нормализованное состояние.
// Этот случай возможен только когда мантисса частного изначально получается нормализованной после деления.
void div_case_15_return_to_normal() {
    float a = (powf(2, 24) - 1) * powf(2, -23) * powf(2, -100);
    float b = 1.0f * powf(2, 27);
    float r = a / b;

    std::cout << std::fixed << std::setprecision(150) << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << r << std::endl;

    std::cout << "is subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение.
// Переполнение мантиссы.
// Точное.
// После нормализации округление не требуется.
void mul_case_1() {
    float a = 1.875f;
    float b = 1.5f;
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение.
// Переполнение мантиссы.
// Не точное.
// После нормализации округление в большую.
void mul_case_2() {
    float a = 1.25f;
    float b = 1.6000001430511474609375f;
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение.
// Переполнение мантиссы.
// Не точное.
// После нормализации округление в меньшую.
void mul_case_3() {
    float a = 1.5f;
    float b = 1.33333337306976318359375f;
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение.
// Переполнение мантиссы.
// Не точное.
// После нормализации округление симметричное в большую.
void mul_case_4() {
    float a = 1.9999992847442626953125f;
    float b = 1.5f;
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение.
// Переполнение мантиссы.
// Не точное.
// После нормализации округление симметричное в меньшую.
void mul_case_5() {
    float a = 1.9999997615814208984375f;
    float b = 1.5f;
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение.
// Переполнения мантиссы нет
// Не точное.
// Округление в большую.
// Переполнение при округлении.
void mul_case_6() {
    float a = ((powf(2, 24) - 1) - 1) * powf(2, -23); // В мантиссе все единицы, кроме младшего разряда.
    float b = 1 + powf(2, -23);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнение есть.
// Сумма экспонент: нет (анти)переполнения.
// Нормализация.
// Переполнение экспоненты есть.
void mul_case_7() {
    float a = 1.9999997615814208984375f * powf(2, 100);
    float b = 1.5f * powf(2, 27);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнение есть.
// Сумма экспонент: нет (анти)переполнения.
// Нормализация.
// Нет (анти)переполнения.
void mul_case_8() {
    float a = 1.9999997615814208984375f * powf(2, 100);
    float b = 1.5f * powf(2, 26);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнение есть.
// Сумма экспонент: есть переполнение.
// Нормализация.
// Есть переполнение.
void mul_case_9() {
    float a = 1.9999997615814208984375f * powf(2, 100);
    float b = 1.5f * powf(2, 28);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнение есть.
// Сумма экспонент: есть антипереполнение.
// Нормализация.
// Нет антипереполнения.
void mul_case_10() {
    float a = 1.9999997615814208984375f * powf(2, -100);
    float b = 1.5f * powf(2, -27);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнение есть.
// Сумма экспонент: есть антипереполнение.
// Нормализация.
// Есть антипереполнение.
void mul_case_11() {
    float a = 1.9999997615814208984375f * powf(2, -100);
    float b = 1.5f * powf(2, -28);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнения нет.
// Сумма экспонент: нет (анти)переполнения
// Округление: нет переполнения мантиссы.
void mul_case_12() {
    float a = 1.25f * powf(2, 100);
    float b = 1.33333337306976318359375f * powf(2, 27);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнения нет.
// Сумма экспонент: есть переполнение.
// Округление: есть переполнение.
// Нормализация.
// Есть переполнение.
void mul_case_13() {
    float a = 1.9999997615814208984375f * powf(2, 100);
    float b = 1.00000011920928955078125f * powf(2, 28);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнения нет.
// Сумма экспонент: есть антипереполнение.
// Округление: нет переполнения.
// Экспонента: есть антипереполнение.
void mul_case_14() {
    float a = 1.25f * powf(2, -126);
    float b = 1.33333337306976318359375f * powf(2, -25);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнения нет.
// Сумма экспонент: (анти)переполнения нет.
// Округление: переполнение мантиссы есть.
// Нормализация.
// Экспонента: переполнение есть.
void mul_case_15() {
    float a = ((powf(2, 24) - 1) - 1) * powf(2, -23) * powf(2, 100);
    float b = (1 + powf(2, -23)) * powf(2, 27);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнения нет.
// Сумма экспонент: (анти)переполнения нет.
// Округление: переполнение мантиссы есть.
// Нормализация.
// Экспонента: переполнения нет.
void mul_case_16() {
    float a = ((powf(2, 24) - 1) - 1) * powf(2, -23) * powf(2, 100);
    float b = (1 + powf(2, -23)) * powf(2, 26);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнения нет.
// Сумма экспонент: антипереполнение есть.
// Округление: переполнение мантиссы есть.
// Нормализация.
// Экспонента: антипереполнения нет.
void mul_case_17() {
    float a = ((powf(2, 24) - 1) - 1) * powf(2, -23) * powf(2, -100);
    float b = (1 + powf(2, -23)) * powf(2, -27);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Произведение мантисс: переполнения нет.
// Сумма экспонент: антипереполнение есть.
// Округление: переполнение мантиссы есть.
// Нормализация.
// Экспонента: антипереполнение есть.
void mul_case_18() {
    float a = ((powf(2, 24) - 1) - 1) * powf(2, -23) * powf(2, -100);
    float b = (1 + powf(2, -23)) * powf(2, -30);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Пример для случая, когда после денормализации мантиссы вправо на 1 разряд в случае антипереполнения
// последующее округление даёт бит переноса и возвращение в нормализованное состояние.
void mul_case_19_return_to_normal() {
    float a = (powf(2, 24) - 1) * powf(2, -23) * powf(2, -126);
    float b = 1.0f * powf(2, -1);
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Пример 20.
//
// BUGFIX:
// Этот пример даёт округление в меньшую сторону.
// В ветке округления после любого направления округления
// управление передавалось в код проверки переполнения при округлении.
// На этом примере с предыдущих операций остался бит переноса, который
// интерпретировался как переполнение при округлении (хотя фактически его и не было)
// что приводило к нормализации и коррекции экспоненты и следовательно к некорректному результату.
void mul_case_20_bugfix() {
    float a = powf(10, 10);
    float b = 10.0f;
    float r = a * b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Равные порядки, неравные мантиссы.
// Переполнение при сложении.
// Нормализация.
// Округление симметричное, в большую сторону.
void old_add_case_1() {
    float a = 1.99999988079071044921875f;
    float b = 1.0f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Равные порядки, неравные мантиссы.
// Переполнение при сложении.
// Нормализация.
// Округление симметричное, в меньшую сторону.
void old_add_case_2() {
    float a = 1.99999988079071044921875f - powf(2, -22);
    float b = 1.0f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Равные порядки, неравные мантиссы.
// Переполнение при сложении.
// Нормализация.
// Округление не требуется.
void old_add_case_3() {
    float a = 1.99999988079071044921875f - powf(2, -23);
    float b = 1.0f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Равные порядки, равные мантиссы.
// Переполнение при сложении.
// Нормализация.
// Округление не требуется.
void old_add_case_4() {
    float a = 1.99999988079071044921875f;
    float b = 1.99999988079071044921875f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Неравные порядки.
// Выравнивание порядков.
// Денормализация мантиссы B в отрезке [-1,-26].
// Округления мантиссы B до RGS нет.
// Переполнения при сложении нет.
// Округление в большую сторону.
// Переполнения при округлении нет.
void old_add_case_5() {
    float a = 1.5f;
    float b = 0.4999998509883880615234375f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Неравные порядки.
// Выравнивание порядков.
// Денормализация мантиссы B в отрезке [-1,-26].
// Округления мантиссы B до RGS нет.
// Переполнения при сложении нет.
// Округление в меньшую сторону.
// Переполнения при округлении нет.
void old_add_case_6() {
    float a = 1.5f;
    float b = 0.4999999105930328369140625f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Неравные порядки.
// Выравнивание порядков.
// Денормализация мантиссы B в отрезке [-1,-26].
// Округления мантиссы B до RGS нет.
// Переполнения при сложении нет.
// Округление в большую сторону.
// Переполнение при округлении есть.
void old_add_case_7() {
    float a = 1.5f;
    float b = 0.4999999701976776123046875f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Неравные порядки.
// Выравнивание порядков.
// Денормализация мантиссы B в отрезке [-1,-26].
// Округления мантиссы B до RGS нет.
// Переполнение при сложении есть.
// Нормализация.
// Округления мантиссы суммы до RGS нет.
// Округление в меньшую сторону.
// Переполнение при округлении не возможно.
void old_add_case_8() {
    float a = 1.99999988079071044921875f;
    float b = 0.4999999701976776123046875f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Неравные порядки.
// Выравнивание порядков.
// Денормализация мантиссы B в отрезке [-1,-26].
// Округления мантиссы B до RGS нет.
// Переполнение при сложении есть.
// Нормализация.
// Округление мантиссы суммы до RGS есть, в большую.
// Округление в меньшую сторону.
// Переполнение при округлении не возможно.
void old_add_case_9() {
    float a = 1.99999988079071044921875f;
    float b = (1.99999988079071044921875f - (powf(2, -20) + powf(2, -21) + powf(2, -22))) * powf(2, -3);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Неравные порядки.
// Выравнивание порядков.
// Денормализация мантиссы B в отрезке [-1,-26].
// Округления мантиссы B до RGS нет.
// Переполнение при сложении есть.
// Нормализация.
// Округление мантиссы суммы до RGS есть, в меньшую.
// Округление в меньшую сторону.
// Переполнение при округлении не возможно.
void old_add_case_10() {
    float a = 1.99999988079071044921875f;
    float b = 0.24999998509883880615234375f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Неравные порядки.
// Выравнивание порядков.
// Денормализация мантиссы B в отрезке [-1,-26].
// Округление мантиссы B до RGS есть, в большую.
// Переполнения при сложении нет.
// Округление в большую сторону.
// Переполнения при округлении нет.
void old_add_case_11() {
    float a = 1.99853503704071044921875f;
    float b = (1.99999988079071044921875f - (powf(2, -14) + powf(2, -15))) * powf(2, -11);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Неравные порядки.
// Выравнивание порядков.
// Денормализация мантиссы B в отрезке [-27,-253].
// Округление мантиссы B до RGS есть, в большую.
// Переполнение при сложении не возможно.
// Округление только в меньшую сторону.
// Переполнение при округлении не возможно.
void old_add_case_12() {
    float a = 1.99853503704071044921875f * powf(2, 127);
    float b = 1.99853503704071044921875f * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Проверка двух отрицательных.
void old_add_case_13() {
    float a = -1.01158893108367919921875f;
    float b = -0.00006100535028963349759578704833984375f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Проверка свопа.
void old_add_case_14() {
    float a = 1.99999988079071044921875f * powf(2, 5);
    float b = -1.5f * powf(2, 10);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Переполнение экспоненты при сложении.
void old_add_case_15() {
    float a = 1.99999988079071044921875f * powf(2, 127);
    float b = 1.99999988079071044921875f * powf(2, 125);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Переполнение экспоненты при округлении.
void old_add_case_16() {
    float a = 1.5f * powf(2, 127);
    float b = 1.99999988079071044921875f * powf(2, 125);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Одинаковые знаки, положительные.
// Неравные порядки.
// Выравнивание порядков.
// Денормализация мантиссы B в отрезке [-1,-26].
// Округления мантиссы B до RGS нет.
// Переполнения при сложении нет.
// Округление симметричное, в меньшую сторону.
// Переполнения при округлении нет.
// Переполнения экспоненты нет.
void old_add_case_17() {
    float a = 1.0f;
    float b = (1.99999988079071044921875f - powf(2, -22)) * powf(2, -1);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

//----------------------------------------------------------------------
// Алгебраическое сложение.
// Разные знаки.
// Равные порядки, равные мантиссы.
// Доп. код мантиссы B.
// Сложение.
// Нулевой результат.
void _add_case_17() {
    float a = 1.5f;
    float b = -1.5f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Разные знаки.
// Равные порядки, неравные мантиссы.
// Доп. код мантиссы B.
// Сложение.
// Денормализация есть, на 23 разряда.
// Нормализация.
// Округление не требуется.
// Антипереполнения экспоненты нет.
void _add_case_18() {
    float a = 1.0f + powf(2, -23);
    float b = -1.0f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Разные знаки.
// Равные порядки, неравные мантиссы.
// Доп. код мантиссы B.
// Сложение.
// Денормализация есть, на 23 разряда.
// Нормализация.
// Округление не требуется.
// Антипереполнение экспоненты есть.
void _add_case_19() {
    float a = (1.0f + powf(2, -23)) * powf(2, -126);
    float b = -1.0f * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 1.
void add_case_1() {
    float a = 1.99999988079071044921875f * powf(2, 127);
    float b = 1.99999988079071044921875f * powf(2, 127);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 2.
void add_case_2() {
    float a = 1.99999988079071044921875f * powf(2, -126);
    float b = 1.99999988079071044921875f * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 3.
void add_case_3() {
    float a = 1.0f * powf(2, 127);
    float b = (1.0f + powf(2, -22) + powf(2, -23)) * powf(2, 127);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 4.
void add_case_4() {
    float a = 1.0f * powf(2, -126);
    float b = (1.0f + powf(2, -22) + powf(2, -23)) * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 5.
void add_case_5() {
    float a = 1.0f * powf(2, 127);
    float b = (1.0f + powf(2, -23)) * powf(2, 127);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 6.
void add_case_6() {
    float a = 1.0f * powf(2, -126);
    float b = (1.0f + powf(2, -23)) * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 7.
void add_case_7() {
    float a = 1.0f * powf(2, 127);
    float b = (1.99999988079071044921875f - powf(2, -23)) * powf(2, 127);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 8.
void add_case_8() {
    float a = 1.0f * powf(2, -126);
    float b = (1.99999988079071044921875f - powf(2, -23)) * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 9.
void add_case_9() {
    float a = 1.99999988079071044921875f * powf(2, 127);
    float b = (1.99999988079071044921875f - powf(2, -14) - powf(2, -19) - powf(2, -21) - powf(2, -22)) * powf(2, 118);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 10.
void add_case_10() {
    float a = 1.99999988079071044921875f * powf(2, -117);
    float b = (1.99999988079071044921875f - powf(2, -14) - powf(2, -19) - powf(2, -21) - powf(2, -22)) * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 11.
void add_case_11() {
    float a = 1.99999988079071044921875f * powf(2, 127);
    float b = (1.99999988079071044921875f - powf(2, -19) - powf(2, -21) - powf(2, -22)) * powf(2, 118);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 12.
void add_case_12() {
    float a = 1.99999988079071044921875f * powf(2, -117);
    float b = (1.99999988079071044921875f - powf(2, -19) - powf(2, -22)) * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 13.
void add_case_13() {
    // сценарий с переполнением экспоненты - уже покрыт другим примером.
}

// Сложение.
// Ветка 14.
void add_case_14() {
    float a = 1.99609375f * powf(2, 126);
    float b = (1.99999988079071044921875f - powf(2, -19) - powf(2, -21) - powf(2, -22)) * powf(2, 117);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 15.
void add_case_15() {
    float a = 1.99609375f * powf(2, 127);
    float b = (1.99999988079071044921875f - powf(2, -14) - powf(2, -19) - powf(2, -21) - powf(2, -22)) * powf(2, 118);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 16.
void add_case_16() {
    float a = 1.99609375f * powf(2, 127);
    float b = (1.99999988079071044921875f - powf(2, -15) - powf(2, -19) - powf(2, -21)) * powf(2, 118);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 26.
void add_case_26() {
    float a = 1.99609375f * powf(2, 100);
    float b = 1.999969482421875f * powf(2, 92);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 36.
void add_case_36() {
    float a = 1.9921875f * powf(2, 100);
    float b = 1.9999847412109375f * powf(2, 92);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 40.
void add_case_40() {
    float a = 1.99999988079071044921875f * powf(2, 127);
    float b = 1.99999988079071044921875f * powf(2, 96);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 41.
void add_case_41() {
    float a = 1.99999988079071044921875f * powf(2, 127);
    float b = 1.99999988079071044921875f * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Сложение.
// Ветка 42.
void add_case_42() {
    float a = -1.01158893108367919921875f;
    float b = -0.00006100535028963349759578704833984375f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 0.
void add_case_neg_0() {
    float a = 1.99999988079071044921875f;
    float b = -1.99999988079071044921875f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 1.
void add_case_neg_1() {
    float a = 1.00000011920928955078125f * powf(2, -126);
    float b = -1.0f * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 2.
void add_case_neg_2() {
    float a = 1.99999988079071044921875f * powf(2, -125);
    float b = -1.0f * powf(2, -125);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 4.
void add_case_neg_4() {
    float a = 1.0f * powf(2, -102);
    float b = -1.99999988079071044921875f * powf(2, -103);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 5.
void add_case_neg_5() {
    float a = 1.5000002384185791015625f;
    float b = -1.00000011920928955078125f * powf(2, -1);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 6.
void add_case_neg_6() {
    float a = 1.50000011920928955078125f;
    float b = -1.00000011920928955078125f * powf(2, -1);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 8.
void add_case_neg_8() {
    float a = 1.0f * powf(2, 127);
    float b = -1.93750011920928955078125f * powf(2, 101);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 10.
void add_case_neg_10() {
    float a = 1.0f * powf(2, -102);
    float b = -1.48437511920928955078125f * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 12.
void add_case_neg_12() {
    float a = 1.0f * powf(2, -101);
    float b = -1.48437511920928955078125f * powf(2, -126);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 20.
void add_case_neg_20() {
    float a = 1.0f;
    float b = -1.0f * powf(2, -25);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 33.
void add_case_neg_33() {
    float a = 1.5f;
    float b = -1.0f * powf(2, -31);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 34.
void add_case_neg_34() {
    float a = 1.0f;
    float b = -1.0f * powf(2, -32);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение. Второй операнд отрицательный.
// Ветка 36.
void add_case_neg_36() {
    float a = -10.0f;
    float b = 5.0f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Вычитание. Оба операнда отрицательные.
// Пример 1.
// NOTE: пример был добавлен, поскольку обнаружилась проблема с вычислением знака в FSUB32 в float32avr.
void fsub_case_1() {
    float a = -12.0f;
    float b = -14.0f;
    float r = a - b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Вычитание. Первый операнд отрицательный, второй - положительный.
// Пример 2.
// NOTE: пример был добавлен, поскольку обнаружилась проблема с вычислением знака в FSUB32 в float32avr.
void fsub_case_2() {
    float a = -12.0f;
    float b = 14.0f;
    float r = a - b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Проверка механики свопа, когда первый аргумент по модулю меньше второго.
void fadd_swap() {
    float a = 1.99999988079071044921875f * powf(2, 5);
    float b = -1.5f * powf(2, 10);
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Оба операнда равны нулю.
void fadd_zero_zero() {
    float a = 0.0f;
    float b = a;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Только первый операнд равен нулю.
void fadd_zero_nonzero() {
    float a = 0.0f;
    float b = -1.99999988079071044921875f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Алгебраическое сложение.
// Только второй операнд равен нулю.
void fadd_nonzero_zero() {
    float a = 1.99999988079071044921875f;
    float b = 0.0f;
    float r = a + b;

    std::cout << std::fixed << std::setprecision(150) << "a=" << a << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "b=" << b << std::endl;
    std::cout << std::fixed << std::setprecision(150) << "r=" << r << std::endl;

    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(r) << std::endl;

    std::cout << std::endl;

    print_float_as_hex(&a);
    print_float_as_hex(&b);
    print_float_as_hex(&r);
}

// Пример, в котором A>B, но A-B даст нулевую разность, если нет поддержки денормализованных чисел.
// К вопросу о том, почему при сравнении двух флоатов на равенство лучше вычислять разность их целочисленных упакованных
// представлений, нежели их разность непосредственно во float.
void zero_diff() {
    float a = ((1 + powf(2, -23)) * powf(2, -126));
    std::cout << std::fixed << std::setprecision(100) << a << "\n";
    print_float_as_hex(&a);
    std::cout << '\n';

    float b = powf(2, -126);
    std::cout << std::fixed << std::setprecision(100) << b << "\n";
    print_float_as_hex(&b);
    std::cout << '\n';

    float c = a - b;
    std::cout << std::fixed << std::setprecision(100) << c << "\n";
    print_float_as_hex(&c);
}

//
// Реализация из z88dk [https://z88dk.org/site/].
// Версия с float и нашими модификациями: "лишний" код, устранение переполнения для граничного случая.
//
// NOTE: эта версия (также, как и оригинальная реализация для double и float) больше не является актуальной,
// поскольку имеет проблемы с нормализацией, поэтому
// она была заменена на ftoan.
void ftoa_float_mod(float num, int precision, char* str, bool debug = true) {
    float order;
    int i;
    int digit;

    if (num < 0.0f) {
        *str++ = '-';
        num = -num;
    }
    i = 1;
    order = 1.0f;
    float numDownScale = num / 10.0f; // Чтобы избежать переполнения.

    while (numDownScale >= order) {
        order *= 10.0f;
        i++;
    }

    // begin: debug.
    if (debug) {
        std::cout << "order:\t";
        print_float_as_hex(&order);
    }
    // end: debug.

    while (i--) {
        // begin: debug.
        if (debug) {
            std::cout << "\nnum/order:\t";
            float num_order = num / order;
            print_float_as_hex(&num_order);
        }
        // end: debug.

        digit = num / order;
        *str++ = digit + '0';

        // begin: debug.
        if (debug) {
            std::cout << "(float)digit:\t";
            float digit_float = (float)digit;
            print_float_as_hex(&digit_float);
        }
        // end: debug.

        // begin: debug.
        if (debug) {
            std::cout << "digit*order:\t";
            float digit_order = (float)digit * order;
            print_float_as_hex(&digit_order);
        }
        // end: debug.

        num = num - ((float)digit * order);
        //order = order * 0.1f;
        // В float32avr умножение и деление эквивалентны в плане алгоритмической сложности, поэтому используем просто деление.
        // В эталонной реализации тоже меняем на деление для сверки результатов.
        order = order / 10.0f;

        // begin: debug.
        if (debug) {
            std::cout << "num-(d*order):\t";
            print_float_as_hex(&num);
        }
        // end: debug.

        // begin: debug.
        if (debug) {
            std::cout << "order/10:\t";
            print_float_as_hex(&order);
        }
        // end: debug.
    }
    if (precision <= 0) {
        *str = 0;
        return;
    }
    *str++ = '.';

    // begin: debug.
    if (debug) {
        std::cout << "\nnum:\t";
        print_float_as_hex(&num);
    }
    // end: debug.

    while (precision--) {
        num *= 10.0f;

        // begin: debug.
        if (debug) {
            std::cout << "\nnum*=10.0f:\t";
            print_float_as_hex(&num);
        }
        // end: debug.

        digit = num;
        *str++ = digit + '0';

        num -= (float)digit;

        // begin: debug.
        if (debug) {
            std::cout << "num-=digit:\t";
            print_float_as_hex(&num);
        }
        // end: debug.
    }
    *str = 0;
}

//
// Реализация основана на z88dk [https://github.com/z88dk/z88dk/blob/master/libsrc/math/genmath/ftoa.c].
// 
// NOTE: это финальная версия, которая принимает только нормализованные десятичные числа.
// Оригинальная версия и версия с нашими модификациями (ftoa_float_mod) не во всех случаях дают корректную нормализацию из-за ошибок округления,
// что приводит к извлечению некорректного числового знака.
void ftoan(float num, int precision, char* str, bool debug = true) {
    float order;
    int i;
    int digit;

    if (num < 0.0f) {
        *str++ = '-';
        num = -num;
    }
    i = 1;

    // begin: debug.
    if (debug) {
        std::cout << "order:\t";
        print_float_as_hex(&order);
    }
    // end: debug.

    digit = num;
    *str++ = digit + '0';

    // begin: debug.
    if (debug) {
        std::cout << "(float)digit:\t";
        float digit_float = (float)digit;
        print_float_as_hex(&digit_float);
    }
    // end: debug.

    num = num - (float)digit;

    // begin: debug.
    if (debug) {
        std::cout << "num-digit:\t";
        print_float_as_hex(&num);
    }
    // end: debug.


    *str++ = '.';

    // begin: debug.
    if (debug) {
        std::cout << "\nnum:\t";
        print_float_as_hex(&num);
    }
    // end: debug.

    while (precision--) {
        num *= 10.0f;

        // begin: debug.
        if (debug) {
            std::cout << "\nnum*=10.0f:\t";
            print_float_as_hex(&num);
        }
        // end: debug.

        digit = num;
        *str++ = digit + '0';

        num -= (float)digit;

        // begin: debug.
        if (debug) {
            std::cout << "num-=digit:\t";
            print_float_as_hex(&num);
        }
        // end: debug.
    }
    *str = 0;
}

//
// Модифицированная реализация atof from K&R, но только в пределах float.
float atof_kr_float(char s[], bool debug = true) {
    float num, overscale;
    int i = 0, sign = 1;

    if (s[0] == '-') {
        sign = -1;
        i++;
    }

    // begin: отладка atof_case_7().
    //float val2 = 0.0f;
    // end: отладка atof_case_7().

    if (debug) {
        std::cout << "\ninteger part:\n";
    }

    for (num = 0.0f; isdigit(s[i]); i++) {
        // begin: отладка atof_case_7().
        /*std::cout << "val:               \t" << std::fixed << std::setprecision(152) << val << '\n';
        std::cout << "10.0f * val:       \t" << std::fixed << std::setprecision(152) << 10.0f * val << '\n';
        std::cout << "10.0f * val + s[i]:\t" << std::fixed << std::setprecision(152) << 10.0f * val + (s[i] - '0') << '\n';
        val = 10.0f * val + (s[i] - '0');
        std::cout << "val :\t" << std::fixed << std::setprecision(152) << val << '\n';

        std::cout << '\n';

        std::cout << "val2:              \t" << std::fixed << std::setprecision(152) << val2 << '\n';
        std::cout << "10.0 * val2:       \t" << std::fixed << std::setprecision(152) << 10.0 * val2 << '\n';
        std::cout << "10.0 * val2 + s[i]:\t" << std::fixed << std::setprecision(152) << 10.0 * val2 + (s[i] - '0') << '\n';
        val2 = 10.0 * val2 + (s[i] - '0');
        std::cout << "val2 :\t" << std::fixed << std::setprecision(152) << val2 << '\n';

        std::cout << "---------------------\n";*/
        // end: отладка atof_case_7().

        if (debug) {
            // begin: debug.
            std::cout << "10.0f * num:        \t";
            float t = 10.0f * num;
            print_float_as_hex(&t);
            // end: debug.

            // begin: debug.
            std::cout << "float(digit):       \t";
            t = (s[i] - '0');
            print_float_as_hex(&t);
            // end: debug.
        }

        num = 10.0f * num + (s[i] - '0');

        // begin: debug.
        if (debug) {
            std::cout << "10.0f * num + digit:\t";
            print_float_as_hex(&num);
            std::cout << '\n';
        }
        // end: debug.
    }

    if (s[i] == '.')
        i++;

    if (debug) {
        std::cout << "\nfractional part:\n";
    }

    for (overscale = 1.0f; isdigit(s[i]); i++) {
        if (debug) {
            // begin: debug.
            std::cout << "10.0f * num:        \t";
            float t = 10.0f * num;
            print_float_as_hex(&t);
            // end: debug.

            // begin: debug.
            std::cout << "overscale:          \t";
            print_float_as_hex(&overscale);
            // end: debug.

            // begin: debug.
            std::cout << "overscale*=10.0f:   \t";
            t = overscale * 10.0f;
            print_float_as_hex(&t);
            // end: debug.

            // begin: debug.
            std::cout << "float(digit):       \t";
            t = (s[i] - '0');
            print_float_as_hex(&t);
            // end: debug.
        }

        num = 10.0f * num + (s[i] - '0');
        overscale *= 10.0f;

        // begin: debug.
        if (debug) {
            std::cout << "10.0f * num + digit:\t";
            print_float_as_hex(&num);
            std::cout << '\n';
        }
        // end: debug.
    }

    return sign * num / overscale;
}

// К вопросу о различии эталонной десктопной реализации ftoa
// и реализации на AVR из-за того, что float32avr не поддерживает
// денормализованные числа.
void denormals_ftoa() {
    //float a = 1.0f + powf(2, -23);
    //float a = 1056.0f + powf(2, -23);
    float a = powf(2, -23) * powf(2, -126);
    /*float a = (powf(2, 23) - 1) * powf(2, -23) * powf(2, -126);
    float a = (powf(2, 23) - 1) * powf(2, -23) * powf(2, -126);*/
    std::cout << std::fixed << std::setprecision(200) << a << "\n";
    print_float_as_hex(&a);

    char str[255];
    ftoa_float_mod(a, 100, str);
    std::cout << str << '\n';

    /*std::cout << '\n';

    float b = a - 1.0f;
    std::cout << std::fixed << std::setprecision(100) << b << "\n";
    print_float_as_hex(&b);*/

    std::cout << '\n';

    float c = a * 10.0f;
    std::cout << std::fixed << std::setprecision(100) << c << "\n";
    print_float_as_hex(&c);
}

// Проверка ftoa.
// Пример 1.
void ftoa_float_mod_case_1() {
    float a = powf(2, -126);
    std::cout << std::fixed << std::setprecision(150) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoa_float_mod(a, 62, str);
    std::cout << str << '\n';
}

// Проверка ftoa.
// Пример 2.
void ftoa_float_mod_case_2() {
    float a = (powf(2, 24) - 1) * powf(2, -24);
    std::cout << std::fixed << std::setprecision(150) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoa_float_mod(a, 23, str);
    std::cout << str << '\n';
}

// Проверка ftoa
// Пример 3.
void ftoa_float_mod_case_3() {
    float a = 1.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoa_float_mod(a, 2, str);
    std::cout << '\n';
    std::cout << str << '\n';
}

// Проверка ftoa
// Пример 4.
void ftoa_float_mod_case_4() {
    float a = 10.0f - powf(2, -23) * powf(2, 3);
    std::cout << std::fixed << std::setprecision(100) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoa_float_mod(a, 22, str);
    std::cout << '\n';
    std::cout << str << '\n';
}

// Проверка ftoa
// Пример 5.
void ftoa_float_mod_case_5() {
    float a = 10.0f;
    std::cout << std::fixed << std::setprecision(100) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoa_float_mod(a, 2, str);
    std::cout << '\n';
    std::cout << str << '\n';
}

// Проверка ftoa
// Пример 6.
void ftoa_float_mod_case_6() {
    float a = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 127);
    std::cout << std::fixed << std::setprecision(150) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoa_float_mod(a, 21, str);
    std::cout << '\n';
    std::cout << str << '\n';
}

// Проверка ftoa
// Пример 7.
void ftoa_float_mod_case_7() {
    float a = -117926.1328125f;
    std::cout << std::fixed << std::setprecision(150) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoa_float_mod(a, 8, str);
    std::cout << '\n';
    std::cout << str << '\n';
}

// Проверка ftoa
// Пример 8.
void ftoa_float_mod_case_8() {
    float a = 0.0f;
    std::cout << std::fixed << std::setprecision(150) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoa_float_mod(a, 8, str);
    std::cout << '\n';
    std::cout << str << '\n';
}

// Проверка atof.
// Переполнение по overscale.
// Desktop: 0.
// float32avr: исключение.
void atof_case_0() {
    char num[] = "0.000000000000000000000000000000000000009";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof.
// Переполнения нет.
// Desktop: денормализованное.
// float32avr: 0.
void atof_case_1() {
    char num[] = "0.00000000000000000000000000000000000001";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof.
// Переполнения нет.
void atof_case_2() {
    char num[] = "0.00000000000000000000000000000000000002";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof.
// Переполнение по overscale.
// Desktop: 0.
// float32avr: исключение.
void atof_case_3() {
    char num[] = "0.340282429999999999999999999999999999999";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнения нет.
void atof_case_4() {
    char num[] = "3.40282429999999999999999999999999999999";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнения нет.
void atof_case_5() {
    char num[] = "340282429999999999.999999999999999999999";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнения нет.
// NOTE: хотя входное десятичное значение больше максимального значения представимого в одинарном float,
// в процессе конвертации из-за промежуточных округлений в итоге получается значение, которое помещается в одинарный float.
void atof_case_6() {
    char num[] = "340282429999999999999999999999999999999";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнение по num.
// Desktop: inf.
// float32avr: исключение.
void atof_case_7() {
    char num[] = "340282429999999999999999999999999999999.0";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнение по num и по overscale.
// Desktop: nan.
// float32avr: исключение при переполнении по num.
void atof_case_8() {
    char num[] = "0.340282430000000000000000000000000000000";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнение по num.
// Desktop: inf.
// float32avr: исключение.
void atof_case_9() {
    char num[] = "3.40282430000000000000000000000000000000";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнение по num.
// Desktop: inf.
// float32avr: исключение.
void atof_case_10() {
    char num[] = "3402824300000000.00000000000000000000000";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнение по num.
// Desktop: inf.
// float32avr: исключение.
void atof_case_11() {
    char num[] = "340282430000000000000000000000000000000";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнение по num.
// Desktop: inf.
// float32avr: исключение.
void atof_case_12() {
    char num[] = "11111111111111111.11111111111111111111119999";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << '\n';
}

// Проверка atof.
// Переполнения нет.
void atof_case_13() {
    char num[] = "297270070.293992768437644036421190501130";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof.
// Переполнения нет.
void atof_case_14() {
    char num[] = "406.93306";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof.
// Переполнения нет.
void atof_case_15() {
    char num[] = "70856.4138686531";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof.
// Переполнения нет.
void atof_case_16() {
    char num[] = "0";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof.
// Отрицательное значение.
void atof_case_17() {
    char num[] = "0.00";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof.
// Отрицательное значение.
void atof_case_18() {
    char num[] = "-16.123";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof.
// Отрицательный ноль.
void atof_case_19() {
    char num[] = "-0";
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Проверка atof
// Просто несколько примеров на разные граничные случаи.
void atof_sandbox() {
    char num[] = "0.00000000000000000000000000000000000001"; // Нет переполнения.
    //char num[] = "0.000000000000000000000000000000000000009"; // Переполнение только по overscale.
    //char num[] = "0.999999999999999999999999999999999999999"; // Переполнение по overscale и по num.
    //char num[] = "0.111111111111111111111111111111111111111"; // Переполнение только по overscale.
    //char num[] = "9.99999999999999999999999999999999999999"; // Переполнение только по num.
    //char num[] = "1.11111111111111111111111111111111111111"; // Нет переполнения.
    //char num[] = "0.340282429999999999999999999999999999999"; // Переполнение только по overscale.
    //char num[] = "3.40282429999999999999999999999999999999"; // Нет переполнения.
    //char num[] = "3.40282430000000000000000000000000000000"; // Переполнение только по num.
    //char num[] = "10000.0000000000000000000000000000000000"; // Нет переполнения.
    //char num[] = "10000.00000000000000000000000000000000000"; // Переполнение только по num.
    //char num[] = "340282429999999999999999999999999999999.0"; // Переполнение только по num.
    //char num[] = "340282429999999999999999999999999999999"; // Нет переполнения.
    //char num[] = "340282430000000000000000000000000000000"; // Переполнения только по num.
    std::cout << "string: " << num << '\n';
    float a = atof_kr_float(num);
    //float a = atof(num);
    std::cout << "float: " << std::fixed << std::setprecision(152) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a) << std::endl;
}

// Чтение клавиатуры.
void read_keypad_1() {
    char a_str[] = "0.5";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "0.6";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a * b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    ftoa_float_mod(c_float, 100, c_str, false);
    std::cout << "c_str: \"" << c_str << "\"" << '\n';
}

// Чтение клавиатуры.
void read_keypad_2() {
    char a_str[] = "-16.123";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "123.73";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float / b_float;
    std::cout << "a / b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    ftoa_float_mod(c_float, 100, c_str, false);
    std::cout << "c_str: \"" << c_str << "\"" << '\n';
}

// Чтение клавиатуры.
// Деление на ноль.
void read_keypad_3() {
    char a_str[] = "1";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "0";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float / b_float;
    std::cout << "a / b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    ftoa_float_mod(c_float, 100, c_str, false);
    std::cout << "c_str: \"" << c_str << "\"" << '\n';
}

// Чтение клавиатуры.
void read_keypad_4() {
    char a_str[] = "999999999999999";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "9999999999999999";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a / b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    ftoa_float_mod(c_float, 100, c_str, false);
    std::cout << "c_str: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_1() {
    char a_str[] = "2";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "3";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float + b_float;
    std::cout << "a + b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_2() {
    char a_str[] = "10";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "7";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a * b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_3() {
    char a_str[] = "10";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "-7";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a * b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_4() {
    char a_str[] = "-10";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "7";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a * b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_5() {
    char a_str[] = "-10";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "-7";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a * b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_6() {
    char a_str[] = "0.0000000000001";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "0.00000000000001";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float + b_float;
    std::cout << "a + b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_7() {
    char a_str[] = "999999999999999";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "9999999999999999";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float + b_float;
    std::cout << "a + b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_8() {
    char a_str[] = "0.0000000000001";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "9999999999999999";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float / b_float;
    std::cout << "a / b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_9() {
    char a_str[] = "999999999999999";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "9999999999999999";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a * b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_10() {
    char a_str[] = "9";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "1";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float + b_float;
    std::cout << "a + b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_11() {
    char a_str[] = "10";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "1";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float - b_float;
    std::cout << "a - b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_12() {
    char a_str[] = "3";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "2";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a * b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_13() {
    char a_str[] = "1";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "2";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float / b_float;
    std::cout << "a / b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_14() {
    char a_str[] = "5";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "0";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float + b_float;
    std::cout << "a + b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_15() {
    char a_str[] = "0";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "5";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float + b_float;
    std::cout << "a + b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_16() {
    char a_str[] = "5";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "0";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float - b_float;
    std::cout << "a - b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_17() {
    char a_str[] = "0";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "5";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float - b_float;
    std::cout << "a - b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_18() {
    char a_str[] = "5";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "0";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a * b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_19() {
    char a_str[] = "0";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "5";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float * b_float;
    std::cout << "a * b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_20() {
    char a_str[] = "5";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "0";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float / b_float;
    std::cout << "a / b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    if (!std::isinf(c_float)) {
        char c_str[200];
        memset(c_str, '\0', sizeof c_str);
        ftoae_v2(c_float, c_str, true);
        std::cout << "result: \"" << c_str << "\"" << '\n';
    }
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_21() {
    char a_str[] = "0";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "5";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float / b_float;
    std::cout << "a / b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_22() {
    char a_str[] = "-0";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "5";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float + b_float;
    std::cout << "a + b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Полная проверка арифметических выражений.
void calculator_workflow_test_23() {
    char a_str[] = "0";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "0";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float / b_float;
    std::cout << "a / b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    if (!std::isnan(c_float)) {
        char c_str[200];
        memset(c_str, '\0', sizeof c_str);
        ftoae_v2(c_float, c_str, true);
        std::cout << "result: \"" << c_str << "\"" << '\n';
    }
}

// Полная проверка арифметических выражений.
// Случайный тест.
void calculator_workflow_test_24() {
    char a_str[] = "301.9533944630";
    std::cout << "a_str: \"" << a_str << "\"" << '\n';
    float a_float = atof_kr_float(a_str, false);
    std::cout << "a_float: " << std::fixed << std::setprecision(152) << a_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&a_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(a_float) << std::endl;

    std::cout << '\n';

    char b_str[] = "23204.0642586600";
    std::cout << "b_str: \"" << b_str << "\"" << '\n';
    float b_float = atof_kr_float(b_str, false);
    std::cout << "b_float: " << std::fixed << std::setprecision(152) << b_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&b_float);
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(b_float) << std::endl;

    std::cout << '\n';

    float c_float = a_float / b_float;
    std::cout << "a / b: " << std::fixed << std::setprecision(152) << c_float << "\n";
    std::cout << "hex: "; print_float_as_hex(&c_float);
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << c_float << "\n";
    std::cout << "subnormal: " << std::boolalpha << !std::isnormal(c_float) << std::endl;

    std::cout << '\n';

    char c_str[200];
    memset(c_str, '\0', sizeof c_str);
    ftoae_v2(c_float, c_str, true);
    std::cout << "result: \"" << c_str << "\"" << '\n';
}

// Эталонная реализация ftoae - конвертация float в строку в экспоненциальной форме.
void ftoae(float num, char* str, bool debug = false) {
    int exp = 0;

    // Целая часть не равна нулю.
    // Значение num либо нормализовано, либо денормализовано влево.
    if ((int)num != 0) {
        // Понижаем порядок, чтобы избежать переполнения order.
        float num_abs_downscaled = abs(num) / 10.0f;
        float order = 1.0f;

        if (debug) {
            std::cout << "num_abs_downscaled: " << std::fixed << std::setprecision(150) << num_abs_downscaled << '\n';
        }

        // Если order стал больше, чем num_abs_downscaled,
        // который в десять раз меньше истинного num_abs,
        // то его порядок равен порядку истинного num.
        while (order <= num_abs_downscaled) {
            order *= 10.0f;
            exp++;

            if (debug) {
                std::cout << std::dec << "exp: " << exp;
                std::cout << ", order: " << std::fixed << std::setprecision(150) << order << "\n";
            }
        }

        if (debug) {
            std::cout << "order: " << std::fixed << std::setprecision(150) << order << '\n';
            std::cout << "hex: ";
            print_float_as_hex(&order);
        }

        // Нормализуем num.
        num /= order;

        if (debug) {
            std::cout << "normalized: " << std::fixed << std::setprecision(150) << num << '\n';
            std::cout << "hex: ";
            print_float_as_hex(&num);
        }

        char normalized_str[255];
        ftoa_float_mod(num, 150, normalized_str, false);

        if (debug) {
            std::cout << "normalized_str: " << normalized_str << '\n';
        }
    }
    // Целая часть равна нулю.
    // Значение num денормализовано вправо.
    else {
        do {
            num *= 10.0f; // Нормализуем num_abs
            exp++;
        } while ((int)num == 0);

        exp = -exp;

        if (debug) {
            std::cout << "normalized: " << std::fixed << std::setprecision(150) << num << '\n';
            std::cout << "hex: ";
            print_float_as_hex(&num);
        }

        char normalized_str[255];
        ftoa_float_mod(num, 150, normalized_str, false);

        if (debug) {
            std::cout << "normalized_str: " << normalized_str << '\n';
        }
    }

    // Максимальное количество знаков на LCD.
    int precision = 0;
    const int LCD_MAX = 16;
    // Экспоненциальная форма не требуется.
    if (exp == 0) {
        // Резервируем два знака под целую часть и точку,
        // и ещё один - под символ '-' в случае отрицательного num.
        precision = num < 0 ? LCD_MAX - 2 - 1 : LCD_MAX - 2;

        ftoa_float_mod(num, precision, str, false);
    }
    else {
        // Резервируем дополнительно 4 знака под экспоненциальную запись: "E+99".
        precision = num < 0 ? LCD_MAX - 2 - 4 - 1 : LCD_MAX - 2 - 4;

        ftoa_float_mod(num, precision, str, false);

        // Смещаем указатель в позицию, где зарезервировано 4 символа под экспоненту.
        str += LCD_MAX - 4;

        // Преобразуем экспоненту в строку.
        *str++ = 'E';
        *str++ = exp < 0 ? '-' : '+';

        // Модуль экспоненты в этой ветке лежит в [1,38].
        exp = abs(exp);
        int q = exp / 10;
        int r = exp % 10;
        *str++ = '0' + q;
        *str++ = '0' + r;
    }
}

// Эталонная реализация ftoae - конвертация float в строку в экспоненциальной форме.
// 
// NOTE: исправлена нормализация вправо - вместо деления на итеративно вычисляемую степень десяти
// выполняется итеративное деление на 10 по аналогии с нормализацией влево.
// Реализация в первой версии из-за округления не во всех случаях давала нормализованное значение.
//
// Проблема в том, что в некоторых случаях после понижения порядка делением на 10, из-за округления в большую сторону,
// порядок числа num в действительности оставался прежним, уменьшалось только его значение. В результате order имел порядок больше истинного
// и при делении num'/order происходила денормализация вправо.
// Другая проблема связана с тем, что после нормализации num'/order значение оказывалось слишком близки к 10 и округлялось до 10,
// давая денормализацию влево.
// 
// Описанная проблема возникает и в оригинальной реализации из z88dk, но на других значениях, поскольку там нет предварительного понижения порядка.
//
// Примеры проблемных степеней десяти можно увидеть в функции ftoae_pows_of_tens.
//
// Обоснование: основной вопрос в том, существует ли денормализованное влево число такое, что после деления на 10 даёт денормализацию вправо и т.о.
// мы снова получим двузначное денормализованное влево значение. Если такое число существует, то оно должно быть максимально близко к единице,
// чтобы после деления дать округление в меньшую сторону и стать меньше единицы. Наименьшее денормализованное - это 10, после деления на десять оно
// даёт единицу. Если теперь брать все значения отдаляющиеся от 10 в плюс бесконечность, то результат деления на 10 также будет увеличиваться
// отдаляясь от единицы (и т.о. - от наибольшего денормализованного вправо меньше единицы) в большую сторону,
// при этом округление по-умолчание выполняется к тому значению, которое ближе к истинному.
//
// Что касается нормализации влево, то мы уже показывали, что при умножении наибольшего денормализованного меньше единицы на 10, мы получаем нормализованное число.
void ftoae_v2(float num, char* str, bool debug = false) {
    int exp = 0;

    // Целая часть не равна нулю.
    // Значение num либо нормализовано, либо денормализовано влево.
    if ((int)num != 0) {
        // Хранит значение num на момент перед очередным делением на 10.
        // В конце содержит нормализованное значение num.
        // Возможно, что num уже содержит нормализованное значение.
        float num_norm = num;

        while (true) {
            num = num / 10.0f;

            // Если num стал меньше единицы после деления на 10,
            // значит предыдущее значение было нормализованным.
            // 
            // NOTE: на уровне ассемблерной реализации в МК нет необходимости вычислять модуль,
            // поскольку мы выясняем отношение |num|<1 не арифметически, а распаковывая экспоненту
            // двоичного представления num в формате float и смотрим, стала ли она меньше нуля (или меньше 127 в коде со смещением).
            // То есть, мы используем однозначный косвенный признак, поскольку все значения float меньше 1 после нормализации двоичной мантиссы
            // будут иметь экспоненту равную как минимум (0+127)-1=126 в коде со смещением или 126-127=-1.
            if (abs(num) < 1)
                break;

            exp++;
            num_norm = num;
        }

        num = num_norm;

        if (debug) {
            std::cout << "normalized: " << std::fixed << std::setprecision(150) << num << '\n';
            std::cout << "hex: ";
            print_float_as_hex(&num);
        }

        char normalized_str[255];
        ftoan(num, 150, normalized_str, false);

        if (debug) {
            std::cout << "normalized_str: " << normalized_str << '\n';
        }
    }
    // Целая часть равна нулю.
    // Значение num денормализовано вправо.
    else {
        while (num != 0 && (int)num == 0) {
            num *= 10.0f; // Нормализуем num_abs
            exp++;
        }

        exp = -exp;

        if (debug) {
            std::cout << "normalized: " << std::fixed << std::setprecision(150) << num << '\n';
            std::cout << "hex: ";
            print_float_as_hex(&num);
        }

        char normalized_str[255];
        ftoan(num, 150, normalized_str, false);

        if (debug) {
            std::cout << "normalized_str: " << normalized_str << '\n';
        }
    }

    // Максимальное количество знаков на LCD.
    int precision = 0;
    const int LCD_LEN = 16;
    // Экспоненциальная форма не требуется.
    if (exp == 0) {
        // Резервируем два знака под целую часть и точку,
        // и ещё один - под символ '-' в случае отрицательного num.
        precision = num < 0 ? LCD_LEN - 2 - 1 : LCD_LEN - 2;

        ftoan(num, precision, str, false);
    }
    else {
        // Резервируем дополнительно 4 знака под экспоненциальную запись: "E+99".
        precision = num < 0 ? LCD_LEN - 2 - 4 - 1 : LCD_LEN - 2 - 4;

        ftoan(num, precision, str, false);

        // Смещаем указатель в позицию, где зарезервировано 4 символа под экспоненту.
        str += LCD_LEN - 4;

        // Преобразуем экспоненту в строку.
        *str++ = 'E';
        *str++ = exp < 0 ? '-' : '+';

        // Модуль экспоненты в этой ветке лежит в [1,38].
        exp = abs(exp);
        int q = exp / 10;
        int r = exp % 10;
        *str++ = '0' + q;
        *str++ = '0' + r;
    }
}

// Проверка ftoae.
// Пример 1. Наибольшее денормализованное больше 9.
// NOTE: здесь и далее имеется ввиду десятичная нормализация/денормализация.
void ftoae_case_1() {
    float a = (powf(2, 24) - 1) * powf(2, -23) * powf(2, 127);
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 2. Наименьшее денормализованное больше 9.
void ftoae_case_2() {
    float a = -10.0f;
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 3. Наибольшее нормализованное.
void ftoae_case_3() {
    float a = 10.0f - powf(2, -23) * powf(2, 3);
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 4. Наименьшее нормализованное.
void ftoae_case_4() {
    float a = -1.0f;
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 5. Наибольшее денормализованное меньше 1.
void ftoae_case_5() {
    float a = 1.0f - powf(2, -24);
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 6. Наименьшее денормализованное меньше 1.
void ftoae_case_6() {
    float a = -powf(2, -126);
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 7. Степень десяти, которая в старой версии была проблемной и давала некорректную нормализацию - 10 в целой части.
void ftoae_case_7() {
    float a = powf(10, 37);
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 8. Степень десяти, которая в старой версии была проблемной и давала некорректную нормализацию - 0 в целой части.
void ftoae_case_8() {
    float a = powf(10, 33);
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 9. Случайный пример числа денормализованного влево.
void ftoae_case_9() {
    float a = 25307.576171875f;
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 10. Случайный пример числа денормализованного вправо.
void ftoae_case_10() {
    float a = 1.3023970127105712890625f * powf(2, -34);
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Проверка ftoae.
// Пример 11. Нулевое число.
void ftoae_case_11() {
    float a = 0.0f;
    std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
    std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
    std::cout << "hex: ";
    print_float_as_hex(&a);

    std::cout << '\n';

    char a_str_sci[255];
    memset(a_str_sci, '\0', sizeof a_str_sci);
    ftoae_v2(a, a_str_sci, true);
    std::cout << "ftoae(): " << a_str_sci;

    std::cout << '\n';
}

// Взятие в качестве num положительных степеней десяти для проверки нормализации вправо.
void ftoae_pows_of_tens() {
    for (int i = 0; i <= 38; i++) {
        float a = powf(10, i);

        std::cout << "exp: " << i << "\n";
        std::cout << "fixed: " << std::fixed << std::setprecision(150) << a << "\n";
        std::cout << "scientific: " << std::scientific << std::setprecision(150) << a << "\n";
        //print_float_as_hex(&a);

        char a_str_sci[255];
        memset(a_str_sci, '\0', sizeof a_str_sci);
        ftoae_v2(a, a_str_sci);
        //ftoae(a, a_str_sci);
        std::cout << "ftoae_v2(): " << a_str_sci << '\n';

        std::cout << '\n';
    }
}

// Проверка ftoan.
// Пример 1.
void ftoan_case_1() {
    float a = 0.0f;
    std::cout << std::fixed << std::setprecision(150) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoan(a, 5, str);
    std::cout << str << '\n';
}

// Проверка ftoan.
// Пример 2.
void ftoan_case_2() {
    float a = 1.0f;
    std::cout << std::fixed << std::setprecision(150) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoan(a, 5, str);
    std::cout << str << '\n';
}

// Проверка ftoan.
// Пример 3.
void ftoan_case_3() {
    float a = 10.0f - powf(2, -23) * powf(2, 3);
    std::cout << std::fixed << std::setprecision(150) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoan(a, 20, str);
    std::cout << str << '\n';
}

// Проверка ftoan.
// Пример 4.
void ftoan_case_4() {
    float a = -4.5832233428955078125f;
    std::cout << std::fixed << std::setprecision(150) << a << "\n";
    print_float_as_hex(&a);

    std::cout << '\n';

    char str[255];
    ftoan(a, 23, str);
    std::cout << str << '\n';
}

int main() {
    //hex_to_float();
    //loop_through_normalized_float();
    //zero_diff();

    //div_case_1();
    //div_case_2();
    //div_case_3();
    //div_case_4();
    //div_case_5();
    //div_case_6();
    //div_case_7();
    //div_case_8();
    //div_case_9();
    //div_case_10();
    //div_case_11();
    //div_case_12();
    //div_case_13();
    //div_case_14();
    //div_case_15_return_to_normal();

    //mul_case_1();
    //mul_case_2();
    //mul_case_3();
    //mul_case_4();
    //mul_case_5();
    //mul_case_6();
    //mul_case_7();
    //mul_case_8();
    //mul_case_9();
    //mul_case_10();
    //mul_case_11();
    //mul_case_12();
    //mul_case_13();
    //mul_case_14();
    //mul_case_15();
    //mul_case_16();
    //mul_case_17();
    //mul_case_18();
    //mul_case_19_return_to_normal();
    //mul_case_20_bugfix();

    // Алгебраическое сложение: одинаковые знаки.
    // 
    // Note:
    // Номер примера соответствует номеру уникальной ветки в майндмапе.
    // Но для большинства веток нет отдельных примеров, поэтому нумерация здесь идет не по порядку, потому что некоторых примеров просто нет.
    // Причина этого в том, что большинство веток в майндмапе в сущности вызывает один и тот же код, который уже покрыт примерами.
    // Например, в любой ветке выполняется округление, поэтому имея необходимое количество примеров уже покрывающих все варианты округления
    // нет смысла для новой уникальной ветки реализовывать все варианты округления, для такой ветки достаточно одного примера с произвольно выбранным вариантом округления.

    //add_case_1();
    //add_case_2();
    //add_case_3();
    //add_case_4();
    //add_case_5();
    //add_case_6();
    //add_case_7();
    //add_case_8();
    //add_case_9();
    //add_case_10();
    //add_case_11();
    //add_case_12();
    //add_case_13();
    //add_case_14();
    //add_case_15();
    //add_case_16();
    //add_case_26();
    //add_case_36();
    //add_case_40();
    //add_case_41();
    //add_case_42();

    // Алгебраическое сложение: разные знаки.
    //add_case_neg_0();
    //add_case_neg_1();
    //add_case_neg_2();
    //add_case_neg_4();
    //add_case_neg_5();
    //add_case_neg_6();
    //add_case_neg_8();
    //add_case_neg_10();
    //add_case_neg_12();
    //add_case_neg_20();
    //add_case_neg_33();
    //add_case_neg_34();
    //add_case_neg_36();

    //fsub_case_1();
    //fsub_case_2();

    //fadd_swap();

    //fadd_zero_zero();
    //fadd_zero_nonzero();
    //fadd_nonzero_zero();

    // Тесты для ftoa_float_mod.
    // NOTE: эта версия больше не актуальна.
    //ftoa_float_mod_case_1();
    //ftoa_float_mod_case_2();
    //ftoa_float_mod_case_3();
    //ftoa_float_mod_case_4();
    //ftoa_float_mod_case_5();
    //ftoa_float_mod_case_6();
    //ftoa_float_mod_case_7();
    //ftoa_float_mod_case_8();
    //denormals_ftoa();

    // Тесты для atof.    
    //atof_case_0();
    //atof_case_1();
    //atof_case_2();
    //atof_case_3();
    //atof_case_4();
    //atof_case_5();
    //atof_case_6();
    //atof_case_7();
    //atof_case_8();
    //atof_case_9();
    //atof_case_10();
    //atof_case_11();
    //atof_case_12();
    //atof_case_13();
    //atof_case_14();
    //atof_case_15();
    //atof_case_16();
    //atof_case_17();
    //atof_case_18();
    //atof_case_19();

    //atof_sandbox();

    // Тесты для проверки чтения клавиатуры.
    //read_keypad_1();
    //read_keypad_2();
    //read_keypad_3();
    //read_keypad_4();

    //calculator_workflow_test_1();
    //calculator_workflow_test_2();
    //calculator_workflow_test_3();
    //calculator_workflow_test_4();
    //calculator_workflow_test_5();
    //calculator_workflow_test_6();
    //calculator_workflow_test_7();
    //calculator_workflow_test_8();
    //calculator_workflow_test_9();
    //calculator_workflow_test_10();
    //calculator_workflow_test_11();
    //calculator_workflow_test_12();
    //calculator_workflow_test_13();
    //calculator_workflow_test_14();
    //calculator_workflow_test_15();
    //calculator_workflow_test_16();
    //calculator_workflow_test_17();
    //calculator_workflow_test_18();
    //calculator_workflow_test_19();
    //calculator_workflow_test_20();
    //calculator_workflow_test_21();
    //calculator_workflow_test_22();
    //calculator_workflow_test_23();
    //calculator_workflow_test_24();

    // Тесты для ftoae.
    ftoae_case_1();
    //ftoae_case_2();
    //ftoae_case_3();
    //ftoae_case_4();
    //ftoae_case_5();
    //ftoae_case_6();
    //ftoae_case_7();
    //ftoae_case_8();
    //ftoae_case_9();
    //ftoae_case_10();
    //ftoae_case_11();

    //ftoae_pows_of_tens();

    // Тесты для ftoan.
    //ftoan_case_1();
    //ftoan_case_2();
    //ftoan_case_3();
    //ftoan_case_4();

    return 0;
}