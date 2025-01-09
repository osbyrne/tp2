/*
compile :
clang tp_7.c -o tp_7.c.compiled

run :
./tp_7.c.compiled
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void travail() {
    usleep(500000);
    printf("Travail effectué\n");
    fflush(stdout);
}

void timer_handler(int signum, siginfo_t *si, void *uc) {
    travail();
}

int main() {
    timer_t timerid;
    struct sigevent sev;
    struct itimerspec its;
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timer_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL);

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timerid;
    timer_create(CLOCK_REALTIME, &sev, &timerid);

    its.it_value.tv_sec = 1;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 1;
    its.it_interval.tv_nsec = 0;

    timer_settime(timerid, 0, &its, NULL);

    while (1) {
        pause();
    }

    return 0;
}