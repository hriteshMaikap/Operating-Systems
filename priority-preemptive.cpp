#include <bits/stdc++.h>
using namespace std;

typedef struct {
    string processId;
    int at;
    int bt;
    int ct = -1;
    int tat = -1;
    int wt = -1;
    int priority;
} processes;

int main() {
    int numProcess;
    cout << "Enter the number of processes: ";
    cin >> numProcess;
    vector<processes> procArray(numProcess);

    // User input
    for (int i = 0; i < numProcess; i++) {
        cout << "Enter the process-id, arrival time, burst time and priority all separated by spaces: ";
        cin >> procArray[i].processId >> procArray[i].at >> procArray[i].bt >> procArray[i].priority;
        cout << endl;
    }

    // Sort on the basis of arrival time
    sort(procArray.begin(), procArray.end(), [](const auto &a, const auto &b) {
        return a.at < b.at;
    });

    int curTime = procArray[0].at;
    int processArrived = 1; // Initially only the first process has arrived
    int p = numProcess;

    // Initial phase: Execute each process for 1 second based on priority until all processes have arrived
    while (processArrived < numProcess) {
        int curProcessIndex = -1;
        int curPriority = INT_MAX;

        for (int i = 0; i < numProcess; i++) {
            if (procArray[i].at <= curTime && procArray[i].priority != -1 && procArray[i].ct == -1) {
                if (procArray[i].priority < curPriority) {
                    curPriority = procArray[i].priority;
                    curProcessIndex = i;
                }
            }
        }

        if (curProcessIndex == -1) { // No process has arrived yet
            curTime++;
        } else {
            // Execute the process for 1 second
            curTime += 1;
            procArray[curProcessIndex].bt -= 1;

            if (procArray[curProcessIndex].bt == 0) {
                procArray[curProcessIndex].ct = curTime;
                procArray[curProcessIndex].priority = -1;
                p--;
            }

            // Check if new processes have arrived
            for (int i = processArrived; i < numProcess; i++) {
                if (procArray[i].at <= curTime) {
                    processArrived++;
                }
            }
        }
    }

    // Normal scheduling phase
    while (p > 0) {
        int curProcessIndex = -1;
        int curPriority = INT_MAX;

        for (int i = 0; i < numProcess; i++) {
            if (procArray[i].at <= curTime && procArray[i].priority != -1 && procArray[i].ct == -1) {
                if (procArray[i].priority < curPriority) {
                    curPriority = procArray[i].priority;
                    curProcessIndex = i;
                }
            }
        }

        if (curProcessIndex == -1) { // No process has arrived yet
            curTime++;
        } else {
            // Execute the process to completion
            curTime += procArray[curProcessIndex].bt;
            procArray[curProcessIndex].ct = curTime;
            procArray[curProcessIndex].priority = -1;
            p--;
        }
    }

    // Printing the output
    cout << "P-id" << "      " << "CT" << endl;
    for (int i = 0; i < numProcess; i++) {
        cout << procArray[i].processId << "     " << procArray[i].ct << endl;
    }

    return 0;
}
