#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[],int at[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = at[i-1]+ wt[i - 1]+bt[i - 1] -at[i];
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[],int at[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = wt[i]+bt[i];
}

void findAvgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt,at);
    findTurnAroundTime(processes, n, bt, wt,at, tat);

    printf("Processes\tArrival time\tBurst time\tWaiting time\tTurnaround time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i],bt[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turnaround time = %.2f\n", (float)total_tat / n);
}

int main() {
    int processes[] = {1, 2, 3,4,5};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {2,1,3,5,4};
    int arrival_time[] = {0,1,2,3,4};

    findAvgTime(processes, n, burst_time, arrival_time);
    return 0;
}
