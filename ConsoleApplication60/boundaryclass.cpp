#include "boundaryclass.h"

boundary::boundary(string filename) {
    int check, checkFirst;
    config = filename;
    check = read_configfile(config);

    if (check == 0) {
        ofstream logBound;
        logBound.open(answers[1]);
        if (logBound.is_open()) {
            ifstream filecommand(answers[answers.size() - 2]);
            if (filecommand.is_open()) {
                checkFirst = readFirstPartofCommandFile(filecommand, logBound);
                if (checkFirst == 0) {
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
                        ifstream rovercommandfile(answers[4]);
                        if (rovercommandfile.is_open()) {
                            readRoverCommandFile(logBound, logControl, rovercommandfile);
                        }
                        else {
                            cout << "ERROR, incorrect name file of rovercommands!" << endl;
                        }
                        logControl.close();
                    }
                    else {
                        cout << "ERROR, incorrect name file of logs Control!" << endl;
                    }
                }
            }
            else {
                cout << "ERROR, incorrect name of command file!" << endl;
            }
            logBound.close();
        }
        else {
            cout << "ERROR, incorrect name file of logs Boundary!" << endl;
        }
    }
}

int boundary::read_configfile(string config) {
    ifstream fileconfig(config);
    string str;
    string startDelimiter = "[";
    string endDelimiter = "]";
    int error = 0;
    unsigned int i = 0;
    while (getline(fileconfig, str)) {
        if (i >= patternsConfig.size()) {
            cout << "ERROR, only " << patternsConfig.size() - 1 << " strings in config!" << endl;
            error = -1;
            break;
        }
        regex pattern(patternsConfig[i]);
        if (regex_search(str, pattern)) {    //проверка строки с шаблоном
            size_t startPos = str.find(startDelimiter);
            size_t endPos = str.find(endDelimiter);    //вычленение данных
            if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
                std::string data = str.substr(startPos + startDelimiter.length(), endPos - startPos - startDelimiter.length());
                answers.push_back(data);    //данные пушатся в вектор
            }
        }
        else {
            cout << "ERROR, mismatch of a string with a template, see this: " << patternsConfig[i] << endl;
            error = -1;
            break;
        }
        i++;
    }
    return error;
}

int boundary::readFirstPartofCommandFile(ifstream& filecommand, ofstream& logBound) {
    string str;
    string startDelimiter = "[";
    string endDelimiter = "]";
    int j = 0;

    while (getline(filecommand, str)) {
        time_t currentTime = time(0);
        if (j == 0) {
            if (str == "Field generation;") {
                j++;
                continue;
            }
            else {
                logBound << "ERROR, mismatch of a string with a template, see this: " << patternsCommand[j] << " Yours: " << str << endl;
                return -1;
                break;
            }
        }
        regex pattern(patternsCommand[j]);
        if (regex_search(str, pattern)) {    //проверка строки с шаблоном
            
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
        else {
            logBound << "ERROR, mismatch of a string with a template, see this: " << patternsCommand[j] << endl;
            return -1;
            break;
        }
        j++;
        if (j == 6) break;
    }
    return 0;
}

void boundary::readSecondPartofCommandFile(ifstream& filecommand, ofstream& logBound, ofstream& logControl) {
    string str;
    string startDelimiter = "[";
    string endDelimiter = "]";
    vector <double> mass1;
    vector <double> mass2;
    vector <double> mass3;
    double num;
    int flag;
    while (getline(filecommand, str)) {
        time_t currentTime = time(0);
        if (str == "Field calculation;") {
            break;
        }
        flag = 0;
        for (unsigned int l = 0; l < patternsAddCommand.size(); l++) {
            regex pattern(patternsAddCommand[l]);
            if (regex_search(str, pattern)) {
                flag = 1;
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
        if (flag == 0) {
            logBound << "This command is not correct: " << str;
            if (answers[0] == "Yes") logBound << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answers[0] == "No") logBound << endl;
        }
    }
}

void boundary::readRoverCommandFile(ofstream& logBound, ofstream& logControl, ifstream& rovercommandfile) {
    string str;
    int i = 0;
    int flag = 0;
    int last_str_line = 3;
    int check_start = 0;
    double num;
    vector <double> cords;
    string startDelimiter = "[";
    string endDelimiter = "]";
    while (getline(rovercommandfile, str)) {
        time_t currentTime = time(0);
        if (i == 0) {
            regex pattern(patternsRoverCommand[0]);
            if (regex_search(str, pattern)) {
                size_t startPos = str.find(startDelimiter);
                size_t endPos = str.find(endDelimiter);    //вычленение данных
                if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
                    std::string data = str.substr(startPos + startDelimiter.length(), endPos - startPos - startDelimiter.length());
                    rovercommands.push_back(data);    //данные пушатся в вектор
                    logBound << "The {" << patternsRoverCommand[0] << "} command was read succesfully! ";
                    if (answers[0] == "Yes") logBound << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                    else if (answers[0] == "No") logBound << endl;
                }
                istringstream iss(rovercommands.back());
                string token;
                while (getline(iss, token, ',')) {
                    num = std::stod(token);
                    cords.push_back(num);
                }
                
                i++;
                continue;
            }
            else {
                logBound << "This command is not correct: " << str << " see this: " << patternsRoverCommand[0] << " ";
                if (answers[0] == "Yes") logBound << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (answers[0] == "No") logBound << endl;
                break;
            }
        }
        else if (i == 1) {
            regex pattern(patternsRoverCommand[1]);
            if (regex_search(str, pattern)) {
                size_t startPos = str.find(startDelimiter);
                size_t endPos = str.find(endDelimiter);    //вычленение данных
                if (startPos != std::string::npos && endPos != std::string::npos && startPos < endPos) {
                    std::string data = str.substr(startPos + startDelimiter.length(), endPos - startPos - startDelimiter.length());
                    rovercommands.push_back(data);    //данные пушатся в вектор
                    logBound << "The {" << patternsRoverCommand[1] << "} command was read succesfully! ";
                    if (answers[0] == "Yes") logBound << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                    else if (answers[0] == "No") logBound << endl;
                }
                istringstream iss(rovercommands.back());
                string token;
                while (getline(iss, token, ',')) {
                    num = std::stod(token);
                    cords.push_back(num);
                }

                i++;
            }
            else {
                logBound << "This command is not correct: " << str << " see this: " << patternsRoverCommand[1] << " ";
                if (answers[0] == "Yes") logBound << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (answers[0] == "No") logBound << endl;
                break;
            }
        }
        else {
            logBound << "This command is not correct: " << str << " see this: last command is " << patternsRoverCommand[1] << " ";
            if (answers[0] == "Yes") logBound << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answers[0] == "No") logBound << endl;
            break;
        }
        check_start = controller.notation_cords_rover(cords, answers[0], logControl);
        if (check_start == -1) {
            break;
        }
    }
    controller.StartRover(rovercommands, answers[0], patternsRoverCommand, logControl);
}