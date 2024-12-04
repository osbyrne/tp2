#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*
compile :
clang tp_3.c -o tp_3.compiled

run :
./tp_3.compiled

in another terminal :
for i in {1..5}; do kill -SIGUSR1 PID; done
*/

typedef unsigned int milliseconds;

void do_work(milliseconds duration)
{
    milliseconds i;
    for (i = 0; i < duration; i++)
    {
        usleep(1000);
    }
}

void handle_sigusr1(int signum)
{
    printf("SIGUSR1 received by process %d - Starting work\n", getpid());
    do_work(2000); // Do 2 seconds of work when signal is received
    printf("Work completed\n");
}

int main()
{
    printf("Process ID: %d\n", getpid());
    signal(SIGUSR1, handle_sigusr1);

    while (1)
    {
        pause();
    }

    return 0;
}