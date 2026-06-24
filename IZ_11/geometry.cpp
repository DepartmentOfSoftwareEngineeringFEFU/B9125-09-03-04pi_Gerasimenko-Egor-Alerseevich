#include "geometry.h"
#include <cmath>
#include <iostream>
using namespace std;
namespace geometry {

    double Cuboid(double a, double b, double c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return -1;
        };
        return 2 * (a * b + b * c + a * c);
    }

    double Cube(double a) {
        if (a <= 0) {
            return -1;
        }
        return 6 * a * a;
    }

    double Prism(int n, double a, double h) {
        if (n < 3 || a <= 0 || h <= 0) {
            return -1;
        };
        return 2 * ((n * a * a) / (4 * tan(PI / n))) + n * a * h;
    }

    double Pyramid(int n, double a, double l) {
        if (n < 3 || a <= 0 || l <= 0) {
            return -1;
        };
        return (n * a * a) / (4 * tan(PI / n)) + 0.5 * n * a * l;
    }

    double Cylinder(double r, double h) {
        if (r <= 0 || h <= 0) {
            return -1;
        };
        return 2 * PI * r * (r + h);
    }

    double Cone(double r, double l) {
        if (r <= 0 || l <= 0) { 
            return -1; 
        };
        return PI * r * (r + l);
    }

    double TruncatedCone(double r1, double r2, double l) {
        if (r1 <= 0 || r2 <= 0 || l <= 0)
        {
            return -1;
        };
        return PI * (r1 + r2) * l + PI * r1 * r1 + PI * r2 * r2;
    }

}