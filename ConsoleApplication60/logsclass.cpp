#include "logsclass.h"

logs::logs(double x1_, double y1_, double x2_, double y2_, double Rad) {
    x1 = x1_; x2 = x2_; y1 = y1_; y2 = y2_; R = Rad;
}

double FirstCordofOrtVtr(double a, double b, double R) {
    return (R * b) / sqrt(sqr(a) + sqr(b));
}

double SecondCordofOrtVtr(double a, double b, double firstCord) {
    return -(a * firstCord / b);
}

int sgn(double x) {
    if (x > 0) return 1;
    else if (fabs(x) < eps) return 0;
    else return -1;
}

double logs::z_log(double x, double y) {
    double a, b, c, d, value1, value2, value3, value4;
    int sgnvalue1, sgnvalue2, sgnvalue3, sgnvalue4;
    double u, v;

    a = x2 - x1;
    b = y2 - y1;
    c = FirstCordofOrtVtr(a, b, R);
    d = SecondCordofOrtVtr(a, b, c);
    value1 = b * x - a * y - b * (x1 + c) + a * (y1 + d);
    value2 = b * x - a * y - b * (x1 - c) + a * (y1 - d);
    value3 = d * x - c * y + c * y1 - d * x1;
    value4 = d * x - c * y + c * y2 - d * x2;
    sgnvalue1 = sgn(value1);
    sgnvalue2 = sgn(value2);
    sgnvalue3 = sgn(value3);
    sgnvalue4 = sgn(value4);
    if (abs(sgnvalue1 + sgnvalue2) > 1 || abs(sgnvalue3 + sgnvalue4) > 1) return 0;
    else {
        u = fabs(b * x - a * y - b * (x1 + c) + a * (y1 + d)) / sqrt(sqr(a) + sqr(b));
        v = fabs(b * x - a * y - b * (x1 - c) + a * (y1 - d)) / sqrt(sqr(a) + sqr(b));
        return sqrt(u * v);
    }
}