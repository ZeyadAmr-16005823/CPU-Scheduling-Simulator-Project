#pragma once
#include "Process.h"

class FCFS
{

public:

	//Constructor
	FCFS(vector<Process>& Processes, int cpuTime = 0) {

		Processes = Processes;
		cpuTime = 0;
	}
	void calculateTimes(vector<Process>& Processes) {
		int currentTime = 0;
		for (auto& process : Processes) {
			if (currentTime < process.arrivalTime) {
				currentTime = process.arrivalTime;
			}
			process.startTime = currentTime;
			process.finishTime = process.startTime + process.burstTime;
			process.waitingTime = process.startTime - process.arrivalTime;
			process.turnaroundTime = process.finishTime - process.arrivalTime;
			currentTime = process.finishTime;
		}
	}
	void displayProcesses(const vector<Process>& Processes) {
		cout << "PID\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\tResponse\n";
		for (const auto& process : Processes) {
			cout << process.pid << "\t"
				<< process.arrivalTime << "\t"
				<< process.burstTime << "\t"
				<< process.startTime << "\t"
				<< process.finishTime << "\t"
				<< process.waitingTime << "\t"
				<< process.turnaroundTime << "\t\t"
				<< process.responseTime << "\n";
		}
	}
	void displayTimes(const vector<Process>& Processes) {
		int totalWaitingTime = 0;
		int totalTurnaroundTime = 0;
		for (const auto& process : Processes) {
			totalWaitingTime += process.waitingTime;
			totalTurnaroundTime += process.turnaroundTime;
		}
		double avgWaitingTime = static_cast<double>(totalWaitingTime) / Processes.size();
		double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / Processes.size();
		cout << "Average Waiting Time: " << avgWaitingTime << "\n";
		cout << "Average Turnaround Time: " << avgTurnaroundTime << "\n";
	}
	void inputBurstTimes(vector<Process>& Processes) {
		for (auto& process : Processes) {
			cout << "Enter burst time for process " << process.pid << ": ";
			cin >> process.burstTime;
		}

  

};



