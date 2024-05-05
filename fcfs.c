#include <stdio.h> 
#include <stdlib.h> 
 
int main() { 
    int n; 
    printf("Enter no. of processes : "); 
    scanf("%d", &n); 
     
    int *at = (int *)malloc(n * sizeof(int)); 
    int *bt = (int *)malloc(n * sizeof(int)); 
    int *ct = (int *)malloc(n * sizeof(int)); 
    int *wt = (int *)malloc(n * sizeof(int)); 
    int *tat = (int *)malloc(n * sizeof(int)); 
 
    printf("Enter arrival and burst times of the processes:\n"); 
    for (int i = 0; i < n; i++) { 
        scanf("%d%d", &at[i], &bt[i]); 
    } 
 
    int total_tat = 0; 
    int t = at[0]; 
    for (int i = 0; i < n; i++) { 
        t += bt[i]; 
        ct[i] = t; 
        tat[i] = ct[i] - at[i]; 
        total_tat += tat[i]; 
        wt[i] = ct[i] - bt[i]; 
    } 
 
    printf("    AT    BT    CT    TAT    WT\n"); 
    for (int i = 0; i < n; i++) { 
        printf("%6d%6d%6d%7d%6d\n", at[i], bt[i], ct[i], tat[i], wt[i]); 
    } 
 
    printf("Average TAT = %.2f\n", (float)total_tat / n); 
 
    free(at); 
    free(bt); 
    free(ct); 
    free(wt); 
    free(tat); 
 
    return 0; 
}