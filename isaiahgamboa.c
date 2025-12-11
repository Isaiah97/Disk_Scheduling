#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//need global variables

int disk_size = 0;			// Number of tracks on the disk (tracks are 0 .. disk_size-1)
int num_requests = 0;		// How many track requests the user gave
int start_track = 0;		// Starting position of the disk head
int *requests = NULL;		// Dynamic array of track requests
int params_set = 0;			// Flag: have we entered parameters yet?


//helpers that are necessary for the project

int abs(int x) {
	return (x < 0) ? -x : x;
}



//formatting the parameters for the assignment

void print_params(void) {
	int i;

printf("\n--- Parameters ---\n");
printf("Disk size 		: %d (tracks 0 .. %d)\n", disk_size, disk_size - 1);
printf("Starting track 		: %d\n", start_track);
printf("Number of requests: %d\n", num_requests);
printf("Requests 		: ");
for (i = 0; i < num_requests; i++) {
	printf("%d", requests[i]);
	if (i < num_requests - 1) {
		printf(" , ");	
	}
}
	if (!params_set) {
		printf("\n No inputs entered.");
		return;

	}

	printf("\n------------------------\n");
}

// FIFO distance logic

int fifo_distance(void){
	int total_distance = 0;
	int current = start_track;
	int i;

	for (i = 0; i < num_requests; i++) {
		total_distance += abs(requests[i] - current);
		current = requests[i];
	}

	return total_distance;
}


// SSTF distance logic

int sstf_distance(void) {
	int *visited = NULL;
	int visited_count = 0;
	int total_distance = 0;
	int current = start_track;
	int i;

	while (visited_count < num_requests) {
		int best_index = -1;
		int best_dist = INT_MAX;

		fot (i = 0; i < num_requests; i++) {
			if (!visited[i]) {
				int dist = abs(requests[i] - current);
				if (dist < best_dist) {
					best_dist = dist;
					best_index = i;
				}
			}
		}

		total_distance += dist;
		current = requests[best_index];
		visited[best_index] = 1;
		visited_count++;
	}

	visited = (int *)calloc(num_requests, sizeof(int));
	if (visited == NULL) {
		printf("Error: failure to allocate memory for SSTF");
		return -1;
	}
}




























