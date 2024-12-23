#include <stdio.h>
#include <stdlib.h> // for abs()

int main() {
    int i, n, scan, j, ioq[20], ihead, temp;
    float avg_seek, seek = 0;

    printf("Enter no of io requests: ");
    scanf("%d", &n);

    printf("Enter initial head position: ");
    scanf("%d", &ihead);
    ioq[0] = ihead;
    ioq[1] = 0;
    n += 2;

    printf("Enter IO Requests: \n");
    for (i = 2; i < n; i++) {
        printf("IO Request %d: ", i - 1);
        scanf("%d", &ioq[i]);
    }

    // Sort the I/O queue using Bubble Sort
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

    printf("\nOrder of request served:\n");

    // Serve requests to the left of the initial head position
    for (i = scan; i >= 0; i--) {
        seek += abs(ioq[i] - ioq[i + 1]);
        printf("%d -> ", ioq[i]);
    }

    // Serve requests to the right of the initial head position
    for (i = scan + 1; i < n; i++) {
        seek += abs(ioq[i] - ioq[i - 1]);
        printf("%d -> ", ioq[i]);
    }

    avg_seek = seek / (n - 2); // Exclude the initial head position and 0

    printf("\n\nTotal seek time is %.2f\n", seek);
    printf("Average seek time is %.2f\n", avg_seek);

    return 0;
}