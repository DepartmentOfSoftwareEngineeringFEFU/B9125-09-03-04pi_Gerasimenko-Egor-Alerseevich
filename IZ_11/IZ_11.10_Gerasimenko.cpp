#include "geometry.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void reportValidationError(const string& figure, const string& param, double value, const string& rule) {
    cerr << "               ОШИБКА ВАЛИДАЦИИ ПАРАМЕТРОВ       \n";
    cerr << "Фигура:     " << left << setw(25) << figure << "\n";
    cerr << "Параметр:    " << left << setw(25) << param << "\n";
    cerr << "Значение:    " << left << setw(25) << value << "\n";
    cerr << "Требование:   " << left << setw(25) << rule << "\n";
    cerr << "Код возврата: " << left << setw(25) << "-2" << "\n";

}

void test1() {

    // ──────────────────────────────────────────────
    // ТЕСТ 1: Куб (валидные данные)
    // ──────────────────────────────────────────────
    cout << "[Тест 1] Cube, сторона = 6.0" << endl;
    double cube_a = 6.0;
    if (cube_a <= 0) {
        reportValidationError("Cube", "a", cube_a, "a > 0");
        return;
    }
    cout << "Результат: " << geometry::Cube(cube_a) << "\n" << endl;
}

void test2() {
    // ──────────────────────────────────────────────
    // ТЕСТ 2: Параллелепипед (невалидные данные: b < 0)
    // ──────────────────────────────────────────────
    cout << "[Тест 2] Cuboid, стороны = 2.0, -3.0, 4.0" << endl;
    double cb_a = 2.0, cb_b = -3.0, cb_c = 4.0;

    if (cb_a <= 0) { reportValidationError("Cuboid", "a", cb_a, "a > 0"); return; }
    if (cb_b <= 0) { reportValidationError("Cuboid", "b", cb_b, "b > 0"); return; }
    if (cb_c <= 0) { reportValidationError("Cuboid", "c", cb_c, "c > 0"); return; }

    cout << "Результат: " << geometry::Cuboid(cb_a, cb_b, cb_c) << "\n" << endl;
}

void test3() {
    // ──────────────────────────────────────────────
    // ТЕСТ 3: Призма (невалидные данные: n < 3)
    // ──────────────────────────────────────────────
    cout << "[Тест 3] Prism, n=2, a=5.0, h=10.0" << endl;
    int prism_n = 2;
    double prism_a = 5.0, prism_h = 10.0;

    if (prism_n < 3) {
        reportValidationError("Prism", "n", prism_n, "n >= 3 (правильный многоугольник)");
        return;
    }
    if (prism_a <= 0) { reportValidationError("Prism", "a", prism_a, "a > 0"); return; }
    if (prism_h <= 0) { reportValidationError("Prism", "h", prism_h, "h > 0"); return; }

    cout << "Результат: " << geometry::Prism(prism_n, prism_a, prism_h) << "\n" << endl;
}

void test4() {
    // ──────────────────────────────────────────────
    // ТЕСТ 4: Цилиндр (валидные данные)
    // ──────────────────────────────────────────────
    cout << "[Тест 4] Cylinder, r=3.0, h=7.0" << endl;
    double cyl_r = 3.0, cyl_h = 7.0;

    if (cyl_r <= 0) { reportValidationError("Cylinder", "r", cyl_r, "r > 0"); return; }
    if (cyl_h <= 0) { reportValidationError("Cylinder", "h", cyl_h, "h > 0"); return; }

    cout << "Результат: " << geometry::Cylinder(cyl_r, cyl_h) << "\n" << endl;
}

void test5() {
    // ─────────────────────────────────────────────
    // ТЕСТ 5: Конус (невалидные данные: l = 0)
    // ──────────────────────────────────────────────
    cout << "[Тест 5] Cone, r=4.0, l=0.0" << endl;
    double cone_r = 4.0, cone_l = 0.0;

    if (cone_r <= 0) { reportValidationError("Cone", "r", cone_r, "r > 0"); return; }
    if (cone_l <= 0) { reportValidationError("Cone", "l", cone_l, "l > 0 (образующая)"); return; }

    cout << "Результат: " << geometry::Cone(cone_r, cone_l) << "\n" << endl;
}
int main() {

    setlocale(LC_ALL, "Russian");
    cout << fixed << setprecision(2);
    cout << "=== Геометрический калькулятор ===\n" << endl;
    cout;
    test1();
    cout;
    test2();
    cout;
    test3();
    cout;
    test4();
    cout;
    test5();
    cout << "=== Все проверки пройдены успешно ===" << endl;
}