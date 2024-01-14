#include "pointclass.h"

Point::Point(double x1, double y1, double z1) {
	x = x1;
	y = y1;
	z = z1;
}

double Point::give_x() {
	return x;
}

double Point::give_y() {
	return y;
}

double Point::give_z() {
	return z;
}