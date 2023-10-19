#include "basicfuncs.h"

class stone {
private:
    double x_0, y_0, z;
    double R;
public:
    stone(double x = 0, double y = 0, double r = 0);
    double z_stone(double x, double y);
};