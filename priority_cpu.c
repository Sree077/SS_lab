// Priority scheduling assuming that arrival time is 0.

#include <stdio.h>

int main() {
    int n, i, j, pos, temp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int p[n], bt[n], priority[n], wt[n], tat[n], ct[n];

    for (i = 0; i < n; i++) {
        p[i] = i + 1; // Process numbers
    }

    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    printf("Enter priorities (lower number = higher priority):\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    // Sort processes based on priority
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (priority[j] < priority[pos]) {
                pos = j;
            }
        }

        // Swap priority
        temp = priority[i];
        priority[i] = priority[pos];
        priority[pos] = temp;

        // Swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap process numbers
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Calculate completion time
    ct[0] = bt[0]; // First process finishes after its burst time
    for (i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + bt[i];
    }

    // Calculate turnaround time and waiting time
    for (i = 0; i < n; i++) {
        tat[i] = ct[i]; // Turnaround time = completion time (arrival time = 0)
        wt[i] = tat[i] - bt[i]; // Waiting time = turnaround time - burst time
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nProcess\tPriority\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], priority[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
