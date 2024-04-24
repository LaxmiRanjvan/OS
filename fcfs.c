#include<stdio.h>
void calculateAverages(int n, int ct[], int tat[], int wt[], int rt[], float rd[]) {
    float avgTAT = 0, avgWT = 0, avgRT = 0, avgRD = 0;

    for (int i = 0; i < n; i++) {
        avgTAT += tat[i];
        avgWT += wt[i];
        avgRT += rt[i];
        avgRD += rd[i];
    }
    avgTAT /= n;
    avgWT /= n;
    avgRT /= n;
    avgRD /= n;
    printf("\nAverage Turnaround Time: %.2f", avgTAT);
    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Response Time: %.2f", avgRT);
    printf("\nAverage Response Delay: %.2f", avgRD);
}
void fcfsScheduling(int n, int at[], int bt[]) {
    int ct[n], tat[n], wt[n], rt[n];
    float rd[n];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
            }
        }
    }
    ct[0] = at[0] + bt[0];
    tat[0] = ct[0] - at[0];
    wt[0] = tat[0] - bt[0];
    rt[0] = wt[0];
    rd[0] = (float) tat[0] / bt[0];
    for (int i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];
        rd[i] = (float) tat[i] / bt[i];
    }
    printf("\nP. no.\tAT\tBT\tCT\tTAT\tWT\tRT\tRD");
    for (int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%.2f", i + 1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i], rd[i]);
    }
    calculateAverages(n, ct, tat, wt, rt, rd);
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int arrivalTime[n], burstTime[n];
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time for process P%d: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Enter the burst time for process P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }
    fcfsScheduling(n, arrivalTime, burstTime);
    return 0;
}
/* 
1 3
1 2
2 4
4 4*/