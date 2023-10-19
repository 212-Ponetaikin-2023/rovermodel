#include "basicfuncs.h"

//double sqr(double t);

double povorot(double x, double x_0, double y, double y_0, double angle, bool flag);

class Gaussyan {
private:
    double x_0, y_0, z;
    double sigma_x, sigma_y, height, angle;
public:
    Gaussyan(double x = 0, double y = 0, double sgm_x = 1, double sgm_y = 1, double A = 0, double angle_ = 0);
    double z_gauss(double x, double y);
};