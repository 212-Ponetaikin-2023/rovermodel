#include "basicfuncs.h"
#include "controlclass.h"
class boundary {
private:
    string config;
    vector <string> patternsConfig = { "Date recording - .*;", "Name of the logs file Boundary - .*;",
     "Name of the logs file Control - .*;", "Name of the command file - .*;", "Name of the rover command file - .*;"};
    vector <string> patternsCommand = { "Field generation.*;", "Length - .*;", "Width - .*;",
        "Number of gaussyans - .*;", "Number of stones - .*;", "Number of logs - .*;" };
    vector <string> patternsAddCommand = { "Add gauss -.*;", "Add stone -.*;", "Add log -.*;" };
    vector <string> patternsRoverCommand = { "Start in .*;", "Finish in .*;"};
    vector <string> answers;
    vector <string> extraAnswers;
    vector <string> rovercommands;
    control controller;
public:
    boundary(string filename = "config.txt");
    int read_configfile(string config);
    int readFirstPartofCommandFile(ifstream& filecommand, ofstream& logBound);
    void readSecondPartofCommandFile(ifstream& filecommand, ofstream& logBound, ofstream& logControl);
    void readRoverCommandFile(ofstream& logBound, ofstream& logControl, ifstream& rovercommandfile);
};