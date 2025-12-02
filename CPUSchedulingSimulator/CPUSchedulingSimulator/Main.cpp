#include "iostream"
#include "string"

#include "CSVReader.h"
#include "FCFS.h"
#include "MLFQ.h"
#include "MLQ.h"
#include "PrioritySchedulerNP.h"
#include "PrioritySchedulerP.h"
#include "RoundRobin.h"
#include "SJF.h"
#include "Process.h"


int main() {
    std::vector<Process> processes; //Dynamic array(vector is like ArrayLists)
	Process p1; p1.pid = 1; p1.arrivalTime = 0; p1.burstTime = 5; p1.priority = 2;
	Process p2; p2.pid = 2; p2.arrivalTime = 1; p2.burstTime = 3; p2.priority = 1;
	Process p3; p3.pid = 3; p3.arrivalTime = 2; p3.burstTime = 4; p3.priority = 3;

    //CSV Reader Code. Reads processes from a CSV file and initializes the processes array.


    //Scheduling Algorithm Selection and Execution Code.
	//PSP Testing:
	processes.push_back(p1);
	processes.push_back(p2);
	processes.push_back(p3);

	PrioritySchedulerP scheduler(processes);
	PSResult result = scheduler.simulate();
	PrioritySchedulerP::printReport(result);

    //Output Code. Displays the scheduling results.


    //Bonus Code for MLQ and MLFQ if implemented.



    //End of main


	return 0;
}
