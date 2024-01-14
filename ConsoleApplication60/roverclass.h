#include "basicfuncs.h"
#include "pointclass.h"

#define PI 3.1415926535



class rover {
private:
	double a[5];
	double b[7];
	double c[9];
	double critical_angle_alpha;
	double old_coverage[9];
	double coverage[9];
	unsigned int length = 3;
	unsigned int width = 3;
	double clearance = 1;
	vector <Point> pixel;
public:
	rover(double critical_angle_alpha_ = 1.05);
	void create_rover(double x, double y, vector <Point> overwritingPixels, int cols);
	int next_tact(vector <Point> overwritingPixels, double x, double y, int cols);
	int recalculate_angles(double* coverage);
	int checkclearance();
	int teleportation(int last_str_line, vector <Point> overwritingPixels, int cols);
	int stop();
	int screening(int direction, double x, double y, vector <Point> overwritingPixels, int cols);
	void give_last_cords(double* x, double* y);
	void printLastCords(ofstream& logControl);
	void printcords();
	void clear();
};

