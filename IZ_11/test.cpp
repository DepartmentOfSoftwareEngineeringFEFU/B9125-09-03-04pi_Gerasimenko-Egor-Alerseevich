#include <iostream>
#include "geometry.h"

int main(void)
{
    double cuboid = geometry::Cuboid(20, 10, -20);
    std::cout << "Площадь прямоугольного параллелепипеда(невалидные данные): " << cuboid << std::endl;

    double cube = geometry::Cube(-20);
    std::cout << "Площадь куба(невалидные данные (отрицательная сторона)): " << cube << std::endl;

    cube = geometry::Cube('y');
    std::cout << "Площадь прямоугольного параллелепипеда(невалидные данные (не число)): " << cube << std::endl;

    double prsim = geometry::Prism(20, 10, -20);
    std::cout << "Площадь призмы(невалидные данные (отрицательная сторона пирамиды)): " << prsim << std::endl;

    prsim = geometry::Prism(20, -10, 20.1);
    std::cout << "Площадь призмы(невалидные данные (отрицательная образующая)): " << prsim << std::endl;

    prsim = geometry::Prism(-20, 10, 20);
    std::cout << "Площадь призмы(невалидные данные(число сторон)): " << prsim << std::endl;

    double pyramid = geometry::Pyramid(20, 10, -20);
    std::cout << "Площадь Пирамиды(невалидные данные (отрицатльное число)): " << pyramid << std::endl;

    double cylinder = geometry::Cylinder(20, 0);
    std::cout << "Площадь цилиндра(невалидные данные (ноль)): " << cylinder << std::endl;

    double cone = geometry::Cone(1.3, -10);
    std::cout << "Площадь конус(оневалидные данные (отрицательное число)): " << cone << std::endl;

    double TrunCone = geometry::TruncatedCone(20, 10, -20);
    std::cout << "Площадь усеченная пирамида(невалидные данные (отрицательное число)): " << TrunCone << std::endl;

    double Valid_Cuboid_1 = geometry::Cuboid(20, 10, 10);
    std::cout << "Площадь прямоугольного параллелепипеда(валидные данные (целые числа)): " << Valid_Cuboid_1 << std::endl;

    double Valid_Cuboid_2 = geometry::Cuboid(20.1, 0.5, 2);
    std::cout << "Площадь прямоугольного параллелепипеда(валидные данные (вещественные числа)): " << Valid_Cuboid_2 << std::endl;

    return 0;
}

/* Модулем пользоваться удобно, но в help отсутствуют коды ошибок,
при некорректных данных выводится один и тот же код ошибки,
При вводе символа программа считает его как за число -> некорректная обработка ошибок,
Программа считает валидные данные верно*/