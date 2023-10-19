#include "stoneclass.h"

stone::stone(double x, double y, double r) {
    x_0 = x; y_0 = y; R = r;
}

double stone::z_stone(double x, double y) {
    if ((sqr(x - x_0) + sqr(y - y_0)) < sqr(R)) {
        z = sqrt(sqr(R) - sqr(x - x_0) - sqr(y - y_0));
        return z;
    }
    else return 0;
}