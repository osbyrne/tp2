/*
compile : 
clang tp_9.c -o tp_9.c.compiled

run :
./tp_9.c.compiled
*/
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

void t2() {
    usleep(166500); // 0.1665 seconds
    printf("T2 executed\n");
    fflush(stdout);
}

void t3() {
    usleep(500000); // 0.5 seconds
    printf("T3 executed\n");

    fflush(stdout);
}

void t4() {
    usleep(1000000); // 1 second
    printf("T4 executed\n");
    fflush(stdout);
}

void do_work(struct timespec *start) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    double elapsed = (now.tv_sec - start->tv_sec) + (now.tv_nsec - start->tv_nsec) / 1e9;

    if (fmod(elapsed, 2.0) < 1e-3) {
        t2();
    }
    if (fmod(elapsed, 3.0) < 1e-3) {
        t3();
    }
    if (fmod(elapsed, 4.0) < 1e-3) {
        t4();
    }
}

int main() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    while (1) {
        do_work(&start);
        usleep(100000); // Sleep for 0.1 seconds to reduce CPU usage
    }

    return 0;
}