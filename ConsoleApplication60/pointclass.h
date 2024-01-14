#include "basicfuncs.h"

class Point {
private:
	double x, y, z;
public:
	Point(double x1, double y1, double z1);
	double give_x();
	double give_y();
	double give_z();
};