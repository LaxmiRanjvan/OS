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

void priorityScheduling(int n, int at[], int bt[], int priority[]) {
    int ct[n], tat[n], wt[n], rt[n];
    float rd[n];
    int completionTime = 0;

    for (int i = 0; i < n; i++) {
        int highestPriority = -1;
        int highestPriorityIndex = -1;

        // Find the highest priority process that has arrived
        for (int j = 0; j < n; j++) {
            if (at[j] <= completionTime && priority[j] != -1) {
                if (highestPriority == -1 || priority[j] < highestPriority) {
                    highestPriority = priority[j];
                    highestPriorityIndex = j;
                }
            }
        }

        if (highestPriorityIndex == -1) {
            // No process available, move to the next arrival time
            completionTime = at[i];
            i--;
            continue;
        }

        // Execute the highest priority process
        ct[highestPriorityIndex] = completionTime + bt[highestPriorityIndex];
        tat[highestPriorityIndex] = ct[highestPriorityIndex] - at[highestPriorityIndex];
        wt[highestPriorityIndex] = tat[highestPriorityIndex] - bt[highestPriorityIndex];
        rt[highestPriorityIndex] = wt[highestPriorityIndex];
        rd[highestPriorityIndex] = (float)tat[highestPriorityIndex] / bt[highestPriorityIndex];

        // Mark this process as completed
        priority[highestPriorityIndex] = -1;

        // Update completion time
        completionTime = ct[highestPriorityIndex];
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
    int arrivalTime[n], burstTime[n], priority[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time for process P%d: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Enter the burst time for process P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
        printf("Enter the priority for process P%d: ", i + 1);
        scanf("%d", &priority[i]);
    }
    priorityScheduling(n, arrivalTime, burstTime, priority);
    return 0;
}
/*   p
0 5  3
1 4  2
4 5  4 
2 1  1
*/