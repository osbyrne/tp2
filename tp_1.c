#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*

Compile :
clang tp_1.c -o tp_1.compiled

Run :
./tp_1.compiled
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

int main()
{
    milliseconds duration = 1000;
    do_work(duration);
    return 0;
}