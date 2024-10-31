#include <stdio.h>
int main(){
    int i, n, j, pos, temp;
    float avg_wt = 0, avg_tat = 0;
    printf("Enter no of process: ");
    scanf("%d", &n);

    int bt[n], wt[n], p[n], tat[n];

    printf("Enter burst time for each process: \n");
    for(i=0; i<n; i++){
        printf("p%d: ", i+1);
        scanf("%d", &bt[i]);
        p[i] = i+1;
    }

    for(i=0; i<n; i++){
        pos = i;
        for(j=i+1; j<n; j++){
            if(bt[j]< bt[pos]){
                pos = j;
            }
        }

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;

    }

    wt[0] = 0;
    for (i=1; i<n; i++){
        wt[i] = wt[i-1] + bt[i-1];
        avg_wt += wt[i];
    }

    for(i=0; i<n; i++){
        tat[i] = wt[i] + bt[i];
        avg_tat += tat[i];
    }
    avg_tat /= n;
    avg_wt /= n;
    printf("Process\tburst time\tTAT\t waiting time\n");
    for(i=0; i<n; i++){
        printf("p%d\t%d\t\t%d\t\t%d\n", p[i], bt[i], tat[i], wt[i]);
    }
    printf("Average waiting time is: %.2f\n", avg_wt);
    printf("Average turn around time is: %.2f\n", avg_tat);

    return 0;
}