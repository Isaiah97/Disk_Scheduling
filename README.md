# Disk_Scheduling

Objective:
 To compare the performance of various disk scheduling algorithms:
First-in-first-out (FIFO), Shortest-seek-time-first (SSTF), Scan, and C-Scan.
Specification:
 The program compares the disk scheduling algorithms: First-in-first-out (FIFO),
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
Assignment:
 For a sequence of size m, a disk scheduling algorithm accepts a starting track followed by
a sequence of m-1 integers, where each index value t is a request to seek track t.
 Each scheduling algorithm generates an ordering according to which the m-1 requests are
serviced from the starting track, and calculates the distance of the tracks traversed.
