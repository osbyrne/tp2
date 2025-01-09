/*
compile :
clang tp_6.alarm.c -o tp_6.alarm.c.compiled

run :
./tp_6.alarm.compiled
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void travail() {
    usleep(500000);
}

void handler(int signum) {
    travail();
    alarm(1);
}

int main() {
    signal(SIGALRM, handler);
    alarm(1);

    while (1) {
        pause();
    }
    return 0;
}