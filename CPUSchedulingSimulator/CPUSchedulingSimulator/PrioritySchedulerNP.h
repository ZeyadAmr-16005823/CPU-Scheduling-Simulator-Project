#pragma once
#include "Process.h"
#include <algorithm>

class PrioritySchedulerNP
{
public:

	//Constructor
	PrioritySchedulerNP(std::vector<Process>& Processes) {

		int cpuTime = 0;
		int amount = Processes.size();
		int completed = 0;

		//Store the processes that are finished
		std::vector<bool> finished(amount, false);
		

		//Loop through all the processes
		while(completed < amount){

			//Find the first process with the Highest Priority(1 is Highest)
			int highestPriority = INFINITY;
			int index = -1;
			int i = 0;
			for (Process& p: Processes) {
				//Checking for highest Priority AND if the process
				//has arrived AND if the process is NOT finished
				if (p.priority < highestPriority && p.arrivalTime<=cpuTime && finished[i] == false) {
					highestPriority = p.priority;
					index = i;
				}
				i++;
			}
			//If no process Arrived
			if (index == -1) {
				cpuTime++;
				continue;
			}
			finished[index] = true;

			//Start Time
			Processes[index].startTime = cpuTime;

			//Finish Time
			Processes[index].finishTime = Processes[index].startTime + Processes[index].burstTime;
			cpuTime = Processes[index].finishTime;

			//Turnaround Time
			Processes[index].turnaroundTime = Processes[index].finishTime - Processes[index].arrivalTime;

			//Waiting Time
			Processes[index].waitingTime = Processes[index].startTime - Processes[index].arrivalTime;

			//Add the completed processes by 1
			completed++;
			
		}
	}

};

