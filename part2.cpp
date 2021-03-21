#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <thread>
using namespace std;

int sharedVar = 0;
int randomNumberOfProcesses = rand() % 4 + 1;
int one, two, three, four;
ofstream outputFile;


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

//sorts all algorithms by fastest one first
bool sorfAvgWait(Scheduling firstS, Scheduling secondS)
{
   return (firstS.avgWaitTime < secondS.avgWaitTime);
}

//sorts by shortest burst time
bool burstTime(Process firstP, Process secondP)
{
   return (firstP.bt < secondP.bt);
}

//sorts by highest priority
bool priority(Process firstP, Process secondP)
{
   return (firstP.pr > secondP.pr);
}

//First-Come-First-Serve Scheduling
class FCFS {
public:
 int findAvgTime(Process processes[], int n) {
   int wt[n] = {};
   int total_wt = 0;

   calcWaitingTime(processes, n, wt);

   for (int i = 0; i < n; i++)
     total_wt = total_wt + wt[i];

   int avgTime = total_wt/n;

   return avgTime;

 }
 void calcWaitingTime(Process processes[], int n, int wt[]) {
   wt[0] = 0;

   for (int i = 1; i < n; i++)
     wt[i] = processes[i-1].bt + wt[i-1];
 }
};

//Shortest Job First Scheduling
class SJF {
public:
 int findAvgTime(Process processes[], int n) {
   int wt[n] = {};
   int total_wt = 0;

   sort(processes, processes + n, burstTime);
   calcWaitingTime(processes, n, wt);

   for (int i = 0; i < n; i++)
     total_wt = total_wt + wt[i];

   int avgTime = total_wt/n;

   return avgTime;

 }
 void calcWaitingTime(Process processes[], int n, int wt[]) {
   wt[0] = 0;

   for (int i = 1; i < n; i++)
     wt[i] = processes[i-1].bt + wt[i-1];
   }


};

//Round Robin Scheduling
class RR {
public:
 int findAvgTime(Process processes[], int n) {
   int wt[n] = {};
   int total_wt = 0;
   int quantum = 5;

   calcWaitingTime(processes, n, wt);

   for (int i = 0; i < n; i++)
     total_wt = total_wt + wt[i];

     int avgTime = total_wt/n;

     return avgTime;
 }
 void calcWaitingTime(Process processes[], int n, int wt[]) {
   int rem_bt[n] = {};
   int quantum = 5;

   for(int i = 0; i < n; i++)
     rem_bt[i] = processes[i].bt;

   int t = 0;

   while(1) {
     bool done = true;

     for(int i = 0; i < n; i++) {

       if(rem_bt[i] > 0)
       {
           done = false;

           if(rem_bt[i] > quantum)
           {
             t += quantum;
             rem_bt[i] -= quantum;
           }
           else
           {
             t = t + rem_bt[i];

             wt[i] = t - processes[i].bt;

             rem_bt[i] = 0;
           }
        }
     }
       if(done == true)
         break;
 }
}
};

//Priority Scheduling
class Priority {
public:
 int findAvgTime(Process processes[], int n) {
   int wt[n] = {};
   int total_wt = 0;

   sort(processes, processes + n, priority);
   calcWaitingTime(processes, n, wt);

   for (int i = 0; i < n; i++)
     total_wt = total_wt + wt[i];

     int avgTime = total_wt/n;

     return avgTime;
 }
 void calcWaitingTime(Process processes[], int n, int wt[]) {
   wt[0] = 0;

   for(int i = 1; i < n; i++)
     wt[i] = processes[i-1].bt + wt[i-1];
 }

};

void genListOfProcess(Process processes[], int randomNumberOfProcesses) {
   ofstream file;
  file.open ("genListOfProcess.txt", ios::out | ios::trunc);
  string processID;
  int bust_time = 0;
  int priority_level = 0;

  for (int i = 0; i < randomNumberOfProcesses; i++){
    processID = "P" + to_string(i+1);
    bust_time = rand() % 50 + 1;
    priority_level = rand() % 4 + 1;
    processes[i] = {processID, bust_time, priority_level};
    file << processID << ", " << bust_time
         << ", " << priority_level << endl;
  }
  file.close();
}


void* threadFunc(void* arg)
{
 Process processes[randomNumberOfProcesses];
 genListOfProcess(processes, randomNumberOfProcesses);
 int n = sizeof(processes)/ sizeof(processes[0]);
 FCFS f1;
 SJF s2;
 RR r3;
 Priority p4;
 ofstream outputFile;
 outputFile.open("output.txt", std::ios_base::app);


 /* Increment the variable */
 if(sharedVar == 0) {
   one = f1.findAvgTime(processes, n);
   outputFile << "Average wait time for FCFS " << one << endl;
 }
 else if(sharedVar == 1) {
   two = s2.findAvgTime(processes, n);
   outputFile << "Average wait time for SJF " << two << endl;
 }
 else if(sharedVar == 2) {
   three = r3.findAvgTime(processes, n);
   outputFile << "Average wait time for RR " << three << endl;
 }
 else {
   four = p4.findAvgTime(processes, n);
   outputFile << "Average wait time for Priority " << four << endl;
 }
 outputFile.close();
 ++sharedVar;
}


int main() {

 pthread_t processThreads[randomNumberOfProcesses];

      for(int threadId = 0; threadId != randomNumberOfProcesses; ++threadId)
     {
       /* Create a thread */
       if(pthread_create(&processThreads[threadId], NULL, threadFunc, NULL) != 0)
       {
         perror("pthread_create");
         exit(-1);
       }
     }

     for(int threadId = 0; threadId != randomNumberOfProcesses; ++threadId)
 {
   /* Create a thread */
   if(pthread_join(processThreads[threadId], NULL) != 0)
   {
     perror("pthread_create");
     exit(-1);
   }
 }
 outputFile.open("output.txt", std::ios_base::app);

 Scheduling scheduling[] = {{"FCFS", one}, {"PRIOR", four}, {"SJF", two}, {"RR", three}};
 int m = sizeof scheduling / sizeof scheduling[0];
 sort(scheduling, scheduling + m, sorfAvgWait); //sort in order of averageWaitTime
 outputFile << "Thus, the " << scheduling[0].type
      << " policy results the minimum average waiting time." << endl;


 outputFile.close();
 fprintf(stderr, "sharedVar = %d\n", sharedVar);

 return 0;
}
