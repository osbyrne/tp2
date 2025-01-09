/*
compile :
clang tp_14.c -o tp_14.c.compiled

run :
./tp_14.c.compiled
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>

void t2() {
    usleep(256000); // 0.256 seconds
    printf("T2 executed\n");
    fflush(stdout);
}

void t3() {
    usleep(769000); // 0.769 seconds
    printf("T3 executed\n");
    fflush(stdout);
}

void t4() {
    usleep(1538000); // 1.538 seconds
    printf("T4 executed\n");
    fflush(stdout);
}

void *task2(void *arg) {
    struct timespec ts;
    ts.tv_sec = 2;
    ts.tv_nsec = 0;

    while (1) {
        t2();
        nanosleep(&ts, NULL);
    }
    return NULL;
}

void *task3(void *arg) {
    struct timespec ts;
    ts.tv_sec = 3;
    ts.tv_nsec = 0;

    while (1) {
        t3();
        nanosleep(&ts, NULL);
    }
    return NULL;
}

void *task4(void *arg) {
    struct timespec ts;
    ts.tv_sec = 4;
    ts.tv_nsec = 0;

    while (1) {
        t4();
        nanosleep(&ts, NULL);
    }
    return NULL;
}

int main() {
    pthread_t thread2, thread3, thread4;
    struct sched_param param2, param3, param4;
    pthread_attr_t attr2, attr3, attr4;

    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);
    pthread_attr_init(&attr4);

    pthread_attr_setschedpolicy(&attr2, SCHED_FIFO);
    pthread_attr_setschedpolicy(&attr3, SCHED_FIFO);
    pthread_attr_setschedpolicy(&attr4, SCHED_FIFO);

    param2.sched_priority = 3;
    param3.sched_priority = 2;
    param4.sched_priority = 1;

    pthread_attr_setschedparam(&attr2, &param2);
    pthread_attr_setschedparam(&attr3, &param3);
    pthread_attr_setschedparam(&attr4, &param4);

    pthread_create(&thread2, &attr2, task2, NULL);
    pthread_create(&thread3, &attr3, task3, NULL);
    pthread_create(&thread4, &attr4, task4, NULL);

    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    return 0;
}