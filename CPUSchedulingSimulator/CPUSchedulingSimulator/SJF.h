#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include "Process.h"

using namespace std;

class SJF {
public:
    SJF(vector<Process>& processes, int currentTime = 0){

        int CompletedProcesses = 0;  // its acts as a counter for the finished processes
        int n = processes.size();  //number of processes

        vector<bool> isCompleted(n, false);

        while (CompletedProcesses < n) {
            int smallestIndex = -1;  // showing that the smallest index we can have would be below 0 (-1 and below)
            int minBurstTime = INT_MAX;  // INT_MAX is the largest number that could be stored on the computer


            for (int i = 0; i < n; i++) {   // loops over all the processes to find the best one with the shortest burstTime(SJF) and its index.
                if (!isCompleted[i] && processes[i].arrivalTime <= currentTime && processes[i].burstTime < minBurstTime) {
                    minBurstTime = processes[i].burstTime;
                    smallestIndex = i;
                }
            }

            if (smallestIndex == -1) {
                //i added the current time aswell so that we can see when the processes are idle.
                cout << "current time is:" << currentTime << "Idle, no process is available right now" << endl;


                int nextArrival = INT_MAX;
                for (int i = 0; i < n; i++) {
                    if (!isCompleted[i] && processes[i].arrivalTime > currentTime) {
                        nextArrival = min(nextArrival, processes[i].arrivalTime);
                    }
                }

                currentTime = nextArrival;
                continue;
            }
            else {
                //Mark the process at the current smallestIndex as done.
                isCompleted[smallestIndex] = true;

                Process& p = processes[smallestIndex];

                //Strat time
                p.startTime = currentTime;

                //Finish Time
                processes[smallestIndex].finishTime = processes[smallestIndex].startTime + processes[smallestIndex].burstTime;
                currentTime = processes[smallestIndex].finishTime;

                //Turnaround Time
                processes[smallestIndex].turnaroundTime = processes[smallestIndex].finishTime - processes[smallestIndex].arrivalTime;

                //Waiting Time
                processes[smallestIndex].waitingTime = processes[smallestIndex].startTime - processes[smallestIndex].arrivalTime;

                //Add the completed processes by 1
                CompletedProcesses++;
            
            }

        }

    }

};
