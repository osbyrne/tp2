/*
compile :
clang tp_6.sleep.c -o tp_6.sleep.c.compiled

run :
./tp_6.sleep.compiled
*/

#include <stdio.h>
#include <unistd.h>

void travail() {
    usleep(500000);
}

int main() {
    while (1) {
        travail();
        sleep(1);
    }
    return 0;
}