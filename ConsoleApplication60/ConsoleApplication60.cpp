#define step 0.5
#define MAX_ELEM_BUMP 10

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <fstream>
using namespace std;

double sqr(double t) {
    return t * t;
}

double povorot(double x, double x_0, double y, double y_0, double angle, bool flag) {
    if (flag == true) return sqr((x - x_0) * cos(angle) - (y - y_0) * sin(angle));
    if (flag == false) return sqr((x - x_0) * sin(angle) + (y - y_0) * cos(angle));
}

class Gaussyan {
private:
    double x_0, y_0, sigma_x, sigma_y, height, angle;
public:
    Gaussyan(double x = 0, double y = 0, double sgm_x = 1, double sgm_y = 1, double A = 0, double angle_ = 0);
    double z_gauss(double x, double y) {
        return height * exp(-((povorot(x, x_0, y, y_0, angle, true) / (2 * sqr(sigma_x))) + (povorot(x, x_0, y, y_0, angle, false) / (2 * sqr(sigma_y)))));
    }
};

Gaussyan::Gaussyan(double x, double y, double sgm_x, double sgm_y, double A, double angle_) {
    x_0 = x; y_0 = y; sigma_x = sgm_x; sigma_y = sgm_y; height = A; angle = angle_;
}

double GetRandom(double min, double max)
{
    double value;
    value = rand() % 1000;
    value = min + (value / 1000) * (max - min);
    return value;
}

void fulfill(int len, int wid, Gaussyan bump[]) {
    double x_0, y_0, sg_x, sg_y, h, alpha;
    for (int i = 0; i < MAX_ELEM_BUMP; i++) {
        x_0 = GetRandom(len / 10, len * 9 / 10);
        y_0 = GetRandom(wid / 10, wid * 9 / 10);
        sg_x = GetRandom(1, 5);
        sg_y = GetRandom(1, 5);
        h = GetRandom(-7, 15);
        alpha = GetRandom(0, 3.1);
        bump[i] = Gaussyan(x_0, y_0, sg_x, sg_y, h, alpha);
    }
}

void print_cord(ofstream &file, int len, int wid, Gaussyan bump[]) {
    double x, y, sum_z;
    for (double i = 0; i < len * 2; i++) {
        x = i / 2;
        for (double j = 0; j < wid * 2; j++) {
            y = j / 2;
            sum_z = 0;
            for (int k = 0; k < MAX_ELEM_BUMP; k++) {
                sum_z += bump[k].z_gauss(x, y);
            }
            file << x << ' ' << y << ' ' << sum_z << '\n';
        }
    }
}

int main()
{
    unsigned int len = 0, wid = 0;
    srand(time(NULL));
    Gaussyan bump[MAX_ELEM_BUMP];
    ofstream file;
    file.open("cord.txt");
    cin >> len >> wid;
    fulfill(len, wid, bump);
    if (file.is_open()) {
        print_cord(file, len, wid, bump);
    }
    file.close();
    return 0;
}