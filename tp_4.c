/*
compile :
clang tp_4.c -o tp_4.exe

run :
./tp_4.c

in another terminal :
for i in {1..5}; do kill -SIGINT PID; done
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile int interrupt_count = 0;
sigset_t mask;

void handler(int signum)
{
    interrupt_count++;
    printf("Interrupt %d received\n", interrupt_count);
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    while (1)
    {
        sigprocmask(SIG_BLOCK, &mask, NULL);
        if (interrupt_count > 0)
        {
            printf("Processing interruption burst: %d signals\n", interrupt_count);
            sleep(1); // Simulating work
            interrupt_count = 0;
        }
        sigprocmask(SIG_UNBLOCK, &mask, NULL);
        sleep(1);
    }
    return 0;
}