#include "basicfuncs.h"
#include "roverclass.h"
class processor {
private:
	double start_x;
	double finish_x;
	double start_y;
	double finish_y;
	rover rover0;
public:
	processor(double start_x_ = 3, double finish_x_ = 9, double start_y_ = 3, double finish_y_ = 9);
	int building_road(vector <Point> overwritingPixels, int cols);
	int distant(double x, double y);
	int maindir(double x, double y);
};