#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

// Custom type for process information
using ProcessInfo = pair<string, pair<int, int>>; // {Process-ID, {Arrival Time, Burst Time}}

int main() {
    vector<ProcessInfo> processes;
    int numProcesses;

    // Input the number of processes
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    // Input validation
    if (numProcesses <= 0) {
        cerr << "Invalid number of processes." << endl;
        return 1;
    }

    // Input the process details
    for (int i = 0; i < numProcesses; ++i) {
        string processID;
        int arrivalTime, burstTime;
        cout << "Enter the Process-ID, Arrival Time, and Burst Time separated by spaces: ";
        cin >> processID >> arrivalTime >> burstTime;

        if (arrivalTime < 0 || burstTime <= 0) {
            cerr << "Invalid Arrival Time or Burst Time." << endl;
            return 1;
        }

        processes.emplace_back(processID, make_pair(arrivalTime, burstTime));
        cout << endl;
    }

    // Sort processes based on Arrival Time
    sort(processes.begin(), processes.end(), [](const ProcessInfo &a, const ProcessInfo &b) {
        return a.second.first < b.second.first;
    });

    // Display sorted processes
    cout << "User input after sorting:" << endl;
    cout << "Process    AT    BT" << endl;
    for (const auto &process : processes) {
        cout << process.first << "        " << process.second.first << "        " << process.second.second << endl;
    }

    // Calculate Completion Time (CT), Turn Around Time (TAT), and Waiting Time (WT)
    vector<int> completionTime(numProcesses);
    vector<int> turnAroundTime(numProcesses);
    vector<int> waitingTime(numProcesses);
    int currentTime = 0;

    for (int i = 0; i < numProcesses; ++i) {
        currentTime = max(currentTime, processes[i].second.first) + processes[i].second.second;
        completionTime[i] = currentTime;
        turnAroundTime[i] = completionTime[i] - processes[i].second.first;
        waitingTime[i] = turnAroundTime[i] - processes[i].second.second;
    }

    // Print the results
    cout << "CT    TAT    WT" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        cout << completionTime[i] << "    " << turnAroundTime[i] << "    " << waitingTime[i] << endl;
    }

    // Calculate and print the average waiting time and completion time
    double averageWT = accumulate(waitingTime.begin(), waitingTime.end(), 0.0) / numProcesses;
    double averageCT = accumulate(completionTime.begin(), completionTime.end(), 0.0) / numProcesses;

    cout << "Average waiting time is: " << averageWT << endl;
    cout << "Average completion time is: " << averageCT << endl;

    return 0;
}
