#include "roverclass.h"

rover::rover(double critical_angle_alpha_) {
	critical_angle_alpha = critical_angle_alpha_;
}

void rover::create_rover(double x, double y, vector <Point> overwritingPixels, int cols) {
	int x_ = x / step;
	int y_ = y / step;
	double z = overwritingPixels[x_ * cols + y_].give_z();
	pixel.push_back(Point(x, y, z));
	old_coverage[0] = z;
	old_coverage[1] = overwritingPixels[x_ * cols + y_ + 1].give_z();
	old_coverage[2] = overwritingPixels[(x_ + 1) * cols + y_ + 1].give_z();
	old_coverage[3] = overwritingPixels[(x_ + 1) * cols + y_].give_z();
	old_coverage[4] = overwritingPixels[(x_ + 1) * cols + y_ - 1].give_z();
	old_coverage[5] = overwritingPixels[x_ * cols + y_ - 1].give_z();
	old_coverage[6] = overwritingPixels[(x_ - 1) * cols + y_ - 1].give_z();
	old_coverage[7] = overwritingPixels[(x_ - 1) * cols + y_].give_z();
	old_coverage[8] = overwritingPixels[(x_ - 1) * cols + y_ + 1].give_z();
}

int rover::next_tact(vector <Point> overwritingPixels, double x, double y, int cols) {
	int x_ = x / step;
	int y_ = y / step;
	double z = overwritingPixels[x_ * cols + y_].give_z();
	int check_angles = 0;
	int check_clears = 0;
	coverage[0] = z;
	coverage[1] = overwritingPixels[x_ * cols + y_ + 1].give_z();
	coverage[2] = overwritingPixels[(x_ + 1) * cols + y_ + 1].give_z();
	coverage[3] = overwritingPixels[(x_ + 1) * cols + y_].give_z();
	coverage[4] = overwritingPixels[(x_ + 1) * cols + y_ - 1].give_z();
	coverage[5] = overwritingPixels[x_ * cols + y_ - 1].give_z();
	coverage[6] = overwritingPixels[(x_ - 1) * cols + y_ - 1].give_z();
	coverage[7] = overwritingPixels[(x_ - 1) * cols + y_].give_z();
	coverage[8] = overwritingPixels[(x_ - 1) * cols + y_ + 1].give_z();
	check_angles = recalculate_angles(coverage);
	check_clears = checkclearance();
	//cout << check_angles << " " << check_clears << endl;
	if (check_angles == 0 && check_clears == 0) {
		for (int i = 0; i < 9; i++) old_coverage[i] = coverage[i];
		return 0;
	}
	else {
		return -1;
	}
}

int rover::checkclearance() {
	double old_maxima = -100;
	double new_maxima = -100;
	double old_minima = 100;
	double new_minima = 100;
	for (int i = 0; i < 9; i++) {
		if (old_coverage[i] > old_maxima) old_maxima = old_coverage[i];
		if (old_coverage[i] < old_minima) old_minima = old_coverage[i];
	}
	for (int i = 0; i < 9; i++) {
		if (coverage[i] > new_maxima) new_maxima = coverage[i];
		if (coverage[i] < new_minima) new_minima = coverage[i];
	}
	if (new_maxima > old_maxima + clearance) return -1;
	if (new_minima < old_minima - clearance) return -1;
	else return 0;
}

int rover::recalculate_angles(double *coverage) {
	double angle_alpha; // угол по оси Ox
	double z;
	double z1;
	int flag = 0;
	z = coverage[0];
	
	z1 = coverage[1];
	angle_alpha = acos(step / sqrt(sqr(step) + sqr(z1 - z)));
	if (angle_alpha < critical_angle_alpha) flag = 0;
	else flag = 1;
	if (flag == 1) return -1;

	z1 = coverage[2];
	angle_alpha = acos(2 * step / (sqrt(2 * sqr(step) + sqr(z1 - z)) * sqrt(2)));
	if (angle_alpha < critical_angle_alpha) flag = 0;
	else flag = 1;
	if (flag == 1) return -1;

	z1 = coverage[3];
	angle_alpha = acos(step / sqrt(sqr(step) + sqr(z1 - z)));
	if (angle_alpha < critical_angle_alpha) flag = 0;
	else flag = 1;
	if (flag == 1) return -1;
	
	z1 = coverage[4];
	angle_alpha = acos(2 * step / (sqrt(2 * sqr(step) + sqr(z1 - z)) * sqrt(2)));
	if (angle_alpha < critical_angle_alpha) flag = 0;
	else flag = 1;
	if (flag == 1) return -1;

	z1 = coverage[5];
	angle_alpha = acos(step / sqrt(sqr(step) + sqr(z1 - z)));
	if (angle_alpha < critical_angle_alpha) flag = 0;
	else flag = 1;
	if (flag == 1) return -1;

	z1 = coverage[6];
	angle_alpha = acos(2 * step / (sqrt(2 * sqr(step) + sqr(z1 - z)) * sqrt(2)));
	if (angle_alpha < critical_angle_alpha) flag = 0;
	else flag = 1;
	if (flag == 1) return -1;

	z1 = coverage[7];
	angle_alpha = acos(step / sqrt(sqr(step) + sqr(z1 - z)));
	if (angle_alpha < critical_angle_alpha) flag = 0;
	else flag = 1;
	if (flag == 1) return -1;
	
	z1 = coverage[8];
	angle_alpha = acos(2 * step / (sqrt(2 * sqr(step) + sqr(z1 - z)) * sqrt(2)));
	if (angle_alpha < critical_angle_alpha) flag = 0;
	else flag = 1;
	if (flag == 1) return -1;

	return 0;
}

int rover::teleportation(int last_str_line, vector <Point> overwritingPixels, int cols) {
	double x_, y_;
	int x1, y1;
	double new_x, new_y, new_z;
	int result = 0;
	switch (last_str_line) { // переделать проверку выхода за пределы поля (пока что работает на 50*50)
	case 1:
		x_ = pixel.back().give_x();
		y_ = pixel.back().give_y();
		new_y = y_ + step;
		x1 = x_ / step;
		y1 = new_y / step;
		if (x1 > 0 && x1 < 200 && y1 > 0 && y1 < 200) {
			new_z = overwritingPixels[x1 * cols + y1].give_z();
			pixel.push_back(Point(x_, new_y, new_z));
		}
		result = next_tact(overwritingPixels, x_, new_y, cols);
		break;
	case 2:
		x_ = pixel.back().give_x();
		y_ = pixel.back().give_y();
		new_x = x_ + step;
		new_y = y_ + step;
		x1 = new_x / step;
		y1 = new_y / step;
		if (x1 > 0 && x1 < 200 && y1 > 0 && y1 < 200) {
			new_z = overwritingPixels[x1 * cols + y1].give_z();
			pixel.push_back(Point(new_x, new_y, new_z));
		}
		result = next_tact(overwritingPixels, new_x, new_y, cols);
		break;
	case 3:
		x_ = pixel.back().give_x();
		y_ = pixel.back().give_y();
		new_x = x_ + step;
		x1 = new_x / step;
		y1 = y_ / step;
		if (x1 > 0 && x1 < 200 && y1 > 0 && y1 < 200) {
			new_z = overwritingPixels[x1 * cols + y1].give_z();
			pixel.push_back(Point(new_x, y_, new_z));
		}
		result = next_tact(overwritingPixels, new_x, y_, cols);
		break;
	case 4:
		x_ = pixel.back().give_x();
		y_ = pixel.back().give_y();
		new_x = x_ + step;
		new_y = y_ - step;
		x1 = new_x / step;
		y1 = new_y / step;
		if (x1 > 0 && x1 < 200 && y1 > 0 && y1 < 200) {
			new_z = overwritingPixels[x1 * cols + y1].give_z();
			pixel.push_back(Point(new_x, new_y, new_z));
		}
		result = next_tact(overwritingPixels, new_x, new_y, cols);
		break;
	case 5:
		x_ = pixel.back().give_x();
		y_ = pixel.back().give_y();
		new_y = y_ - step;
		x1 = x_ / step;
		y1 = new_y / step;
		if (x1 > 0 && x1 < 200 && y1 > 0 && y1 < 200) {
			new_z = overwritingPixels[x1 * cols + y1].give_z();
			pixel.push_back(Point(x_, new_y, new_z));
		}
		result = next_tact(overwritingPixels, x_, new_y, cols);
		break;
	case 6:
		x_ = pixel.back().give_x();
		y_ = pixel.back().give_y();
		new_x = x_ - step;
		new_y = y_ - step;
		x1 = new_x / step;
		y1 = new_y / step;
		if (x1 > 0 && x1 < 200 && y1 > 0 && y1 < 200) {
			new_z = overwritingPixels[x1 * cols + y1].give_z();
			pixel.push_back(Point(new_x, new_y, new_z));
		}
		result = next_tact(overwritingPixels, new_x, new_y, cols);
		break;
	case 7:
		x_ = pixel.back().give_x();
		y_ = pixel.back().give_y();
		new_x = x_ - step;
		x1 = new_x / step;
		y1 = y_ / step;
		if (x1 > 0 && x1 < 200 && y1 > 0 && y1 < 200) {
			new_z = overwritingPixels[x1 * cols + y1].give_z();
			pixel.push_back(Point(new_x, y_, new_z));
		}
		result = next_tact(overwritingPixels, new_x, y_, cols);
		break;
	case 8:
		x_ = pixel.back().give_x();
		y_ = pixel.back().give_y();
		new_x = x_ - step;
		new_y = y_ + step;
		x1 = new_x / step;
		y1 = new_y / step;
		if (x1 > 0 && x1 < 200 && y1 > 0 && y1 < 200) {
			new_z = overwritingPixels[x1 * cols + y1].give_z();
			pixel.push_back(Point(new_x, new_y, new_z));
		}
		result = next_tact(overwritingPixels, new_x, new_y, cols);
		break;
	}
	//cout << result << endl;
	return result;
}

int rover::stop() {
	int speed = 0;
	return speed;
}

int rover::screening(int direction, double x, double y, vector <Point> overwritingPixels, int cols) {
	double maxima = -100;
	double minima = 100;
	int x_ = x / step;
	int y_ = y / step;
	double new_coverage[9];
	int flag = 0;
	switch (direction) {
	case 1:
		for (int i = -2; i < 3; i++) a[i + 2] = overwritingPixels[(x_ + i) * cols + y_ + 2].give_z();
		for (int j = -3; j < 4; j++) b[j + 3] = overwritingPixels[(x_ + j) * cols + y_ + 3].give_z();
		for (int k = -4; k < 5; k++) c[k + 4] = overwritingPixels[(x_ + k) * cols + y_ + 4].give_z();
		new_coverage[0] = b[3];
		new_coverage[1] = c[4];
		new_coverage[2] = c[5];
		new_coverage[3] = b[4];
		new_coverage[4] = a[3];
		new_coverage[5] = a[2];
		new_coverage[6] = a[1];
		new_coverage[7] = b[2];
		new_coverage[8] = c[3];
		break;
	case 2:
		for (int i = 0; i < 3; i++) a[i] = overwritingPixels[(x_ + i) * cols + y_ + 2].give_z();
		for (int i = 1; i < 3; i++) a[i + 2] = overwritingPixels[(x_ + 2) * cols + y_ + 2 - i].give_z();
		for (int j = 0; j < 4; j++) b[j] = overwritingPixels[(x_ + j) * cols + y_ + 3].give_z();
		for (int j = 1; j < 4; j++) b[j + 3] = overwritingPixels[(x_ + 3) * cols + y_ + 3 - j].give_z();
		for (int k = 0; k < 5; k++) c[k] = overwritingPixels[(x_ + k) * cols + y_ + 4].give_z();
		for (int k = 1; k < 5; k++) c[k + 4] = overwritingPixels[(x_ + 4) * cols + y_ + 4 - k].give_z();
		new_coverage[0] = b[3];
		new_coverage[1] = c[3];
		new_coverage[2] = c[4];
		new_coverage[3] = c[5];
		new_coverage[4] = c[6];
		new_coverage[5] = b[4];
		new_coverage[6] = a[2];
		new_coverage[7] = b[2];
		new_coverage[8] = c[2];
		break;
	case 3:
		for (int i = 0; i < 5; i++) a[i] = overwritingPixels[(x_ + 2) * cols + y_ + 2 - i].give_z();
		for (int j = 0; j < 7; j++) b[j] = overwritingPixels[(x_ + 3) * cols + y_ + 3 - j].give_z();
		for (int k = 0; k < 9; k++) c[k] = overwritingPixels[(x_ + 4) * cols + y_ + 4 - k].give_z();
		new_coverage[0] = b[3];
		new_coverage[1] = c[4];
		new_coverage[2] = c[5];
		new_coverage[3] = b[4];
		new_coverage[4] = a[3];
		new_coverage[5] = a[2];
		new_coverage[6] = a[1];
		new_coverage[7] = b[2];
		new_coverage[8] = c[3];
		break;
	case 4:
		for (int i = 0; i < 3; i++) a[i] = overwritingPixels[(x_ + 2) * cols + y_ - i].give_z();
		for (int i = 1; i < 3; i++) a[i + 2] = overwritingPixels[(x_ + 2 - i) * cols + y_ - 2].give_z();
		for (int j = 0; j < 4; j++) b[j] = overwritingPixels[(x_ + 3) * cols + y_ - j].give_z();
		for (int j = 1; j < 4; j++) b[j + 3] = overwritingPixels[(x_ + 3 - j) * cols + y_ - 3].give_z();
		for (int k = 0; k < 5; k++) c[k] = overwritingPixels[(x_ + 4) * cols + y_ - k].give_z();
		for (int k = 1; k < 5; k++) c[k + 4] = overwritingPixels[(x_ + 4 - k) * cols + y_ - 4].give_z();
		new_coverage[0] = b[3];
		new_coverage[1] = c[3];
		new_coverage[2] = c[4];
		new_coverage[3] = c[5];
		new_coverage[4] = c[6];
		new_coverage[5] = b[4];
		new_coverage[6] = a[2];
		new_coverage[7] = b[2];
		new_coverage[8] = c[2];
		break;
	case 5:
		for (int i = 0; i < 5; i++) a[i] = overwritingPixels[(x_ - 2 + i) * cols + y_ - 2].give_z();
		for (int j = 0; j < 7; j++) b[j] = overwritingPixels[(x_ - 3 + j) * cols + y_ - 3].give_z();
		for (int k = 0; k < 9; k++) c[k] = overwritingPixels[(x_ - 4 + k) * cols + y_ - 4].give_z();
		new_coverage[0] = b[3];
		new_coverage[1] = c[4];
		new_coverage[2] = c[5];
		new_coverage[3] = b[4];
		new_coverage[4] = a[3];
		new_coverage[5] = a[2];
		new_coverage[6] = a[1];
		new_coverage[7] = b[2];
		new_coverage[8] = c[3];
		break;
	case 6:
		for (int i = 0; i < 3; i++) a[i] = overwritingPixels[(x_ - 2) * cols + y_ - i].give_z();
		for (int i = 1; i < 3; i++) a[i + 2] = overwritingPixels[(x_ - 2 + i) * cols + y_ - 2].give_z();
		for (int j = 0; j < 4; j++) b[j] = overwritingPixels[(x_ - 3) * cols + y_ - j].give_z();
		for (int j = 1; j < 4; j++) b[j + 3] = overwritingPixels[(x_ - 3 + j) * cols + y_ - 3].give_z();
		for (int k = 0; k < 5; k++) c[k] = overwritingPixels[(x_ - 4) * cols + y_ - k].give_z();
		for (int k = 1; k < 5; k++) c[k + 4] = overwritingPixels[(x_ - 4 + k) * cols + y_ - 4].give_z();
		new_coverage[0] = b[3];
		new_coverage[1] = c[3];
		new_coverage[2] = c[4];
		new_coverage[3] = c[5];
		new_coverage[4] = c[6];
		new_coverage[5] = b[4];
		new_coverage[6] = a[2];
		new_coverage[7] = b[2];
		new_coverage[8] = c[2];
		break;
	case 7:
		for (int i = 0; i < 5; i++) a[i] = overwritingPixels[(x_ - 2) * cols + y_ + 2 - i].give_z();
		for (int j = 0; j < 7; j++) b[j] = overwritingPixels[(x_ - 3) * cols + y_ + 3 - j].give_z();
		for (int k = 0; k < 9; k++) c[k] = overwritingPixels[(x_ - 4) * cols + y_ + 4 - k].give_z();
		new_coverage[0] = b[3];
		new_coverage[1] = c[4];
		new_coverage[2] = c[5];
		new_coverage[3] = b[4];
		new_coverage[4] = a[3];
		new_coverage[5] = a[2];
		new_coverage[6] = a[1];
		new_coverage[7] = b[2];
		new_coverage[8] = c[3];
		break;
	case 8:
		for (int i = 0; i < 3; i++) a[i] = overwritingPixels[(x_ - i) * cols + y_ + 2].give_z();
		for (int i = 1; i < 3; i++) a[i + 2] = overwritingPixels[(x_ - 2) * cols + y_ + 2 - i].give_z();
		for (int j = 0; j < 4; j++) b[j] = overwritingPixels[(x_ - j) * cols + y_ + 3].give_z();
		for (int j = 1; j < 4; j++) b[j + 3] = overwritingPixels[(x_ - 3) * cols + y_ + 3 - j].give_z();
		for (int k = 0; k < 5; k++) c[k] = overwritingPixels[(x_ - k) * cols + y_ + 4].give_z();
		for (int k = 1; k < 5; k++) c[k + 4] = overwritingPixels[(x_ - 4) * cols + y_ + 4 - k].give_z();
		new_coverage[0] = b[3];
		new_coverage[1] = c[3];
		new_coverage[2] = c[4];
		new_coverage[3] = c[5];
		new_coverage[4] = c[6];
		new_coverage[5] = b[4];
		new_coverage[6] = a[2];
		new_coverage[7] = b[2];
		new_coverage[8] = c[2];
		break;
	}
	for (int i = 0; i < 9; i++) {
		if (old_coverage[i] > maxima) maxima = old_coverage[i];
		if (old_coverage[i] < minima) minima = old_coverage[i];
	}
	maxima++;
	minima--;
	for (int i = 0; i < 5; i++) {
		if (a[i] > maxima) return -1;
		if (a[i] < minima) return -1;
	}
	for (int j = 0; j < 7; j++) {
		if (b[j] > maxima) return -1;
		if (b[j] < minima) return -1;
	}
	for (int k = 0; k < 9; k++) {
		if (c[k] > maxima) return -1;
		if (c[k] < minima) return -1;
	}
	if (recalculate_angles(new_coverage) == -1) return -1;
	return 0;
}

void rover::give_last_cords(double* x, double* y) {
	*x = pixel.back().give_x();
	*y = pixel.back().give_y();
}

void rover::printLastCords(ofstream& logControl) {
	logControl << "Cords [" << pixel.back().give_x() << ", " << pixel.back().give_y() << ", " << pixel.back().give_z() << "]. ";
}

void rover::printcords() {
	ofstream file("cordsrover.txt");
	for (size_t t = 0; t < pixel.size(); t++) {
		file << pixel[t].give_x() << " " << pixel[t].give_y() << " " << pixel[t].give_z() << endl;
	}
}

void rover::clear() {
	pixel.clear();
}