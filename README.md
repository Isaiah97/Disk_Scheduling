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
What NOT to do (any violation will result in an automatic score of 0 on the assignment):
 Do NOT modify the choice values (1,2,3,4,5,6) or input characters and then try to convert
them to integers--the test script used for grading your assignment will not work correctly.
 Do NOT turn in an alternate version of the assignment downloaded from the Internet
(coursehero, chegg, reddit, github, ChatGPT, etc.) or submitted from you or another
student from a previous semester.
 Do NOT turn in your assignment coded in another programming language (C++, C#,
Java).
