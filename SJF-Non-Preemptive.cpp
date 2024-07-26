#include <bits/stdc++.h>
using namespace std;

int main()
{

    int n; 
    cout << "Enter The no of Processes.:" << endl;
    cin >> n;

    //  custom datatype
    vector<pair<string, pair<int, int>>> userInput;

    // Taking Input from User
    for (int i = 0; i < n; i++)
    {
        string str;
        int at, bt;

        cout << "Enter the process name, arrival time and burst time respectively: ";
        cin >> str >> at >> bt;
        cout << endl;

        userInput.push_back({str, {at, bt}});
    }
    int j = -1;
    int a = INT_MAX;
    for (int i = 0; i < userInput.size(); i++)
    {
        if (userInput[i].second.first < a)
        {
            j = i;
            a = userInput[i].second.first;
        }
    }

    int currTime = userInput[j].second.first; //will act as gantt chart time completion

    vector<int> completionTime(userInput.size(), -1);

    currTime += userInput[j].second.second;
    completionTime[j] = currTime + userInput[j].second.second;

    int p = n - 1; //first process completed already

    int b = -1;

    while (p > 0)
    {
        int k = INT_MAX;
        for (int i = 0; i < userInput.size(); i++)
        {
            if (userInput[i].second.first <= currTime && completionTime[i] == -1)
            {
                if (userInput[i].second.second < k)
                {
                    b = i;
                    k = userInput[i].second.second;
                }
            }
        }
        //test this edge case
        if (b != -1)
        {
            currTime += userInput[b].second.second;
            completionTime[b] = currTime;
            p--;
        }
        else //this may be true when no process has arrived till the current completion time
        {
            currTime++;
        }
    }
    cout << endl;

    // Calculating Turn around time

    vector<int> tat;
    tat.resize(userInput.size());

    for (int i = 0; i < userInput.size(); i++)
    {
        tat[i] = completionTime[i] - userInput[i].second.first;
    }

    // Calculating Waiting Time

    vector<int> waitingTime;
    waitingTime.resize(userInput.size());

    for (int i = 0; i < userInput.size(); i++)
    {
        waitingTime[i] = tat[i] - userInput[i].second.second;
    }

    cout << endl;

    // Display process times
    cout << "Process ID\tArrival Time\tBurst Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << userInput[i].first << "\t\t" << userInput[i].second.first << "\t\t" << userInput[i].second.second << endl;
    }
    cout << endl;
    cout << "Completion Time\tTurnaround Time\tWaiting Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << completionTime[i] << "\t\t" << tat[i] << "\t\t" << waitingTime[i] << endl;
    }

    // print average for waiting time and completion time

    float ct_avg = accumulate(completionTime.begin(), completionTime.end(), 0.0 / completionTime.size()) / completionTime.size();

    double avg = 0;

    for (int i = 0; i < waitingTime.size(); i++)
    {
        avg += waitingTime[i];
    }

    avg /= waitingTime.size();

    cout << endl;
    cout << "The average of completion time: " << ct_avg << endl;
    cout << "The average of waiting time: " << avg;

    return 0;
}