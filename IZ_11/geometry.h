#pragma once
#include <cmath>

namespace geometry {
    constexpr double PI = 3.14159265358979323846;

    // Прямоугольный параллелепипед
    double Cuboid(double a, double b, double c);

    // Куб
    double Cube(double a);

    // Призма с правильным многоугольником в основании
    double Prism(int n, double a, double h);

    // Пирамида с правильным многоугольником в основании
    double Pyramid(int n, double a, double l);

    // Цилиндр
    double Cylinder(double r, double h);

    // Конус
    double Cone(double r, double l);

    // Усечённый конус
    double TruncatedCone(double r1, double r2, double l);
}