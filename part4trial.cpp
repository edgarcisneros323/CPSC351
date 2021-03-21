#include <stdio.h>
#include <pthread.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <sstream>
using namespace std;

vector<string> inputStrings;
int numOfThreads = 0;
int threadFound = 0;
int subStringNum =0;
int threadNum = 0;
string key;
int found = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* ThreadSearch(void* args) {
   pthread_mutex_lock(&mutex);
   int num = threadNum++;
   for (int i = num * ( inputStrings.size()/ numOfThreads); i < ((num + 1) * (inputStrings.size() / numOfThreads)); i++){
      if (inputStrings[i] == key){
        subStringNum++;
        found = 1;
      }
   }
   if(found == 1){
     threadFound++;
   }
   pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) {

  if (argc != 4) {
    cout << "There are not enough arguments to continue";
    exit(-1);
  }
  else{
    ifstream infile(argv[1]);
    if(infile.fail()){
      cout << argv[1] << " not found." << endl;
      exit(1);
    }
    string inputLine;
    string eachString;
    while (getline(infile,inputLine)){
      stringstream ss(inputLine);
      while (getline(ss,eachString, ',')){
        inputStrings.push_back(eachString);
      }
    }
    key = argv[2];
    numOfThreads = stoi(argv[3]);
    found = 0;

    pthread_t thread[numOfThreads];
    for (int i = 0; i < numOfThreads; i++) {
      if(pthread_create(&thread[i], NULL, ThreadSearch, NULL) < 0){
       perror("pthread_create");
       exit(-1);
     }
    }
    for (int i = 0; i < numOfThreads; i++) {
       pthread_join(thread[i], NULL);
    }
    cout << "The " << key << "string has been found by "
      << threadFound << "threads, there are " << subStringNum << "occurrences for the sub-string." << endl;
  }

  return 0;
}
