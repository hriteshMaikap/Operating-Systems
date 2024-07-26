#include <bits\stdc++.h>
using namespace std;
typedef struct {
    string processId;
    int at;
    int bt;
    int ct = -1;
    int tat = -1;
    int wt = -1;
    int remaining_bt=0;
} processes;

int main(){
    int numProcess;
    cout << "Enter the number of processes: ";
    cin >> numProcess;
    vector<processes> procArray(numProcess);

    // User input
     for (int i = 0; i < numProcess; i++) {
        cout << "Enter the process-id, arrival time, and burst time separated by spaces: ";
        cin >> procArray[i].processId >> procArray[i].at >> procArray[i].bt;
        procArray[i].remaining_bt = procArray[i].bt; // Initialize remaining burst time
        cout << endl;
    }

    // Sort on the basis of arrival time
    sort(procArray.begin(), procArray.end(), [](const auto &a, const auto &b) {
        return a.at < b.at;
    });

    int curTime = procArray[0].at;
    int completedProcesses = 0;
    vector<bool>inQueue(numProcess, false);

    while(completedProcesses<numProcess){
        int shortestIndex = -1;
        int minBT = INT_MAX;
        for (int i=0; i<numProcess; i++){
            if (procArray[i].at<=curTime && procArray[i].remaining_bt>0){
                if(procArray[i].remaining_bt<minBT){
                    minBT = procArray[i].remaining_bt;
                    shortestIndex = i;
                }
            }
        }

        if (shortestIndex==-1){
            //no process executed
            curTime++;
        }
        else{
            processes &curProcess = procArray[shortestIndex];
            curProcess.remaining_bt--;
            curTime++;

            //check if process completed
            if (curProcess.remaining_bt==0){
                curProcess.ct = curTime;
                curProcess.tat = curProcess.ct-curProcess.at;
                curProcess.wt = curProcess.tat-curProcess.bt;
                completedProcesses++;
            }
        }
    }
    cout << "P-id" << "\t" << "AT" << "\t" << "BT" << "\t" << "CT" << "\t" << "TAT" << "\t" << "WT" << endl;
    for (int i = 0; i < numProcess; i++) {
        cout << procArray[i].processId << "\t" << procArray[i].at << "\t" << procArray[i].bt << "\t" << procArray[i].ct << "\t" << procArray[i].tat << "\t" << procArray[i].wt << endl;
    }

    // Calculate average Waiting Time and Completion Time 
    double averageWT = accumulate(procArray.begin(), procArray.end(), 0.0, [](double sum, const processes &p) {
        return sum + p.wt;
    }) / numProcess;

    double averageCT = accumulate(procArray.begin(), procArray.end(), 0.0, [](double sum, const processes &p) {
        return sum + p.ct;
    }) / numProcess;

    cout << "Average Waiting Time (WT): " << averageWT << endl;
    cout << "Average Completion Time (CT): " << averageCT << endl;

    return 0;
}