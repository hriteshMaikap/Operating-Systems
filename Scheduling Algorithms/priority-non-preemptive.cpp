#include <bits\stdc++.h>
using namespace std;
typedef struct{
  string processId;
  int at;
  int bt;
  int ct=-1;
  int tat=-1;
  int wt=-1;
  int priority;  
}processes;

int main(){
    int numProcess;
    cout << "Enter the number of processes: ";
    cin >> numProcess;
    vector<processes>procArray(numProcess);
    //user input
    for (int i=0; i<numProcess; i++){
        cout << "Enter the process-id, arrival time, burst time and priority all separated by spaces: ";
        cin >> procArray[i].processId >> procArray[i].at >> procArray[i].bt >> procArray[i].priority;
        cout << endl;
    }
    //sort on the basis of arrival time
    sort(procArray.begin(), procArray.end(), [](const auto &a, const auto &b) {
        return a.at < b.at;
    });
    //set the current time to the first arrival time (minimum arrival time)
    int curTime = procArray[0].at;
    //manually complete the first process
    curTime += procArray[0].bt;
    procArray[0].ct=curTime;
    procArray[0].priority=-1;
    //run a loop 
    int p=numProcess-1;
    while(p>0){
        int curProcessIndex=-1;
        int curPriority= INT_MAX;
        //check which processes have arrived
        for (int i=1; i<numProcess; i++){
            if (procArray[i].at<=curTime && procArray[i].priority!=-1 && procArray[i].ct==-1){
                if (procArray[i].priority<curPriority){
                    curPriority=procArray[i].priority;
                    curProcessIndex=i;
                }
            }
        }
        if(curProcessIndex==-1){ //this means no process has arrived yet
            curTime++;
        }
        else{
            //execute the process
            curTime += procArray[curProcessIndex].bt;
            procArray[curProcessIndex].ct=curTime;
            procArray[curProcessIndex].priority=-1;
            p--;
        }
    }

    //printing the output
    cout << "P-id" <<"      "<<"CT"<<endl;
    for (int i=0; i<numProcess; i++){
        cout << procArray[i].processId << "     "<< procArray[i].ct <<endl;
    }
    return 0;
}