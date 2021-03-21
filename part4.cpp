//Part 4 Edgar Cisneros
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

string wordArr[8] = {""};
string searchArr[4][2] = {{"",""},{"",""},{"",""},{"",""}};


void* threadSearch(void* args){

}


int main(int argc, char const *argv[]) {
  string word;
  ifstream infile;
  infile.open(argv[1]);
  int numOfThreads = atoi(argv[4]);
  pthread_t threads[numOfThreads];

  //int size_word = sizeof(argv[3]) / sizeof(char);
  //string wordCheck = s(argv[3]);

  if (argc < 4) {
    cout << "There are not enough arguments to continue";
    exit(-1);
  }
  int num = 0;
  while (getline(infile,word)){
    wordArr[num] = word;
    num++;
  }
  infile.close();

  int splitnum = 8/numOfThreads;
  for (int i = 0; i < numOfThreads; i+=2) {
    for (int j = 0; i < 2; j++) {
      searchArr[i][j] = wordArr[j];
    }


  }

  for (int threadNum = 0; threadNum < numOfThreads; ++threadNum) {
    if(pthread_create(&threads[threadNum],NULL,threadSearch,NULL)<0)
    {
      perror("pthread_create");
      exit(-1);
    }
  }

  for(int threadNum = 0; threadNum < numOfThreads; ++threadNum){
    pthread_join(threads[threadNum],NULL);
  }
  return 0;
}
