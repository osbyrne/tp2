/*
compile :
clang tp_5.c -o tp_5.compiled

run :
./tp_5.compiled

run in another terminal window :
for i in {1..5}; do kill -SIGINT $(pgrep tp_5.compiled); done
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t processing_interrupt = 0;

volatile sig_atomic_t interrupt_count = 0;

sigset_t sigset;

void signal_handler(int signum) {
    if (processing_interrupt) {
        return;
    }

    processing_interrupt = 1;

    interrupt_count++;

    printf("SIGINT received and processed. Total interrupts: %d\n", interrupt_count);

    sleep(1);

    processing_interrupt = 0;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);


    printf("Press Ctrl+C to send SIGINT signals.\n");
    while (1) {
        sigprocmask(SIG_UNBLOCK, &sigset, NULL);

        if (interrupt_count > 0) {
            sigprocmask(SIG_BLOCK, &sigset, NULL);
        }
        sleep(1);
    }

    return 0;
}