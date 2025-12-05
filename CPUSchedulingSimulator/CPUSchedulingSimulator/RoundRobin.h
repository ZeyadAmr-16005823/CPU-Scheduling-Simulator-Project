//
// Created by Lenovo on 12/4/2025.
//
#include <iostream>
#include "Process.h"
#ifndef OS_ROUNDROBIN_H
#define OS_ROUNDROBIN_H
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
struct GanttSlice { // to create objects for grantt chart creation
    int start;
    int end;
    string pid;
};
class RoundRobin
{
private:
    int Quantamtime;
    std::vector<Process>RRprocess;// intilizae an empty vector for the variabels of the RR process
    vector<GanttSlice> gantt;
public:

    RoundRobin(int q,  const std::vector<Process>& Rprocess)
    {
Quantamtime=q;// this takes intilaizes our quantamtime

        for ( const Process& s:Rprocess)
        {
Process RR(s.pid,s.arrivaltime,s.bursttime,s.priorty);// intlizae the the varibels of process for the RR algorithim
RRprocess.push_back(RR); // this is a functioun that adds an element at the end of the vector
        }

    }
void go()
    {

int n =RRprocess.size();// get the number of process the algorithim will work on via getting the length of the vector as the vector contains all the process
  //edge cases
        if (n==0)return;
sort(RRprocess.begin(),RRprocess.end(),
    []( const Process& a, const Process& b )//[] is a lambda [] is a helper method with no name i want to comapre between a and b to sort them asecdlingy so it get me a boolean as an output
    { // the parmeters are refrences of objects from our vector RRprocess and the .end and .begin defines the scope i want tha to be implemented in
        return a.arrivaltime<b.arrivaltime;
    });
int cputime=RRprocess[0].arrivaltime;
int finshed=0;
int nextProcess=0;
queue<int>ready;
 // these are intliazed here as these belong to the algorthim(running) that applies not the process
while (nextProcess<n && RRprocess[nextProcess].arrivaltime<=cputime)
{   // this loop adds proces to the qeue as soon as they arrive two parts nextProces<n are there any process left ?
    // the second one is RRprocess[nextProces].arrivaltime<=time is a vital point of RR algorithim it simply
    //  diffrentiates between the arrival time of a process and the cpu time so if a process arrived at the same time as cpu time enter the ready qeue and if a process arrives after at a time more than the cpu time admit as there could be a time where process waited until some other finshed its quantam time

    ready.push(nextProcess);
    nextProcess++;
}
// here finshed refers to the finshed process comapred to the amount
while (finshed<n)
{
    if (ready.empty())
    { // this is here to handle when there are large time diffrences between the process so this fastforwards to the time of the next process as the cpu sits idle

        cputime=RRprocess[nextProcess].arrivaltime;
        // so this adds the process at the end to the ready  qeue instead of waiting which is impractical in loops
        while (nextProcess<n && RRprocess[nextProcess].arrivaltime<=cputime)
        {
            ready.push(nextProcess);
            nextProcess++;
        }
        continue; // continue the loop normally that this case is handeld

    }


    int i =ready.front(); // get the one waiting the longest this will gets us the index of the process
    ready.pop();// remove the process from the qeue as it is now in the cpu
    Process &p=RRprocess[i]; // alias for the process named p
    if (p.startTime==-1)
    {  // at the start we made the startTime -1 signaling the process didnt start
        p.startTime=cputime;// so we say it started at the current time(cpu time)
    }
    int runtime; // so in this tells us when to use the full quantam time and when to use less (when the bursts left is less  than the Quantam time so you dont need to use quantam time)

    if (p.remaning>=Quantamtime)
        runtime=Quantamtime;
    else
        runtime=p.remaning;

    cputime += runtime;     // add the time to the cpu time
    p.remaning -= runtime;   // minus what is left of the remaning either quantum or less
    // minus what is left of the remaning either quantum or less
    gantt.push_back({cputime - runtime, cputime, p.pid});

    // this adds process while the cpu is executing handels another cases as we just ipdated time (cpu time)
    while (nextProcess<n && RRprocess[nextProcess].arrivaltime<=cputime)
    {
        ready.push(nextProcess);
        nextProcess++;
    }

    if (p.remaning==0)
    {
        p.compleTime=cputime; // the current finsished at the time
        finshed++; // a process is fineshed
    }
    else
    {ready.push(i);}
}




    }

void getCompletionTimes()const
    {
cout<<"Completion Times"<<endl;
 for (int i=0;i<RRprocess.size();i++)
 { cout<<"Process"<<RRprocess[i].pid;
cout<< "Completion time"<<RRprocess[i].compleTime<<endl;

 }
cout<<endl;
    }

    void getWT()
    {  // WT=TAT-cpu burst time
cout<<"Waiting times "<<endl;
 for (int i=0;i<RRprocess.size();i++)
 {
     double tat=RRprocess[i].compleTime-RRprocess[i].arrivaltime;
     double wt= tat-RRprocess[i].bursttime;
     cout<<"Process"<<RRprocess[i].pid<<endl;
     cout<<"waiting time "<<wt<<endl;


 }
cout<<endl;


    }
void getRT()
    {
cout<<"Response Time "<<endl;
  // time spent in ready qeue till first -quantam time
    for (int i=0;i<RRprocess.size();i++)
    {
double RT=RRprocess[i].startTime-RRprocess[i].arrivaltime;
        cout<<"Process"<<RRprocess[i].pid<<endl;
        cout<<" Response Time :"<<RT<<endl;


    }



cout<<endl;


    }
void getavgWT()
    {
// edge case handling
 if (RRprocess.empty())
 {
cout<<"Average Wait time is 0"<<endl;
return; // to not divide by zero
 }
double sumwt=0;
for (int i=0;i<RRprocess.size();i++)
{
    double tat=RRprocess[i].compleTime-RRprocess[i].arrivaltime;
    double wt= tat-RRprocess[i].bursttime;
    sumwt+=wt;

}

double avgwt=sumwt/RRprocess.size();
cout<<"Average Wait Time"<<endl;
cout<<"Average WT:"<<avgwt<<endl;

        cout<<endl;
    }
void getavgTAT()
    {
        if (RRprocess.empty())
        {
            cout<<"Average Turnaroud Time is 0"<<endl<<endl;
return; // to not divide by 0
        }
double sumTAT=0;
        for (int i=0;i<RRprocess.size();i++)
        {
            double tat=RRprocess[i].compleTime-RRprocess[i].arrivaltime;

sumTAT+=tat;

        }

        double avgTaT=sumTAT/RRprocess.size();
        cout<<"Average Turnaroud time"<<endl;
        cout<<"Average TAT:"<<avgTaT<<endl;
    }
    void getThroughput() const
    {
        cout << "Throughput " << endl;

        if (RRprocess.empty())
        {
            cout << "Throughput is 0" << endl << endl;
            return;
        }

        int firstArrival = RRprocess[0].arrivaltime;
        int lastCompletion = RRprocess[0].compleTime;

        for (int i = 1; i < RRprocess.size(); i++)
        {
            if (RRprocess[i].arrivaltime < firstArrival)// find earliest arrival time
                firstArrival = RRprocess[i].arrivaltime;

            if (RRprocess[i].compleTime > lastCompletion)// find the latest completetion timw
                lastCompletion = RRprocess[i].compleTime;
        }

        int totalTime = lastCompletion - firstArrival;

        if (totalTime <= 0)
        {
            cout << "Throughput is 0" << endl << endl;
            return;
        }

        double thr = (double)RRprocess.size() / totalTime;
// how many process finsih per unit time
        cout << "Throughput = " << thr <<  endl;
    }
    void getCPUutil() const
    {
        cout << " CPU Utilization " << endl;
// edege case
        if (RRprocess.empty())
        {
            cout << "CPU Util is 0%" << endl << endl;
            return;
        }

        int busy = 0;

        for (int i = 0; i < RRprocess.size(); i++)
        {
            busy += RRprocess[i].bursttime; // got the time the cpu was doing work
        }

        int firstArrival = RRprocess[0].arrivaltime;
        int lastCompletion = RRprocess[0].compleTime;

        for (int i = 1; i < RRprocess.size(); i++)
        {
            if (RRprocess[i].arrivaltime < firstArrival)
                firstArrival = RRprocess[i].arrivaltime;

            if (RRprocess[i].compleTime > lastCompletion)
                lastCompletion = RRprocess[i].compleTime;
        }
// same as before this gets the earliest process started and the latest one to finsish to get the total time
        int totalTime = lastCompletion - firstArrival;

        if (totalTime <= 0)
        {
            cout << "CPU Util is 0%" << endl << endl;
            return;
        }

        double util = 100.0 * (double)busy / totalTime;//calculate the percentage of (busy time of cpu-doing work/ total time of cpu)

        cout << "CPU Utilization = " << util << " %" << endl << endl;
    }


    void getGanttChart() const
    {
        cout << " Gantt Chart " << endl;

        if (gantt.empty())
        {
            cout << "No Gantt Data." << endl << endl;
            return;
        }

        for (int i = 0; i < gantt.size(); i++)
        {
            cout << "[" << gantt[i].start << "," << gantt[i].end << "] "
                 << gantt[i].pid << "  ";
        }

        cout << endl << endl;
    }



};


#endif //OS_ROUNDROBIN_H
