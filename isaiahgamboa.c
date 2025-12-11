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

// FIFO logic

int fifo_distance(void){
	
}
































