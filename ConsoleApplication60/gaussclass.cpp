#include "gaussclass.h"

double sqr(double t) {
    return t * t;
}

double povorot(double x, double x_0, double y, double y_0, double angle, bool flag) {
    if (flag == true) return sqr((x - x_0) * cos(angle) - (y - y_0) * sin(angle));
    else return sqr((x - x_0) * sin(angle) + (y - y_0) * cos(angle));
}

Gaussyan::Gaussyan(double x, double y, double sgm_x, double sgm_y, double A, double angle_) {
    x_0 = x; y_0 = y; sigma_x = sgm_x; sigma_y = sgm_y; height = A; angle = angle_;
}

double Gaussyan::z_gauss(double x, double y) {
    z = height * exp(-((povorot(x, x_0, y, y_0, angle, true) / (2 * sqr(sigma_x))) + (povorot(x, x_0, y, y_0, angle, false) / (2 * sqr(sigma_y)))));
    return z;
}