#include "processor.h"
processor::processor(double start_x_, double finish_x_, double start_y_, double finish_y_) {
	start_x = start_x_;
	start_y = start_y_;
	finish_x = finish_x_;
	finish_y = finish_y_;
}

//0 - ok, 1 - up, 2 - upright, 3 - right, 4 - downright, 5 - down, 6 - downleft, 7 - left, 8 - upleft. 
int processor::maindir(double x, double y) { // можно обращаться к этой функции после каждой корректировки пути
	if (x < finish_x) {
		if (y < finish_y) return 2;
		else if (fabs(y - finish_y) < eps) return 3;
		else return 4;
	}
	else if (fabs(x - finish_x) < eps) {
		if (fabs(y - finish_y) < eps) return 0; // можно говорить, что программа закончена.
		else if (y < finish_y) return 1;
		else return 5;
	}
	else {
		if (y < finish_y) return 8;
		else if (fabs(y - finish_y) < eps) return 7;
		else return 6;
	}
}

int processor::distant(double x, double y) {
	if (sqrt(sqr(x - finish_x) + sqr(y - finish_y)) < 3 * step) return 0;
	else return 1;
}

int processor::building_road(vector <Point> overwritingPixels, int cols) {
	int dir, dir1, dir2, correctdir;
	int l = 0;
	int count = 0;
	int itermax = 0;
	double x = start_x;
	double y = start_y;
	correctdir = maindir(x, y);
	double next_x, next_y;
	rover0.create_rover(start_x, start_y, overwritingPixels, cols);
	while (1) {
		l = 0;
		dir = maindir(x, y);
		if (distant(x, y) > 2 * sqrt(2) * step + eps) {
			if (count > 9) {
				count = 0;
				correctdir = maindir(x, y);
			}
			if (rover0.screening(dir, x, y, overwritingPixels, cols) == 0) {
				rover0.teleportation(dir, overwritingPixels, cols);
				count++;
			}
			else if (rover0.screening(correctdir, x, y, overwritingPixels, cols) == 0) {
				while (l < 3) {
					if (rover0.teleportation(correctdir, overwritingPixels, cols) != 0) break;
					l++;
				}
				count = 0;
			}
			else {
				count = 0;
				dir1 = dir + 2;
				dir2 = dir - 2;
				if (dir1 > 8) dir1 -= 8;
				if (dir1 < 1) dir1 += 8;
				if (dir2 > 8) dir2 -= 8;
				if (dir2 < 1) dir2 += 8;
				
				if (rover0.screening(dir1, x, y, overwritingPixels, cols) == 0) {
					//while (l < 3) {
						//if (rover0.teleportation(dir1, overwritingPixels, cols) != 0) break;
						//l++;
					//}
					rover0.teleportation(dir1, overwritingPixels, cols);
					correctdir = dir1;
				}
				else if (rover0.screening(dir2, x, y, overwritingPixels, cols) == 0) {
					//while (l < 3) {
						//if (rover0.teleportation(dir2, overwritingPixels, cols) != 0) break;
						//l++;
					//}
					rover0.teleportation(dir2, overwritingPixels, cols);
					correctdir = dir2;
				}
				else cout << "gg" << endl;
			}
			
		}
		// все что ниже - легкая (рабочая)
		else {
			if (rover0.screening(dir, x, y, overwritingPixels, cols) == 0) {
				if (rover0.teleportation(dir, overwritingPixels, cols) != 0) break;
			}
			else {
				for (int i = 1; i < 8; i++) {
					dir = (dir++) % 8;
					if (dir == 0) dir = 8;
					if (rover0.screening(dir, x, y, overwritingPixels, cols) == 0) {
						if (rover0.teleportation(dir, overwritingPixels, cols) != 0) break;
						break;
					}
				}
			}
		}
		rover0.give_last_cords(&next_x, &next_y);
		x = next_x;
		y = next_y;
		if (maindir(x, y) == 0) {
			break;
		}
		itermax++;
		if (itermax == 200) {
			break;
		}
	}
	rover0.printcords();
	return 0;
}