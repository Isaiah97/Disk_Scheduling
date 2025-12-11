/*The program compares the disk scheduling algorithms: First-in-first-out (FIFO),
Shortest-seek-time-first (STTF), Scan, and C-Scan in terms of traversing a set of tracks
input by the user, and calculates the total distance of the tracks traversed.
 A menu controls the operations, and each choice calls the appropriate procedure, where
the choices are:
1) Enter parameter
2) Calculate distance to traverse tracks using FIFO
3) Calculate distance to traverse tracks using SSTF
4) Calculate distance to traverse tracks using Scan
5) Calculate distance to traverse tracks using C-Scan
6) Quit program and free memory
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int seq_size = 0;      // total sequence size m (including starting track) 
int params_set = 0;    // did the user enter the size yet? 

//Helper class

int abs(int x) {
    return (x < 0) ? -x : x;
}

//---------- FIFO ---------- 
// FIFO just follows the input order: start, then the sequence as given. 
int fifo(int start, int *req, int m, int *order) {
    int i;
    int total = 0;

    order[0] = start;
    for (i = 0; i < m - 1; i++) {
        order[i + 1] = req[i];
    }

    total += abs(start - 0);

    for (i = 0; i < m - 1; i++) {
        total += abs(order[i + 1] - order[i]);
    }

    return total;
}

//SSTF algo
//At each step, go to the closest unvisited request.
int sstf(int start, int *req, int m, int *order) {
    int n = m - 1;   // number of requests
    int *visited = (int *)calloc(n, sizeof(int));
    int i;
    int k;
    int current = start;
    int total = 0;

    if (visited == NULL) {
        printf("Error: could not allocate memory in SSTF.\n");
        return -1;
    }

    order[0] = start;

    total += abs(start - 0);

    for (k = 1; k < m; k++) {
        int best_index = -1;
        int best_dist = INT_MAX;

        for (i = 0; i < n; i++) {
            if (!visited[i]) {
                int d = abs(req[i] - current);
                if (d < best_dist) {
                    best_dist = d;
                    best_index = i;
                }
            }
        }

        order[k] = req[best_index];
        total += best_dist;
        current = req[best_index];
        visited[best_index] = 1;
    }

    free(visited);
    return total;
}

//Sorting helper for SCAN / C-SCAN

void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_array(int *arr, int n) {
    int i;
    int j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap_int(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/*
 * We treat SCAN as:
 * - sort the requests
 * - if direction = increasing:
 *     go from the closest >= start, up to largest,
 *     then reverse and go through the smaller ones.
 * - if direction = decreasing: symmetric.
 * We only care about the ORDER of requests, not the actual disk ends,
 * to match the sample's traversed sequence style.
 */
int scan_alg(int start, int *req, int m, int *order, int direction_up) {
    int n = m - 1;
    int *sorted = (int *)malloc(n * sizeof(int));
    int i = 1;
    int k = 1;
    int total = 0;

    if (sorted == NULL) {
        printf("Error: could not allocate memory in SCAN.\n");
        return -1;
    }

    for (i = 0; i < n; i++) {
        sorted[i] = req[i];
    }
    sort_array(sorted, n);

    // find first index with track >= start
    int split = n;
    for (i = 0; i < n; i++) {
        if (sorted[i] >= start) {
            split = i;
            break;
        }
    }

    order[0] = start;

    if (direction_up) {
        // go up first: from split..n-1
        for (i = split; i < n; i++) {
            order[k++] = sorted[i];
        }

        // then go down: from split-1..0
        for (i = split - 1; i >= 0; i--) {
            order[k++] = sorted[i];
        }

    } else {
        // go down first: split-1..0
        for (i = split - 1; i >= 0; i--) {
            order[k++] = sorted[i];
        }

        // then go up: split..n-1
        for (i = split; i < n; i++) {
            order[k++] = sorted[i];
        }
    }

    // compute total distance
    total += abs(start - 0);
    for (i = 0; i < m - 1; i++) {
        total += abs(order[i + 1] - order[i]);
    }

    free(sorted);
    return total;
}

//C-SCAN 
/*
 * C-SCAN:
 * - sort the requests
 * - if direction = increasing:
 *     visit all >= start (ascending), then wrap and visit < start (ascending).
 * - if direction = decreasing:
 *     visit all <= start (descending), then wrap and visit > start (descending).
 */
int cscan_alg(int start, int *req, int m, int *order, int direction_up) {
    int n = m - 1;
    int *sorted = (int *)malloc(n * sizeof(int));
    int i;
    int k = 1;
    int total = 0;

    if (sorted == NULL) {
        printf("Error: could not allocate memory in C-SCAN.\n");
        return -1;
    }

    for (i = 0; i < n; i++) {
        sorted[i] = req[i];
    }
    sort_array(sorted, n);

    int split = n;
    for (i = 0; i < n; i++) {
        if (sorted[i] >= start) {
            split = i;
            break;
        }
    }

    order[0] = start;
    if (direction_up) {
        // first: from split..n-1 (upward)
        for (i = split; i < n; i++) {
            order[k++] = sorted[i];
        }
        // then wrap: from 0..split-1 (upward)
        for (i = 0; i < split; i++) {
            order[k++] = sorted[i];
        }

    } else {
        // first: from split-1..0 (downward)
        for (i = split - 1; i >= 0; i--) {
            order[k++] = sorted[i];
        }
        // then wrap: from n-1..split (downward)
        for (i = n - 1; i >= split; i--) {
            order[k++] = sorted[i];
        }
    }

    total += abs(start - 0);
    for (i = 0; i < m - 1; i++) {
        total += abs(order[i + 1] - order[i]);
    }

    free(sorted);
    return total;
}

// Main / Menu Logic

void print_menu(void) {
    printf("\nDisk scheduling\n");
    printf("---------------\n");
    printf("1) Enter parameters\n");
    printf("2) Calculate distance to traverse tracks using FIFO\n");
    printf("3) Calculate distance to traverse tracks using SSTF\n");
    printf("4) Calculate distance to traverse tracks using Scan\n");
    printf("5) Calculate distance to traverse tracks using C-Scan\n");
    printf("6) Quit program and free memory\n");
}

int main(void) {
    int choice;
    int done = 0;

    while (!done) {
        print_menu();
        printf("Enter selection: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Quitting program...\n");
            break;
        }

        if (choice == 1) {
            printf("Enter size of sequence: ");
            scanf("%d", &seq_size);
            if (seq_size <= 1) {
                printf("Size must be at least 2 (start + at least one request).\n");
                params_set = 0;
            } else {
                params_set = 1;
            }
        } else if (choice >= 2 && choice <= 5) {
            if (!params_set) {
                printf("Please enter parameters first (option 1).\n");
                continue;
            }

            int start;
            int n = seq_size - 1;
            int *requests = (int *)malloc(n * sizeof(int));
            int *order = (int *)malloc(seq_size * sizeof(int));
            int i;
            int direction;
            int dist;

            if (requests == NULL || order == NULL) {
                printf("Memory allocation failed.\n");
                free(requests);
                free(order);
                continue;
            }

            printf("Enter starting track: ");
            scanf("%d", &start);

            printf("Enter sequence of tracks to seek: ");
            for (i = 0; i < n; i++) {
                scanf("%d", &requests[i]);
            }

            if (choice == 2) {
                dist = fifo(start, requests, seq_size, order);

            } 
            else if (choice == 3) {
                dist = sstf(start, requests, seq_size, order);
            }             
            else if (choice == 4) {
                printf("Enter initial direction: (0=decreasing, 1=increasing): ");
                scanf("%d", &direction);
                dist = scan_alg(start, requests, seq_size, order, direction);
            } 
            else /* this will be option 5 */ {
                dist = cscan_alg(start, requests, seq_size, order, direction);
            }

            //universal for all inputs.
            printf("Traversed sequence: ");
            for (i = 0; i < seq_size; i++) {
                printf("%d", order[i]);
                if (i < seq_size - 1) 
                	printf(" ");
            }

            printf("\n");
            printf("The distance of the traversed tracks is: %d\n", dist);

            free(requests);
            free(order);
        } 
        else if (choice == 6) {
            printf("Quitting program...\n");
            done = 1;
        } 
        
    }

    return 0;
}
