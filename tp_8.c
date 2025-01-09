/*
compile : 
clang tp_8.c -o tp_8.c.compiled

run :
./tp_8.c.compiled
*/
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void t2() {
    usleep(333000);
    printf("T2 executed\n");
    fflush(stdout);
}

void t3() {
    sleep(1);
    printf("T3 executed\n");
    fflush(stdout);
}

void t4() {
    sleep(2);
    printf("T4 executed\n");
    fflush(stdout);
}

void do_work() {
    static int count = 0;

    if (count % 2 == 0) {
        t2();
    }
    if (count % 3 == 0) {
        t3();
    }
    if (count % 4 == 0) {
        t4();
    }

    count++;
}

int main() {
    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 0;

    while (1) {
        do_work();
        nanosleep(&ts, NULL);
    }

    return 0;
}