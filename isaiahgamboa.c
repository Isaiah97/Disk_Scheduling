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

	free(visited);
	return total_distance;
}

/*
 * SCAN :
 * the head moves in a chosen direction (up or down),
 * services all requests in that direction, then reverses and
 * services the remaining ones.
 * direction_up = 1  -> move towards higher track numbers first
 * direction_up = 0  -> move towards track 0 first
 */

int scan_distance (int direction_up) {
	int *temp = NULL;
	int total_distance = 0;
	int current = start_track;
	int i, split;

	//sorting requests
	for (i = 0; i < num_requests; i++) {
		temp[i] = requests[i];
	}
	sort_array(temp, num_requests);

	//start_track must equal first request

	split = num_requests;
	for (i = 0; i < num_requests; i++) {
		if (temp[i] >= start_track) {
			split = i;
			break;
		}
	}

	if (direction_up) {
		//moves up
		for (i = split; i < num_requests; i++) {
			total_distance += abs(temp[i] - current);
			current = temp[i];
		}

		//reverse if requests are too low.
		if (split > 0) {
			total_distance += abs((disk_size - 1) - current);
			current = disk_size - 1;

			for (i = split - 1; i >= 0; i--) {
				total_distance += abs(temp[i] - current);
				current = temp[i];
			}
		}
	}
	else{
		//moving downward first

		for (i = split - 1; i >= 0; i--) {
			total_distance += abs(temp[i] - current);
			current = temp[i];
		}

		//too many request handling

		if (split < num_requests) {
			total_distance += abs(current - 0);
			current = 0;

			for (i = split; i < num_requests; i++) {
				total_distance += abs(temp[i] - current);
				current = temp[i];
			}
		}
	}

	temp = (int *)malloc(num_requests * sizeof(int));
	if (temp == NULL) {
		printf("Error no memory allocated memory in scan\n");
		return -1;
	}

	free(temp);
	return total_distance;
}

// input menu for user input

void enter_params(void) {
	int i;
	int track;

	printf("\nEnter disk size (number of tracks): ");
	printf("%d", &disk_size);

	if (disk_size <= 0){
		printf("Disk size must be positive.\n");
		params_set = 0;
		return;
	}

	printf("Enter number of requests: ");
	printf("%d", &num_requests);

	if (num_requests <= 0) {
		printf("Number of requests must be positive.\n");
		params_set = 0;
		return;
	}

	printf("Enter starting track (0 ... %d): ", disk_size -1);
	scanf("%d", &start_track);

	if (start_track < 0 || start_track >= disk_size) {
		printf("Starting track is out of range.\n");
		if (start_track < 0) 
			start_track = 0;
		
		if (start_track >= disk_size) 
			start_track = disk_size - 1;
	}

	requests = (int *)malloc(num_requests * sizeof(int));
	if (requests == NULL) {
		printf("Error: could not allocate memory for requests.\n");
		params_set = 0;
		return;
	}

	


	// freeing older requests
	if (requests != NULL) {
		free(requests);
		requests = NULL;
	}

}
























