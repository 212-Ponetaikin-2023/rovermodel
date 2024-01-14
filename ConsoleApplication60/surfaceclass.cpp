#include "surfaceclass.h"

surface::surface(int length, int width) {
    len = length; wid = width;
}

double GetRandom(double min, double max)
{
    double value;
    value = rand() % 1000;
    value = min + (value / 1000) * (max - min);
    return value;
}

void surface::fill(unsigned int GLO_BUMPS, unsigned int GLO_STONES, unsigned int GLO_LOGS) {
    double x_0, y_0, sg_x, sg_y, h, alpha;
    double x, y, R;
    double x1, y1, x2, y2, r;
    for (unsigned int i = 0; i < GLO_BUMPS; i++) {
        x_0 = GetRandom(len / 10, len * 9 / 10);
        y_0 = GetRandom(wid / 10, wid * 9 / 10);
        sg_x = GetRandom(1, 5);
        sg_y = GetRandom(1, 5);
        h = GetRandom(-8, 8);
        alpha = GetRandom(0, 3.1);
        bumps.push_back(Gaussyan(x_0, y_0, sg_x, sg_y, h, alpha));
    }
    for (unsigned int i = 0; i < GLO_STONES; i++) {
        x = GetRandom(len / 10, len * 9 / 10);
        y = GetRandom(wid / 10, wid * 9 / 10);
        R = GetRandom(1, 3);
        hSpheres.push_back(stone(x, y, R));
    }
    for (unsigned int i = 0; i < GLO_LOGS; i++) {
        x1 = GetRandom(len / 10, len * 9 / 10);
        x2 = GetRandom(len / 10, len * 9 / 10);
        y1 = GetRandom(wid / 10, wid * 9 / 10);
        y2 = GetRandom(wid / 10, wid * 9 / 10);
        r = GetRandom(1, 3);
        hLogs.push_back(logs(x1, y1, x2, y2, r));
    }
}

void surface::print_cord(string fileCord, int len, int wid, vector <Gaussyan> ExtraBump, vector <stone> ExtraStone, vector <logs> ExtraLogs, double **pixels) {
    ofstream file;
    file.open(fileCord);
    double x, y, sum_z;
    unsigned int rBumps, rStones, rLogs, extraRbumps, extraRstones, extraRlogs;
    
    rBumps = bumps.size();
    rStones = hSpheres.size();
    rLogs = hLogs.size();
    extraRbumps = ExtraBump.size();
    extraRstones = ExtraStone.size();
    extraRlogs = ExtraLogs.size();
    for (double i = 0; i < len / step; i++) {
        x = i * step;
        for (double j = 0; j < wid / step; j++) {
            y = j * step;
            sum_z = 0;
            for (unsigned int k = 0; k < rBumps; k++) {
                sum_z += bumps[k].z_gauss(x, y);
            }
            for (unsigned int k = 0; k < rStones; k++) {
                sum_z += hSpheres[k].z_stone(x, y);
            }
            for (unsigned int k = 0; k < rLogs; k++) {
                sum_z += hLogs[k].z_log(x, y);
            }
            for (unsigned int k = 0; k < extraRbumps; k++) {
                sum_z += ExtraBump[k].z_gauss(x, y);
            }
            for (unsigned int k = 0; k < extraRstones; k++) {
                sum_z += ExtraStone[k].z_stone(x, y);
            }
            for (unsigned int k = 0; k < extraRlogs; k++) {
                sum_z += ExtraLogs[k].z_log(x, y);
            }
            file << x << ' ' << y << ' ' << sum_z << '\n';
            pixels[(int)i][(int)j] = sum_z;
        }
    }
    file.close();
}