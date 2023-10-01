#define step 0.25
#define MAX_ELEM_BUMP 10
#define MAX_ELEM_STON 7
#define MAX_ELEM_LOGS 5

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <fstream>
//#include <vector>
using namespace std;

unsigned int GLO_BUMPS = 7;
unsigned int GLO_STONES = 7;
unsigned int GLO_LOGS = 7;

double sqr(double t) {
    return t * t;
}

double povorot(double x, double x_0, double y, double y_0, double angle, bool flag) {
    if (flag == true) return sqr((x - x_0) * cos(angle) - (y - y_0) * sin(angle));
    if (flag == false) return sqr((x - x_0) * sin(angle) + (y - y_0) * cos(angle));
}

class Point {
protected:
    double x_0, y_0, z;
};

class Gaussyan : public Point{
private:
    double sigma_x, sigma_y, height, angle;
public:
    Gaussyan(double x = 0, double y = 0, double sgm_x = 1, double sgm_y = 1, double A = 0, double angle_ = 0);
    double z_gauss(double x, double y) {
        z = height * exp(-((povorot(x, x_0, y, y_0, angle, true) / (2 * sqr(sigma_x))) + (povorot(x, x_0, y, y_0, angle, false) / (2 * sqr(sigma_y)))));
        return z;
    }
};

Gaussyan::Gaussyan(double x, double y, double sgm_x, double sgm_y, double A, double angle_) {
    x_0 = x; y_0 = y; sigma_x = sgm_x; sigma_y = sgm_y; height = A; angle = angle_;
}

class stone : public Point{
private:
    double R;
public:
    stone(double x = 0, double y = 0, double r = 0);
    double z_stone(double x, double y) {
        if ((sqr(x - x_0) + sqr(y - y_0)) < sqr(R)) {
            z = sqrt(sqr(R) - sqr(x - x_0) - sqr(y - y_0));
            return z;
        }
        else return 0;
    }
};

stone::stone(double x, double y, double r) {
    x_0 = x; y_0 = y; R = r;
}

class logs {
private:
    double x1, y1, x2, y2, R;
public:
    logs(double x1_ = 0, double y1_ = 0, double x2_ = 0, double y2_ = 0, double Rad = 0);
    double z_log(double x, double y);
};

logs::logs(double x1_, double y1_, double x2_, double y2_, double Rad) {
    x1 = x1_; x2 = x2_; y1 = y1_; y2 = y2_; R = Rad;
}

double FirstCordofOrtVtr(double a, double b, double R) {
    return (R * b) / sqrt(sqr(a) + sqr(b));
}

double SecondCordofOrtVtr(double a, double b, double firstCord) {
    return - (a * firstCord / b);
}

int sgn(double x) {
    if (x > 0) return 1;
    else if (x == 0) return 0;
    else return -1;
}

double logs::z_log(double x, double y) {
    double a, b, c, d, value1, value2, value3, value4, z_value;
    int sgnvalue1, sgnvalue2, sgnvalue3, sgnvalue4;
    double u, v;

    a = x2 - x1;
    b = y2 - y1;
    c = FirstCordofOrtVtr(a, b, R);
    d = SecondCordofOrtVtr(a, b, c);
    value1 = b * x - a * y - b * (x1 + c) + a * (y1 + d);
    value2 = b * x - a * y - b * (x1 - c) + a * (y1 - d);
    value3 = d * x - c * y + c * y1 - d * x1;
    value4 = d * x - c * y + c * y2 - d * x2;
    sgnvalue1 = sgn(value1);
    sgnvalue2 = sgn(value2);
    sgnvalue3 = sgn(value3);
    sgnvalue4 = sgn(value4);
    if (abs(sgnvalue1 + sgnvalue2) > 1 || abs(sgnvalue3 + sgnvalue4) > 1) return 0;
    else {
        u = fabs(b * x - a * y - b * (x1 + c) + a * (y1 + d)) / sqrt(sqr(a) + sqr(b));
        v = fabs(b * x - a * y - b * (x1 - c) + a * (y1 - d)) / sqrt(sqr(a) + sqr(b));
        return sqrt(u * v);
    }
}

class surface {
private:
    Gaussyan bump[MAX_ELEM_BUMP];
    stone hSphere[MAX_ELEM_STON];
    logs hLogs[MAX_ELEM_LOGS];
    int len, wid;
public:
    surface(ofstream& file, int length = 0, int width = 0);
    void fill(int len, int wid, Gaussyan bump[], stone hSphere[], logs hLogs[]);
    void print_cord(ofstream& file, int len, int wid);
};

surface::surface(ofstream& file, int length, int width) {
    len = length; wid = width;
    fill(len, wid, bump, hSphere, hLogs);
    print_cord(file, len, wid);
}

double GetRandom(double min, double max)
{
    double value;
    value = rand() % 1000;
    value = min + (value / 1000) * (max - min);
    return value;
}

void surface::fill(int len, int wid, Gaussyan bump[], stone hSphere[], logs hLogs[]) {
    double x_0, y_0, sg_x, sg_y, h, alpha;
    double x, y, R;
    double x1, y1, x2, y2, r;
    for (int i = 0; i < MAX_ELEM_BUMP; i++) {
        x_0 = GetRandom(len / 10, len * 9 / 10);
        y_0 = GetRandom(wid / 10, wid * 9 / 10);
        sg_x = GetRandom(1, 5);
        sg_y = GetRandom(1, 5);
        h = GetRandom(-8, 8);
        alpha = GetRandom(0, 3.1);
        bump[i] = Gaussyan(x_0, y_0, sg_x, sg_y, h, alpha);
    }
    for (int i = 0; i < MAX_ELEM_STON; i++) {
        x = GetRandom(len / 10, len * 9 / 10);
        y = GetRandom(wid / 10, wid * 9 / 10);
        R = GetRandom(1, 5);
        hSphere[i] = stone(x, y, R);
    }
    for (int i = 0; i < MAX_ELEM_LOGS; i++) {
        x1 = GetRandom(len / 10, len * 9 / 10);
        x2 = GetRandom(len / 10, len * 9 / 10);
        y1 = GetRandom(wid / 10, wid * 9 / 10);
        y2 = GetRandom(wid / 10, wid * 9 / 10);
        r = GetRandom(1, 4);
        hLogs[i] = logs(x1, y1, x2, y2, r);
    }
}

void surface::print_cord(ofstream& file, int len, int wid) {
    double x, y, sum_z;
    for (double i = 0; i < len / step; i++) {
        x = i * step;
        for (double j = 0; j < wid / step; j++) {
            y = j * step;
            sum_z = 0;
            for (int k = 0; k < MAX_ELEM_BUMP; k++) {
                sum_z += bump[k].z_gauss(x, y);
            }
            for (int k = 0; k < MAX_ELEM_STON; k++) {
                sum_z += hSphere[k].z_stone(x, y);
            }
            for (int k = 0; k < MAX_ELEM_LOGS; k++) {
                sum_z += hLogs[k].z_log(x, y);
            }
            file << x << ' ' << y << ' ' << sum_z << '\n';
        }
    }
}

int main()
{
    unsigned int len = 0, wid = 0;
    srand(time(NULL));
    ofstream file;
    file.open("cord.txt");
    cin >> len >> wid;
    if (file.is_open()) {
        surface surf(file, len, wid);
    }
    file.close();
    return 0;
}