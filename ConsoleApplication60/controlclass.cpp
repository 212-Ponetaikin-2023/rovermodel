#include "controlclass.h"
    control::control(unsigned int length_, unsigned int width_, unsigned int amountBumps_, unsigned int amountStones_, unsigned int amountLogs_) {
        length = length_;
        width = width_;
        amountBumps = amountBumps_;
        amountStones = amountStones_;
        amountLogs = amountLogs_;
    }

    int control::fillUserDataofSurface(ofstream& logControl, vector<string> data) {
        time_t currentTime = time(0);
        if (data[5] == "") {
            logControl << "The length value is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                length = stoi(data[5]);
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
        if (data[6] == "") {
            logControl << "The width value is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                width = stoi(data[6]);
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
        if (data[7] == "") {
            logControl << "The Number of gaussyans is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                amountBumps = stoi(data[7]);
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
        if (data[8] == "") {
            logControl << "The Number of stones is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                amountStones = stoi(data[8]);
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
        if (data[9] == "") {
            logControl << "The Number of logs is set by default! ";
            if (data[0] == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (data[0] == "No") logControl << endl;
        }
        else {
            try {
                amountLogs = stoi(data[9]);
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

    void control::checkandfillBump(vector <double> massBump, string answer, ofstream& logControl) {
        time_t currentTime = time(0);
        int error = 0;

        if (massBump.size() != 6) {
            logControl << "Get incorrect values of Gaussyan! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
            error = -1;
        }

        if (error == 0) {
            extraBumps.push_back(Gaussyan(massBump[0], massBump[1], massBump[2], massBump[3], massBump[4], massBump[5]));
            logControl << "Get correct values of Gaussyan! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
        }
    }

    void control::checkandfillStone(vector <double> massBump, string answer, ofstream& logControl) {
        time_t currentTime = time(0);
        int error = 0;

        if (massBump.size() != 3) {
            logControl << "Get incorrect values of stone! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
            error = -1;
        }

        if (error == 0) {
            extraStones.push_back(stone(massBump[0], massBump[1], massBump[2]));
            logControl << "Get correct values of stone! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
        }
    }

    void control::checkandfillLog(vector <double> massBump, string answer, ofstream& logControl) {
        time_t currentTime = time(0);
        int error = 0;

        if (massBump.size() != 5) {
            logControl << "Get incorrect values of log! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
            error = -1;
        }

        if (error == 0) {
            extraLogs.push_back(logs(massBump[0], massBump[1], massBump[2], massBump[3], massBump[4]));
            logControl << "Get correct values of log! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
        }
    }

    int control::notation_cords_rover(vector <double> cords, string answer, ofstream& logControl) {
        time_t currentTime = time(0);
        int check = 0;
        int cols = width / step;
        if (cords.size() == 4) {
            if (cords[0] < length && cords[0] > 0 && cords[1] < width && cords[1] > 0 && cords[2] < length && cords[2] > 0 && cords[3] < width && cords[3] > 0) {
                
                process = processor(cords[0], cords[2], cords[1], cords[3]);
                logControl << "Rover has created at [" << cords[0] << ", " << cords[1] << "] coordinates! ";
                if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (answer == "No") logControl << endl;
            }
            else {
                logControl << "ERROR, These values of x and y aren't correct! ";
                if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
                else if (answer == "No") logControl << endl;
            }
        }
        else {
            logControl << "ERROR, if you want to create rover, you have to input 4 values! ";
            if (answer == "Yes") logControl << "Time: " << std::asctime(std::localtime(&currentTime)) << endl;
            else if (answer == "No") logControl << endl;
        }
        return 0;
    }

    int control::StartRover(vector <string> commands, string answer, vector <string> patternsRover, ofstream& logControl) {
        int cols = width / step;
        process.building_road(overwritingPixels, cols);
        return 0;
    }

    void control::createSurface() {
        srand(time(NULL));
        terra = surface(length, width);
        terra.fill(amountBumps, amountStones, amountLogs);
        const int rows = length / step; //проверка на нецелый шаг не забыть сделать
        const int cols = width / step;
        double** pixels = new double* [rows];
        for (int l = 0; l < rows; l++) {
            pixels[l] = new double[cols];
        }
        terra.print_cord("cord.txt", length, width, extraBumps, extraStones, extraLogs, pixels);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                overwritingPixels.push_back(Point(i * step, j * step, pixels[i][j]));
            }
        }
        for (int l = 0; l < rows; l++) delete[] pixels[l];
    }
