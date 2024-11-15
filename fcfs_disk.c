#include <stdio.h>

int main() {
    int ioq[20], i, n, ihead, tot;
    float seek = 0, avgs;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the initial head position: ");
    scanf("%d", &ihead);

    ioq[0] = ihead; // Set initial head position as the first request

    printf("Enter the I/O queue requests:\n");
    for (i = 1; i <= n; i++) {
        scanf("%d", &ioq[i]);
    }

    printf("\nOrder of requests served:\n");
    for (i = 0; i < n; i++) {
        printf("%d --> ", ioq[i]);
        tot = ioq[i + 1] - ioq[i];
        if (tot < 0)
            tot = -tot; // Absolute difference
        seek += tot;
    }
    printf("%d\n", ioq[n]); // Print the last request without `-->`

    avgs = seek / n;

    printf("\nTotal Seek Time: %.2f", seek);
    printf("\nAverage Seek Time: %.2f\n", avgs);
    return 0;
}
