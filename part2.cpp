#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <thread>
using namespace std;

void threadFunc(int x);

ofstream outputFile;
struct Process
{
   int id;  // process ID
   int bt;    // process burst time
   int pr;    // process priority level
};

class FCFS {    //First-Come-First-Serve Scheduling
public:
  void findAvgTime(Process processes[], int n) {
    int wt[n] = {};
    int total_wt = 0;

    calcWaitingTime(processes, n, wt);

    for (int i = 0; i < n; i++)
      total_wt = total_wt + wt[i];

    int avgTime = total_wt/n;

    // return avgTime;

    cout << "Average wait time for FCFS " << avgTime << endl;
  }
  void calcWaitingTime(Process processes[], int n, int wt[]) {
    wt[0] = 0;

    for (int i = 1; i < n; i++)
      wt[i] = processes[i-1].bt + wt[i-1];
  }
 // void threadFunc(int x) {
 //   //ofstream outputFile;
 //   outputFile.open("output.txt");
 //   outputFile << "Average wait time for FCFS " << x << endl;
 //   //outputFile.close();
 // }
};


class SJF { //Shortest Job First Scheduling
public:
  void findAvgTime(Process processes[], int n) {
    int wt[n] = {};
    int total_wt = 0;

    calcWaitingTime(processes, n, wt);

    for (int i = 0; i < n; i++)
      total_wt = total_wt + wt[i];

    int avgTime = total_wt/n;

    // return avgTime;
    cout << "Average wait time for SJF " << avgTime << endl;
  }
  void calcWaitingTime(Process processes[], int n, int wt[]) {
    wt[0] = 0;

    for (int i = 1; i < n; i++)
      wt[i] = processes[i-1].bt + wt[i-1];
    }


};
  // void threadFunc(int x) {
  //   //ofstream outputFile;
  //   outputFile.open("output.txt");
  //   outputFile << "Average wait time for FCFS " << x << endl;
  //   //outputFile.close();
  // }


class RR {  //Round Robin Scheduling
public:
  void findAvgTime(Process processes[], int n, int quantum) {
    int wt[n] = {};
    int total_wt = 0;

    calcWaitingTime(processes, n, wt, quantum);

    for (int i = 0; i < n; i++)
      total_wt = total_wt + wt[i];

      int avgTime = total_wt/n;

      //return avgTime;
      cout << "Average wait time for RR " << avgTime << endl;
  }
  void calcWaitingTime(Process processes[], int n, int wt[], int quantum) {
    int rem_bt[n] = {};

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
  // void threadFunc(int x) {
  //   //ofstream outputFile;
  //   outputFile.open("output.txt");
  //   outputFile << "Average wait time for RR " << x << endl;
  //   //outputFile.close();
  // }
};


class Priority {  //Priority Scheduling
public:
  void findAvgTime(Process processes[], int n) {
    int wt[n] = {};
    int total_wt = 0;

    calcWaitingTime(processes, n, wt);

    for (int i = 0; i < n; i++)
      total_wt = total_wt + wt[i];

      int avgTime = total_wt/n;

      //return avgTime;
      cout << "Average wait time for Priority " << avgTime << endl;
  }
  void calcWaitingTime(Process processes[], int n, int wt[]) {
    wt[0] = 0;

    for(int i = 1; i < n; i++)
      wt[i] = processes[i-1].bt + wt[i-1];
  }

};


int main() {
  Process processes[] = {{1,-1,-1},{2, -1, -1}, {3, -1, -1}};
  int n = sizeof(processes)/ sizeof(processes[0]);
  int quantum = 5;
  int btSorted[3] = {};
  int prSorted[3] = {};

  FCFS f1;
  SJF s2;
  RR r3;
  Priority p4;


  for(int i = 0; i < 3; i++) {
    btSorted[i] = rand() % 10 + 1;
    prSorted[i] = rand() % 3 + 1;
  }

 //btSorted and prSorted are not sorted at this point yet
  for(int i = 0; i < 3; i++) {
    processes[i].bt = btSorted[i];
    processes[i].pr = prSorted[i];
  }
  // int one = f1.findAvgTime(processes, n, burstTime);
  // sort(burstTime, burstTime + n);
  // int two = s2.findAvgTime(processes, n, burstTime);
  // int three = r3.findAvgTime(processes, n, burstTime, quantum);

  //FCFS Scheduling
  f1.findAvgTime(processes, n);

  //SJF Scheduling
  sort(btSorted, btSorted + n);
  for(int i = 0; i < 3; i++) {
    processes[i].bt = btSorted[i];
  }
  s2.findAvgTime(processes, n);

  //RR Scheduling
  r3.findAvgTime(processes, n, quantum);

  //Priority Scheduling
  sort(prSorted, prSorted + n);
  for(int i = 0; i < 3; i++) {
    processes[i].bt = btSorted[i];
    processes[i].pr = prSorted[i];
  }
  p4.findAvgTime(processes, n);

 // std::thread th1(&FCFS::threadFunc, &f1, one);
 // //std::thread th1(&threadFunc, &f1, one);
 // //th1.join();
 // std::thread th2(&SJF::threadFunc, &s2, two);
 // std::thread th3(&RR::threadFunc, &s2, three);
 // th1.join();
 // th2.join();
 // th3.join();



  return 0;
}
// void threadFunc(int x) {
//   ofstream outputFile;
//   outputFile.open("output.txt");
//   outputFile << "Average wait time for FCFS " << x << endl;
//   outputFile << "Average wait time for SJF " << x << endl;
//   outputFile.close();
// }
