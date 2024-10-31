#include <stdio.h>

int main() {
    int ioq[20], i, n, j, ihead, temp, scan, tot;
    float seek = 0, avgs;

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the initial head position: ");
    scanf("%d", &ihead);
    ioq[0] = ihead;  // Store initial head position
    ioq[1] = 0;      // Add starting point (0)
    n += 2;          // Include head and starting point

    printf("Enter the I/O queue requests:\n");
    for (i = 2; i < n; i++) {
        scanf("%d", &ioq[i]);
    }

    // Sorting the I/O queue using Bubble Sort
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (ioq[j] > ioq[j + 1]) {
                temp = ioq[j];
                ioq[j] = ioq[j + 1];
                ioq[j + 1] = temp;
            }
        }
    }

    // Find the position of the initial head in the sorted queue
    for (i = 0; i < n; i++) {
        if (ihead == ioq[i]) {
            scan = i;
            break;
        }
    }

    printf("\nOrder of request served:\n\n");
    tot = 0;

    // Serve requests to the left of the initial head position
    for (i = scan; i >= 0; i--) {
        if (i == scan) {
            tot = ioq[i] - ioq[i + 1]; // First movement to the left
        } else {
            tot = ioq[i] - ioq[i + 1];
        }
        if (tot < 0) tot = -tot;  // Make distance positive
        seek += tot;               // Accumulate total seek time
        printf("%d\t%d\n", ioq[i], tot);
    }

    // Serve requests to the right of the initial head position
    for (i = scan + 1; i < n; i++) {
        tot = ioq[i] - ioq[i - 1];
        if (tot < 0) tot = -tot;  // Make distance positive
        seek += tot;               // Accumulate total seek time
        printf("%d\t%d\n", ioq[i], tot);
    }

    avgs = seek / (n - 2);  // Average seek time excluding head and starting point

    printf("\nTotal Seek time\t\t: %.2f", seek);
    printf("\nAverage seek time\t: %.2f\n", avgs);

    return 0;
}
