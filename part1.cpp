
#include<bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Process
{
   string id;  // process ID
   int bt;    // process burst time
   int pr;    // process priority level
};

struct Scheduling
{
  string type;     // type of process scheduling algorithm
  int avgWaitTime; // the avgWaitTime of that process scheduling algorithm
};

//function to sort all process by priority level
bool priority(Process firstP, Process secondP)
{
    return (firstP.pr > secondP.pr);
}

//function to sort all process by burst time
bool burstTime(Process firstP, Process secondP)
{
    return (firstP.bt < secondP.bt);
}

// function to find the waiting time for all processes
void waitTime(Process listOfProc[], int n, int wt[])
{
    for (int i = 1; i < n ; i++){
        wt[i] = listOfProc[i-1].bt + wt[i-1] ;
    }
}

// function to calculate average time
int averageWaitTime(Process listOfProc[], int n)
{
    int wt[n], total_wt = 0;
    wt[0] = 0; // waiting time for first process is 0

    waitTime(listOfProc, n, wt);

    for (int i = 0; i < n; i++){
        total_wt = total_wt + wt[i];
    }
    int averageWait = total_wt / n;
    return averageWait;
}

//function to sort all CPU Scheduling by averageWaitTime
bool sorfAvgWait(Scheduling firstS, Scheduling secondS)
{
    return (firstS.avgWaitTime < secondS.avgWaitTime);
}

// function to find the waiting time for all processes in RR
void RRwaitTime(Process listOfProc[], int n, int wt[], int quantum)
{
	int remainBT[n]; // remaining burst times array
	for (int i = 0 ; i < n ; i++)
		remainBT[i] = listOfProc[i].bt;

	int t = 0;
  int loop = 1;// loop = 1 means will continue looping
	do {
    bool done = true;
		for (int i = 0 ; i < n; i++){
			if (remainBT[i] > 0){
				done = false; // still have burst time => not done

				if (remainBT[i] > quantum){
          t += quantum;
          remainBT[i] -= quantum;
				}
				else {
          t = t + remainBT[i];
					wt[i] = t - listOfProc[i].bt;
					remainBT[i] -= remainBT[i];
				}
			}
		}
    if (done == true){
      loop = 0; //signal that loop is finished, no more looping
    }
	} while (loop == 1);
}

// function to calculate RR average time
int RRaverageWaitTime(Process listOfProc[], int n)
{
	int wt[n], total_wt = 0;
  int quantum = 5;

	RRwaitTime(listOfProc, n, wt, quantum);

	for (int i=0; i<n; i++){
		total_wt = total_wt + wt[i];
	}
  int averageWait = total_wt / n;
  return averageWait;
}

/*void genListOfProcess(){
  ofstream file;
  file.open ("genListOfProcess.txt");
  file << "Please writr this text to a file.\n this text is written using C++\n";
  file.close();

}*/




int main()
{
    // examples
    Process listOfProc[] = {{"P1", 21, 2}, {"P2", 3, 1}, {"P3", 6, 4}, {"P4", 2, 3}};
    int n = sizeof listOfProc / sizeof listOfProc[0];

    /*
    Average waiting time for FCFS
    */
    int FCFS = averageWaitTime(listOfProc, n);
    cout << "Average waiting time for FCFS "
         << FCFS << endl;

    /*
    Average waiting time for SJF
    */
    sort(listOfProc, listOfProc + n, priority); //sort in order of priority
    int PRIOR = averageWaitTime(listOfProc, n);
    cout << "Average waiting time for Priority "
         << PRIOR << endl;

    /*
    Average waiting time for SJF
    */
    sort(listOfProc, listOfProc + n, burstTime); //sort in order of shortest bt first
    int SJF = averageWaitTime(listOfProc, n);
    cout << "Average waiting time for SJF (non-preemtive) "
         << SJF << endl;

    /*
    Average waiting time for RR
    */
    int RR = RRaverageWaitTime(listOfProc, n);
    cout << "Average waiting time for RR "
         << RR << endl;

    /*
    Find the process scheduling algorithm with minimum average waiting time
    */
    Scheduling scheduling[] = {{"FCFS", FCFS}, {"PRIOR", PRIOR}, {"SJF", SJF}, {"RR", RR}};
    int m = sizeof scheduling / sizeof scheduling[0];
    sort(scheduling, scheduling + m, sorfAvgWait); //sort in order of averageWaitTime
    cout << "Thus, the " << scheduling[0].type
         << " policy results the minimum average waiting time." << endl;
    return 0;
}
