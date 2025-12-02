#include "PrioritySchedulerP.h"
#include <algorithm>
#include <iostream>

using namespace std;

PrioritySchedulerP::PrioritySchedulerP(const vector<Process>& processes)
    : processes(processes)
{}

vector<PSResult::Entry> compressTimeline(const vector<string>& timeline) {
// converts timeline into readable Gantt chart table

    vector<PSResult::Entry> result;

    if (timeline.empty()) return result;

    string curr = timeline[0];
    int count = 1;

    for (int i = 1; i < timeline.size(); i++) {
        if (timeline[i] == curr) {
            count++;
        } else {
            result.push_back({curr, count});
            curr = timeline[i];
            count = 1;
        }
    }
    result.push_back({curr, count});
    return result;
}

PSResult PrioritySchedulerP::simulate() {
    PSResult result;

    struct ProcessInfo {
        // simplifies process information
        string pid;
        int arrival;
        int burst;
        int remaining; // remaining time of current process
        int priority;
        int startTime = -1;
        int completionTime = -1;
    };

    vector<ProcessInfo> procs;

    for (int i = 0; i < processes.size(); i++) {
        // copy all process data
        ProcessInfo p;
        // Process.pid is an int; store a readable id string
        p.pid = to_string(processes[i].pid);
        p.arrival = processes[i].arrivalTime;
        p.burst = processes[i].burstTime;
        p.remaining = processes[i].burstTime;
        p.priority = processes[i].priority;
        procs.push_back(p);
    }

    sort(procs.begin(), procs.end(), [](const ProcessInfo& a, const ProcessInfo& b) {
        return a.arrival < b.arrival; // sort procs in ascending order of arrival time using lambda function
    });

    int n = procs.size();
    if (n == 0) return result;

    int time = procs[0].arrival; // initialize start
    int done = 0; // finished processes counter
    int busyTime = 0; // cpu busy time
    vector<string> timeline; // for recording

    while (done < n) { // runs until all processes are complete
        // each loop iteration is equal 1 time unit passing as to follow preemptivity
        int best = -1;

        for (int i = 0; i < n; i++) {
            if (procs[i].remaining <= 0) continue;
            if (procs[i].arrival > time) continue;

            if (best == -1) { // first process
                best = i;
            } else { // allow for preemptivity
                if (procs[i].priority < procs[best].priority) {
                    best = i; // lower num = higher prio
                } else if (procs[i].priority == procs[best].priority) {
                    // tie-breaker -> FCFS
                    if (procs[i].arrival < procs[best].arrival) {
                        best = i;
                    }
                }
            }
        }

        if (best == -1) {
            timeline.push_back("IDLE");
            time++;
            continue;
        }

        if (procs[best].startTime == -1) {
            procs[best].startTime = time; // sync time when a processer first gets cpu
        }

        timeline.push_back(procs[best].pid);
        procs[best].remaining--;
        time++;
        busyTime++; // cpu per time unit recorded in Gantt chart

        if (procs[best].remaining == 0) {
            procs[best].completionTime = time;
            done++; // each completed process finished an iteration
        }
    }

    result.gantt = compressTimeline(timeline);
    result.totalTime = time - procs[0].arrival;
    // Gantt chart start time is relative to when first process arrives

    double totalWait = 0;
    double totalTurnaround = 0;
    double totalResponse = 0;

    for (int i = 0; i < n; i++) {
        PSResult::Metrics m; // initialize metrics

        m.pid = procs[i].pid;
        m.arrival = procs[i].arrival;
        m.burst = procs[i].burst;
        m.priority = procs[i].priority;
        m.start = procs[i].startTime;
        m.completion = procs[i].completionTime;

        m.turnaround = m.completion - m.arrival;
        m.waiting = m.turnaround - m.burst;
        m.response = m.start - m.arrival;

        result.perProcess.push_back(m);

        totalWait += m.waiting;
        totalTurnaround += m.turnaround;
        totalResponse += m.response;
    }

    // completed scheduling stats
    result.avgWaiting = totalWait / n;
    result.avgTurnaround = totalTurnaround / n;
    result.avgResponse = totalResponse / n;
    result.throughput = (double)n / result.totalTime;
    result.cpuUtilization = (double)busyTime / result.totalTime * 100.0;

    return result;
}

void PrioritySchedulerP::printReport(const PSResult& res) {
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < res.gantt.size(); i++) {
        cout << res.gantt[i].pid << "(" << res.gantt[i].duration << "), " ;
    }
    cout << "\n\n";

    cout << left << setw(8) << "PID" // set table headers
         << setw(10) << "Arrival"
         << setw(8) << "Burst"
         << setw(10) << "Priority"
         << setw(8) << "Start"
         << setw(12) << "Completion"
         << setw(12) << "Turnaround"
         << setw(10) << "Waiting"
         << setw(10) << "Response" << "\n";

    for (int i = 0; i < res.perProcess.size(); i++) {
        const PSResult::Metrics& m = res.perProcess[i];
        cout << left << setw(8) << m.pid // print all process metrics onto Gantt chart
             << setw(10) << m.arrival
             << setw(8) << m.burst
             << setw(10) << m.priority
             << setw(8) << m.start
             << setw(12) << m.completion
             << setw(12) << m.turnaround
             << setw(10) << m.waiting
             << setw(10) << m.response << "\n";
    }

    cout << "\nAverage Waiting Time: " << res.avgWaiting << "\n";
    cout << "Average Turnaround Time: " << res.avgTurnaround << "\n";
    cout << "Average Response Time: " << res.avgResponse << "\n";
    cout << "Throughput: " << res.throughput << "\n";
    cout << "CPU Utilization: " << res.cpuUtilization << "%\n";
}