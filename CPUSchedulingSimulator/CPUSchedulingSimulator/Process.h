#pragma once
#include <vector>
#include <string>

class Process
{
public:
	//Process Data Process
	std::string pid;
	int arrivalTime;
	int burstTime;
	int priority;

	 // Computed by the scheduling algorithm:
    int startTime = 0;
    int finishTime = 0;
    int waitingTime = 0;
    int turnaroundTime = 0;
	
	
};


//
// Created by Lenovo on 12/4/2025.
//

#ifndef OS_PROCESS_H
#define OS_PROCESS_H
#include<string>
using namespace std;
class Process
{
//the attributes of the Process class are for all the algorthimis unified for every one
public:
   string pid;
    int arrivaltime;
    int bursttime;
    int priorty;
    int remaning;
    int startTime;
    int compleTime;

Process(const string id ,int arrival,int burst,int pr )
{
   pid=id;
    arrivaltime=arrival;
    bursttime=burst;
    priorty=pr;
    remaning=burst;// at the begining nothing happend so the remaining is the same as the start
    startTime=-1;
    compleTime=-1;//-1 denotes that the process hasnt finshed  yet
}
};


#endif //OS_PROCESS_H









