#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include "Process.h"
using namespace std;

// Holds the full outcome of a preemptive priority scheduling run
struct PSResult {
	struct Entry {
		string pid;
		int duration;
	};

	vector<Entry> gantt;

	struct Metrics {
		string pid;
		int arrival;
		int burst;
		int priority;
		int start;          // first time process gets CPU
		int completion;     // time when process finishes
		int turnaround;     // completion - arrival
		int waiting;        // turnaround - burst
		int response;       // start - arrival
	};

	vector<Metrics> perProcess;

	// Aggregate metrics
	double avgWaiting = 0.0;
	double avgTurnaround = 0.0;
	double avgResponse = 0.0;
	double throughput = 0.0;        // processes per time unit
	double cpuUtilization = 0.0;    // percentage
	int totalTime = 0;              // total simulation duration
};

class PrioritySchedulerP {
private:
	vector<Process> processes;
public:
	// Build a scheduler with the given process list.
	explicit PrioritySchedulerP(const vector<Process>& processes);

	// Run the simulation and return the full result (Gantt + metrics).
	PSResult simulate();

	// Print a human-readable report for a previously computed result.
	static void printReport(const PSResult& res);

};