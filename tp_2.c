#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

typedef unsigned int milliseconds;

void do_work(milliseconds duration)
{
    milliseconds i;
    for (i = 0; i < duration; i++)
    {
        usleep(1000); // the unit of usleep input is microseconds
    }
}

void handle_sigusr1(int signum)
{
    printf("SIGUSR1 received by process %d\n", getpid());
}

int main()
{
    printf("Process ID: %d\n", getpid()); // send the command "kill -SIGUSR1 <pid>" to send a signal to this process
    signal(SIGUSR1, handle_sigusr1);

    while (1)
    {
        pause();
    }

    return 0;
}