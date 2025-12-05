#pragma once
#include<iostream>
using namespace std;
#include "Process.h"
#include<vector>
#include <fstream>
#include <sstream>


#include<string>
class CSVReader
{
public:


    CSVReader(string file_path, vector<Process>& Processes) {
        ifstream file(file_path);
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string pid, at, bt, pr;
            getline(ss, pid, ',');
            getline(ss, at, ',');
            getline(ss, bt, ',');
            getline(ss, pr, ',');
            Process p;
            p.pid = pid;
            p.burstTime = stoi(bt);
            p.priority = stoi(pr);
            p.arrivalTime = stoi(at);

            Processes.push_back(p);

        }
        file.close();
    }

};
