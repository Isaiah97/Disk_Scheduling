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
	
}