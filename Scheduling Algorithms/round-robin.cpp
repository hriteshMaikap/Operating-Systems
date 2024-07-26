#include <bits/stdc++.h>
using namespace std;

struct processes {
    string processId;
    int at;  
    int bt;  
    int ct;  
    int tat; 
    int wt;  
    int original_bt; 

    processes() : ct(-1), tat(-1), wt(-1) {}
};

int main() {
    int numProcess;
    int timeQuantum = 2;

    cout << "Enter the number of processes: ";
    cin >> numProcess;
    vector<processes> procArray(numProcess);

    // User input
    for (int i = 0; i < numProcess; i++) {
        cout << "Enter the process-id, arrival time, burst time all separated by spaces: ";
        cin >> procArray[i].processId >> procArray[i].at >> procArray[i].bt;
        procArray[i].original_bt = procArray[i].bt; // Store the original burst time
        cout << endl;
    }

    // Sort on the basis of arrival time
    sort(procArray.begin(), procArray.end(), [](const auto &a, const auto &b) {
        return a.at < b.at;
    });

    int curTime = 0;
    int completedProcess = 0;
    queue<int> readyQueue;
    set<int> inQueue; // Track indices of processes in the queue

    // Initialize the ready queue with processes that have arrived at the initial time
    for (int i = 0; i < numProcess; i++) {
        if (procArray[i].at <= curTime) {
            readyQueue.push(i);
            inQueue.insert(i);
        }
    }

    while (completedProcess < numProcess) {
        if (readyQueue.empty()) {
            curTime++;
            // Add processes to the ready queue that have arrived by current time
            for (int i = 0; i < numProcess; i++) {
                if (procArray[i].at == curTime && inQueue.find(i) == inQueue.end()) {
                    readyQueue.push(i);
                    inQueue.insert(i);
                }
            }
        } else {
            int idx = readyQueue.front();
            readyQueue.pop();
            inQueue.erase(idx);
            processes &curProcess = procArray[idx];

            if (curProcess.bt <= timeQuantum) {
                curTime += curProcess.bt;
                curProcess.bt = 0;
                curProcess.ct = curTime;
                completedProcess++;
            } else {
                curProcess.bt -= timeQuantum;
                curTime += timeQuantum;
            }

            // Add newly arrived processes to the ready queue
            for (int i = 0; i < numProcess; i++) {
                if (procArray[i].at > curProcess.at && procArray[i].at <= curTime && inQueue.find(i) == inQueue.end() && procArray[i].bt > 0) {
                    readyQueue.push(i);
                    inQueue.insert(i);
                }
            }

            // If the process is not yet completed, re-add it to the ready queue
            if (curProcess.bt > 0) {
                readyQueue.push(idx);
                inQueue.insert(idx);
            }
        }
    }

    for (int i = 0; i < numProcess; i++) {
        procArray[i].tat = procArray[i].ct - procArray[i].at;
        procArray[i].wt = procArray[i].tat - procArray[i].original_bt;
    }

    // Printing the output
    cout << "P-id" << "\t" << "AT" << "\t" << "BT" << "\t" << "CT" << "\t" << "TAT" << "\t" << "WT" << endl;
    for (int i = 0; i < numProcess; i++) {
        cout << procArray[i].processId << "\t" << procArray[i].at << "\t" << procArray[i].original_bt << "\t" << procArray[i].ct << "\t" << procArray[i].tat << "\t" << procArray[i].wt << endl;
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
