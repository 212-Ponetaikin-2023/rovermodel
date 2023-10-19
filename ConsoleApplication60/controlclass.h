#include "basicfuncs.h"
#include "surfaceclass.h"

class control {
private:
    unsigned int length;
    unsigned int width;
    unsigned int amountBumps;
    unsigned int amountStones;
    unsigned int amountLogs;
    surface terra;
    vector <Gaussyan> extraBumps;
    vector <stone> extraStones;
    vector <logs> extraLogs;
public:
    control(unsigned int length_ = 30, unsigned int width_ = 30, unsigned int amountBumps_ = 3, unsigned int amountStones_ = 3, unsigned int amountLogs_ = 3);

    int fillUserDataofSurface(ofstream& logControl, vector<string> data);

    void checkandfillBump(vector <double> massBump, string answer, ofstream& logControl);

    void checkandfillStone(vector <double> massBump, string answer, ofstream& logControl);

    void checkandfillLog(vector <double> massBump, string answer, ofstream& logControl);

    void createSurface();
};