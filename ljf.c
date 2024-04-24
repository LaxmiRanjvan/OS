#include <stdio.h>

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

void ljfScheduling(int n, int at[], int bt[]) {
    int ct[n], tat[n], wt[n], rt[n];
    float rd[n];

    int completed[n];
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    int currentTime = 0;  

    while (1) {
        int maxBurst = -1, longest = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && completed[i] == 0 && bt[i] > maxBurst) {
                maxBurst = bt[i];
                longest = i;
            }
        }

        if (longest == -1) {
            break;
        }

        currentTime += bt[longest];
        ct[longest] = currentTime;
        tat[longest] = ct[longest] - at[longest];
        wt[longest] = tat[longest] - bt[longest];
        rt[longest] = wt[longest];
        rd[longest] = (float) tat[longest] / bt[longest];

        completed[longest] = 1;
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

    ljfScheduling(n, arrivalTime, burstTime);

    return 0;
}
