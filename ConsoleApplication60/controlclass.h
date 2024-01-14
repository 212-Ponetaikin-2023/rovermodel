#include "basicfuncs.h"
#include "surfaceclass.h"
#include "processor.h"

class control {
private:
    unsigned int length;
    unsigned int width;
    unsigned int amountBumps;
    unsigned int amountStones;
    unsigned int amountLogs;
    vector <Point> overwritingPixels;
    surface terra;
    processor process;
    vector <Gaussyan> extraBumps;
    vector <stone> extraStones;
    vector <logs> extraLogs;
public:
    control(unsigned int length_ = 30, unsigned int width_ = 30, unsigned int amountBumps_ = 3, unsigned int amountStones_ = 3, unsigned int amountLogs_ = 3);

    int fillUserDataofSurface(ofstream& logControl, vector<string> data);

    void checkandfillBump(vector <double> massBump, string answer, ofstream& logControl);

    void checkandfillStone(vector <double> massBump, string answer, ofstream& logControl);

    void checkandfillLog(vector <double> massBump, string answer, ofstream& logControl);

    int notation_cords_rover(vector <double> cords, string answer, ofstream& logControl);

    int StartRover(vector <string> commands, string answer, vector <string> patternsRover, ofstream& logControl);

    void createSurface();
};