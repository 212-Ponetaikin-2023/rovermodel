#define _CRT_SECURE_NO_WARNINGS
#define step 0.25

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

double sqr(double t) {
    return t * t;
}

double povorot(double x, double x_0, double y, double y_0, double angle, bool flag) {
    if (flag == true) return sqr((x - x_0) * cos(angle) - (y - y_0) * sin(angle));
    else return sqr((x - x_0) * sin(angle) + (y - y_0) * cos(angle));
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
    double a, b, c, d, value1, value2, value3, value4;
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
    vector <Gaussyan> bumps;
    vector <stone> hSpheres;
    vector <logs> hLogs;
    int len, wid;
public:
    surface(int length = 0, int width = 0);
    void fill(unsigned int GLO_BUMPS, unsigned int GLO_STONES, unsigned int GLO_LOGS);
    void print_cord(string fileCord, int len, int wid, vector <Gaussyan> ExtraBump, vector <stone> ExtraStone, vector <logs> ExtraLogs);
};

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

void surface::print_cord(string fileCord, int len, int wid, vector <Gaussyan> ExtraBump, vector <stone> ExtraStone, vector <logs> ExtraLogs) {
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
        }
    }
    file.close();
}

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
    control(unsigned int length_ = 30, unsigned int width_ = 30, unsigned int amountBumps_ = 3, unsigned int amountStones_ = 3, unsigned int amountLogs_ = 3) {
        length = length_;
        width = width_;
        amountBumps = amountBumps_;
        amountStones = amountStones_;
        amountLogs = amountLogs_;
    }

    int fillUserDataofSurface(ofstream& logControl, vector<string> data) {
        time_t currentTime = time(0);
        if (data[4] == "") {
            logControl << "The length value is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                length = stoi(data[4]);
                logControl << "The length value is correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
            catch (...) {
                logControl << "The lenght value isn't correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
        }
        if (data[5] == "") {
            logControl << "The width value is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                width = stoi(data[5]);
                logControl << "The width value is correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
            catch (...) {
                logControl << "The width value isn't correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
        }
        if (data[6] == "") {
            logControl << "The Number of gaussyans is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                amountBumps = stoi(data[6]);
                logControl << "The Number of gaussyans value is correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
            catch (...) {
                logControl << "The Number of gaussyans value isn't correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
        }
        if (data[7] == "") {
            logControl << "The Number of stones is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                amountStones = stoi(data[7]);
                logControl << "The Number of stones value is correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
            catch (...) {
                logControl << "The Number of stones value isn't correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
        }
        if (data[8] == "") {
            logControl << "The Number of logs is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                amountLogs = stoi(data[8]);
                logControl << "The Number of logs value is correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
            catch (...) {
                logControl << "The Number of logs value isn't correct! ";
                if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (data[0] == "No") logControl << endl;
            }
        }
        return 0;
    }

    void checkandfillBump(vector <double> massBump, string answer, ofstream& logControl) {
        time_t currentTime = time(0);
        int error = 0;
        for (size_t i = 0; i < 6; i++) {
            if (massBump[i] == NULL) {
                logControl << "Get incorrect values of Gaussyan! ";
                if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (answer == "No") logControl << endl;
                error = -1;
                break;
            }
        }
        if (error == 0) {
            extraBumps.push_back(Gaussyan(massBump[0], massBump[1], massBump[2], massBump[3], massBump[4], massBump[5]));
            logControl << "Get correct values of Gaussyan! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
        }
    }

    void checkandfillStone(vector <double> massBump, string answer, ofstream& logControl) {
        time_t currentTime = time(0);
        int error = 0;
        for (size_t i = 0; i < 3; i++) {
            if (massBump[i] == NULL) {
                logControl << "Get incorrect values of stone! ";
                if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (answer == "No") logControl << endl;
                error = -1;
                break;
            }
        }
        if (error == 0) {
            extraStones.push_back(stone(massBump[0], massBump[1], massBump[2]));
            logControl << "Get correct values of stone! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
        }
    }

    void checkandfillLog(vector <double> massBump, string answer, ofstream& logControl) {
        time_t currentTime = time(0);
        int error = 0;
        for (size_t i = 0; i < 5; i++) {
            if (massBump[i] == NULL) {
                logControl << "Get incorrect values of log! ";
                if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (answer == "No") logControl << endl;
                error = -1;
                break;
            }
        }
        if (error == 0) {
            extraLogs.push_back(logs(massBump[0], massBump[1], massBump[2], massBump[3], massBump[4]));
            logControl << "Get correct values of log! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
        }
    }

    void createSurface() {
        srand(time(NULL));
        terra = surface(length, width);
        terra.fill(amountBumps, amountStones, amountLogs);
        terra.print_cord("cord.txt", length, width, extraBumps, extraStones, extraLogs);
    }
};

class boundary {
private:
    string config;
    vector <string> patternsConfig = { "Date recording - .*;", "Name of the logs file Boundary - .*;",
     "Name of the logs file Control - .*;", "Name of the command file - .*;"};
    vector <string> patternsCommand = { "Field generation.*;", "Length - .*;", "Width - .*;",
        "Number of gaussyans - .*;", "Number of stones - .*;", "Number of logs - .*;" };
    vector <string> patternsAddCommand = {"Add gauss -.*;", "Add stone -.*;", "Add log -.*;"};
    vector <string> answers;
    vector <string> extraAnswers;
    control controller;
public:
    boundary(string filename = "config.txt");
    int read_configfile(string config);
    void readFirstPartofCommandFile(ifstream& filecommand, ofstream& logBound);
    void readSecondPartofCommandFile(ifstream& filecommand, ofstream& logBound, ofstream& logControl);
};

boundary::boundary(string filename) {
    int check;
    config = filename;
    check = read_configfile(config);
    
    if (check == 0) {
        ifstream filecommand(answers.back());
        ofstream logBound;
        logBound.open(answers[1]);
        readFirstPartofCommandFile(filecommand, logBound);
        
        ofstream logControl;
        logControl.open(answers[2]);
        if (logControl.is_open()) {
            controller.fillUserDataofSurface(logControl, answers);
            readSecondPartofCommandFile(filecommand, logBound, logControl);
            controller.createSurface();
            time_t currentTime = time(0);
            logControl << "The field generation was successful! ";
            if (answers[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answers[0] == "No") logControl << endl;
            logControl.close();
        }
        logBound.close();
    }
}

int boundary::read_configfile(string config) {
    ifstream fileconfig(config);
    string str;
    string startDelimiter = "[";
    string endDelimiter = "]";
    const int N_STR = 7;
    int error = 0;
    unsigned int i = 0;
    while (getline(fileconfig, str)) {
        if (i >= patternsConfig.size()) {
            cout << "ERROR, only " << patternsConfig.size() - 1 << " strings in config!" << endl;
            error = -1;
            break;
        }
        regex pattern(patternsConfig[i]);
        if (regex_match(str, pattern)) {    //проверка строки с шаблоном
            size_t startPos = str.find(startDelimiter);
            size_t endPos = str.find(endDelimiter);    //вычленение данных
            if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
                std::string data = str.substr(startPos + startDelimiter.length(), endPos - startPos - startDelimiter.length());
                answers.push_back(data);    //данные пушатся в вектор
            }
        }
        else {
            cout << "ERROR, mismatch of a string with a template, see this: " << patternsConfig[i] << endl;
            error = -1; //
            break;
        }
        i++;
    }
    return error;
}

void boundary::readFirstPartofCommandFile(ifstream& filecommand, ofstream& logBound) {
    string str;
    string startDelimiter = "[";
    string endDelimiter = "]";
    int j = 0, error = 0;

    if (logBound.is_open()) {
        while (getline(filecommand, str)) {
            time_t currentTime = time(0);

            regex pattern(patternsCommand[j]);
            if (regex_match(str, pattern)) {    //проверка строки с шаблоном
                if (j == 0) {
                    j++;
                    continue;
                }
                else {
                    size_t startPos = str.find(startDelimiter);
                    size_t endPos = str.find(endDelimiter);    //вычленение данных
                    if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
                        std::string data = str.substr(startPos + startDelimiter.length(), endPos - startPos - startDelimiter.length());
                        answers.push_back(data);    //данные пушатся в вектор
                        logBound << "The {" << patternsCommand[j] << "} command was read succesfully! ";
                        if (answers[0] == "Yes") logBound << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                        else if (answers[0] == "No") logBound << endl;
                    }
                }
            }
            else {
                logBound << "ERROR, mismatch of a string with a template, see this: " << patternsCommand[j] << endl;
                error = -1;
                break;
            }
            j++;
            if (j == 6) break;
        }
    }
}

void boundary::readSecondPartofCommandFile(ifstream& filecommand, ofstream& logBound, ofstream& logControl) {
    string str;
    string startDelimiter = "[";
    string endDelimiter = "]";
    vector <double> mass1;
    vector <double> mass2;
    vector <double> mass3;
    double num;
    while (getline(filecommand, str)) {
        time_t currentTime = time(0);
        if (str == "Field calculation;") {
            cout << "lets calculate!" << endl;
            break;
        }
        for (unsigned int l = 0; l < patternsAddCommand.size(); l++) {
            regex pattern(patternsAddCommand[l]);
            if (regex_match(str, pattern)) {
                size_t startPos = str.find(startDelimiter);
                size_t endPos = str.find(endDelimiter);    //вычленение данных
                if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
                    std::string data = str.substr(startPos + startDelimiter.length(), endPos - startPos - startDelimiter.length());
                    extraAnswers.push_back(data);    //данные пушатся в вектор
                    logBound << "The {" << patternsAddCommand[l] << "} command was read succesfully! ";
                    if (answers[0] == "Yes") logBound << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                    else if (answers[0] == "No") logBound << endl;
                }
                istringstream iss(extraAnswers.back());
                string token;
                switch (l) {
                case 0:
                    while (getline(iss, token, ',')) {
                        num = std::stod(token);
                        mass1.push_back(num);
                    }
                    controller.checkandfillBump(mass1, answers[0], logControl);
                    break;
                case 1:
                    while (getline(iss, token, ',')) {
                        num = std::stod(token);
                        mass2.push_back(num);
                    }
                    controller.checkandfillStone(mass2, answers[0], logControl);
                    break;
                case 2:
                    while (getline(iss, token, ',')) {
                        num = std::stod(token);
                        mass3.push_back(num);
                    }
                    controller.checkandfillLog(mass3, answers[0], logControl);
                    break;
                }
            }
        }
    }
}

int main()
{
    cout << "Please, input name of the config file: ";
    string name;
    cin >> name;
    boundary interface(name);
    return 0;
}