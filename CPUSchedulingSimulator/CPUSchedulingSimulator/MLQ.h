#pragma once
#include "Process.h"
#include "PrioritySchedulerNP.h"
#include "SJF.h"
#include <iostream>
#include <vector>


class MLQ
{
public:

	//Constructor
	MLQ(std::vector<Process>& Processes) {
		
		std::vector<Process> queue1;//Highest Priority
		std::vector<Process> queue2;//Medium Priority
		std::vector<Process> queue3;//Low Priority

		//Add to the queues their respective processes depending on their Priority
		for(Process& p: Processes) {
			if (p.priority == 1)
				queue1.push_back(p);
			else if (p.priority == 2)
				queue2.push_back(p);
			else
				queue3.push_back(p);
		}

		int cpuTime = 0;

		//Queue 1(SJF)
		std::cout << "Queue 1(Shortest Job First(SJF)): " << std::endl;
		std::cout << "Process ID\t" << "Arrival Time\t" << "Burst Time\t" << "Priority\t" << "Start Time\t" << "Finish Time\t"
			<< "Waiting Time\t" << "Turnaround Time" << std::endl;

		SJF sjf(queue1, cpuTime);
		for (Process& p : queue1) {
			std::cout << p.pid << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.priority << "\t\t"
				<< p.startTime << "\t\t" << p.finishTime << "\t\t"
				<< p.waitingTime << "\t\t" << p.turnaroundTime << std::endl;
		}

		//set the cpuTime to the Maximum Finish Time
		cpuTime = getMaxFinishTime(queue1);

		std::cout <<"-------------------------------------------------------------------------------------------------------------------" << std::endl;//LINE SPACE

		//Queue 2(Priority Scheduler Non Preemptive)
		std::cout << "Queue 2(Priority Scheduler Non Preemptive): " << std::endl;
		std::cout << "Process ID\t" << "Arrival Time\t" << "Burst Time\t" << "Priority\t" << "Start Time\t" << "Finish Time\t"
			<< "Waiting Time\t" << "Turnaround Time" << std::endl;

		PrioritySchedulerNP PSNP(queue2, cpuTime);
		for (Process& p : queue2) {
			std::cout << p.pid << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.priority << "\t\t"
				<< p.startTime << "\t\t" << p.finishTime << "\t\t"
				<< p.waitingTime << "\t\t" << p.turnaroundTime << std::endl;
		}

		//set the cpuTime to the Maximum Finish Time
		cpuTime = getMaxFinishTime(queue2);


		std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;//LINE SPACE

		//Queue 3(FCFS)
		std::cout << "Queue 3(FCFS): " << std::endl;
		std::cout << "Process ID\t" << "Arrival Time\t" << "Burst Time\t" << "Priority\t" << "Start Time\t" << "Finish Time\t"
			<< "Waiting Time\t" << "Turnaround Time" << std::endl;

		FCFS fcfs(queue3, cpuTime);

		for (Process& p : queue3) {
			std::cout << p.pid << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t" << p.priority << "\t\t"
				<< p.startTime << "\t\t" << p.finishTime << "\t\t"
				<< p.waitingTime << "\t\t" << p.turnaroundTime << std::endl;
		}

		std::cout << "-------------------------------------------------------------------------------------------------------------------" << std::endl;//LINE SPACE

	}

	int getMaxFinishTime(std::vector<Process>& q) {
		//Update CpuTime
		int maxTime = 0;
		for (Process& p : q) {
			maxTime = std::max(maxTime, p.finishTime);
		}
		return maxTime;
	}
};

