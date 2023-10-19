#include "basicfuncs.h"

//double sqr(double t);

class logs {
private:
    double x1, y1, x2, y2, R;
public:
    logs(double x1_ = 0, double y1_ = 0, double x2_ = 0, double y2_ = 0, double Rad = 0);
    double z_log(double x, double y);
};