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
	int responseTime = 0;
	
	
};




