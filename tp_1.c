#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned int milliseconds;

void do_work(milliseconds duration)
{
    milliseconds i;
    for (i = 0; i < duration; i++)
    {
        usleep(1000);
    }
}

int main()
{
    milliseconds duration = 1000;
    do_work(duration);
    return 0;
}