#include "gaussclass.h"
#include "stoneclass.h"
#include "logsclass.h"
#include "basicfuncs.h"

class surface {
private:
    vector <Gaussyan> bumps;
    vector <stone> hSpheres;
    vector <logs> hLogs;
    int len, wid;
public:
    surface(int length = 0, int width = 0);
    void fill(unsigned int GLO_BUMPS, unsigned int GLO_STONES, unsigned int GLO_LOGS);
    void print_cord(string fileCord, int len, int wid, vector <Gaussyan> ExtraBump, vector <stone> ExtraStone, vector <logs> ExtraLogs, double** pixels);
};