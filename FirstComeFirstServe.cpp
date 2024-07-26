#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

struct Process {
    string processID;
    int arrivalTime;
    int burstTime;
    int completionTime = -1;
    int turnAroundTime = -1;
    int waitingTime = -1;
};

int main() {
    int numProcesses;

    // Input the number of processes
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    // Input validation
    if (numProcesses <= 0) {
        cerr << "Invalid number of processes." << endl;
        return 1;
    }

    vector<Process> processes(numProcesses);

    // Input the process details
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Enter the Process-ID, Arrival Time, and Burst Time separated by spaces: ";
        cin >> processes[i].processID >> processes[i].arrivalTime >> processes[i].burstTime;

        if (processes[i].arrivalTime < 0 || processes[i].burstTime <= 0) {
            cerr << "Invalid Arrival Time or Burst Time." << endl;
            return 1;
        }

        cout << endl;
    }

    // Sort processes based on Arrival Time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // Display sorted processes
    cout << "User input after sorting:" << endl;
    cout << "Process    AT    BT" << endl;
    for (const auto &process : processes) {
        cout << process.processID << "        " << process.arrivalTime << "        " << process.burstTime << endl;
    }

    // Calculate Completion Time (CT), Turn Around Time (TAT), and Waiting Time (WT)
    int currentTime = 0;

    for (int i = 0; i < numProcesses; ++i) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime; // Processor is idle until the next process arrives
        }

        currentTime += processes[i].burstTime;
        processes[i].completionTime = currentTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
    }

    cout << "Process    CT    TAT    WT" << endl;
    for (const auto &process : processes) {
        cout << process.processID << "        " << process.completionTime << "        " << process.turnAroundTime << "        " << process.waitingTime << endl;
    }

    double averageWT = accumulate(processes.begin(), processes.end(), 0.0, [](double sum, const Process &p) {
        return sum + p.waitingTime;
    }) / numProcesses;

    double averageCT = accumulate(processes.begin(), processes.end(), 0.0, [](double sum, const Process &p) {
        return sum + p.completionTime;
    }) / numProcesses;

    cout << "Average waiting time is: " << averageWT << endl;
    cout << "Average completion time is: " << averageCT << endl;

    return 0;
}
