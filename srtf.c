#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
 
struct Process { 
    int pid; // Process ID 
    int bt; // Burst Time 
    int art; // Arrival Time 
}; 
 
void findWaitingTime(struct Process proc[], int n, int wt[]) { 
    int rt[n]; 
    for (int i = 0; i < n; i++) 
        rt[i] = proc[i].bt; 
 
    int complete = 0, t = 0, minm = INT_MAX; 
    int shortest = 0, finish_time; 
    int check = 0; 
 
    while (complete != n) { 
        for (int j = 0; j < n; j++) { 
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) { 
                minm = rt[j]; 
                shortest = j; 
                check = 1; 
            } 
        } 
 
        if (check == 0) { 
            t++; 
            continue; 
        } 
 
        rt[shortest]--; 
        minm = rt[shortest]; 
        if (minm == 0) 
            minm = INT_MAX; 
 
        if (rt[shortest] == 0) { 
            complete++; 
            check = 0; 
            finish_time = t + 1; 
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art; 
            if (wt[shortest] < 0) 
                wt[shortest] = 0; 
        } 
        t++; 
    } 
} 
 
void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) { 
    for (int i = 0; i < n; i++) 
        tat[i] = proc[i].bt + wt[i]; 
} 
 
void findavgTime(struct Process proc[], int n) { 
    int *wt = (int *)malloc(n * sizeof(int)); 
    int *tat = (int *)malloc(n * sizeof(int)); 
    int total_wt = 0, total_tat = 0; 
 
    findWaitingTime(proc, n, wt); 
    findTurnAroundTime(proc, n, wt, tat); 
 
    printf(" P\t\tBT\t\tWT\t\tTAT\t\t\n"); 
    for (int i = 0; i < n; i++) { 
        total_wt += wt[i]; 
        total_tat += tat[i]; 
        printf(" %d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, wt[i], tat[i]); 
    } 
 
    printf("\nAverage waiting time = %.2f\n", (float)total_wt / (float)n); 
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n); 
 
    free(wt); 
    free(tat); 
} 
 
int main() { 
    int n; 
    printf("Enter the number of processes: "); 
    scanf("%d", &n); 
 
    struct Process *proc = (struct Process *)malloc(n * sizeof(struct Process)); 
    printf("Enter arrival time and burst time for each process:\n"); 
    for (int i = 0; i < n; i++) { 
        printf("Process %d: ", i + 1); 
        scanf("%d %d", &proc[i].art, &proc[i].bt); 
        proc[i].pid = i + 1; 
    } 
 
    findavgTime(proc, n); 
 
    free(proc); 
 
    return 0; 
}