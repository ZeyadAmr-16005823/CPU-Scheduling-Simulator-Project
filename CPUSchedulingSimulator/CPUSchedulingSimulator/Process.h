#pragma once
#include <vector>

class Process
{
public:
	//Process Data Process
	int pid;
	int arrivalTime;
	int burstTime;
	int priority;

	 // Computed by the scheduling algorithm:
    int startTime = 0;
    int finishTime = 0;
    int waitingTime = 0;
    int turnaroundTime = 0;
};


