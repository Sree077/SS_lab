#include <stdio.h>

int main() {
    int n, i, j, pos, temp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], wt[n], tat[n], ct[n], p[n];

    for (i = 0; i < n; i++) {
        p[i] = i + 1; // Store process numbers
    }

    printf("Enter arrival times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &at[i]);
    }

    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Sort processes by burst time (SJF)
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos]) {
                pos = j;
            }
        }

        // Swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap arrival time
        temp = at[i];
        at[i] = at[pos];
        at[pos] = temp;

        // Swap process numbers
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Calculate completion time
    ct[0] = at[0] + bt[0]; // First process completion time
    for (i = 1; i < n; i++) {
        if (ct[i - 1] > at[i]) {
            ct[i] = ct[i - 1] + bt[i];
        } else {
            ct[i] = at[i] + bt[i];
        }
    }

    // Calculate turnaround time and waiting time
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i]; // Turnaround time = completion time - arrival time
        wt[i] = tat[i] - bt[i]; // Waiting time = turnaround time - burst time
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
