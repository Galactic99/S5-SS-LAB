#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

void sortProcesses(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority ||
                (processes[j].priority == processes[j + 1].priority && processes[j].arrival_time > processes[j + 1].arrival_time)) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process processes[], int n) {
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void calculateAvgTimes(struct Process processes[], int n) {
    float avg_wt = 0, avg_tat = 0;
    printf("PID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        avg_wt += processes[i].waiting_time;
        avg_tat += processes[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average waiting time = %.2f\n", avg_wt / n);
    printf("Average turnaround time = %.2f\n", avg_tat / n);
}

int main() {
    struct Process processes[] = {
        {1, 0, 8, 2},
        {2, 1, 1, 1},
        {3, 2, 3, 3},
        {4, 3, 2, 4},
        {5, 4, 6, 5}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    sortProcesses(processes, n);
    calculateTimes(processes, n);
    calculateAvgTimes(processes, n);

    return 0;
}
