/*
compile : 
clang tp_11.c -o tp_11.c.compiled -lpthread

run :
./tp_11.c.compiled
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>

typedef struct {
    int id;
    double period;
    double execution_time;
    double next_deadline;
} task_t;

task_t tasks[3];
pthread_mutex_t lock;

void t1() {
    usleep(100000); // 0.1 seconds
    printf("T1 executed\n");
    fflush(stdout);
}

void t2() {
    usleep(333000); // 0.333 seconds
    printf("T2 executed\n");
    fflush(stdout);
}

void t3() {
    usleep(500000); // 0.5 seconds
    printf("T3 executed\n");
    fflush(stdout);
}

void *scheduler(void *arg) {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    while (1) {
        pthread_mutex_lock(&lock);
        double min_deadline = tasks[0].next_deadline;
        int min_index = 0;

        for (int i = 1; i < 3; i++) {
            if (tasks[i].next_deadline < min_deadline) {
                min_deadline = tasks[i].next_deadline;
                min_index = i;
            }
        }

        double elapsed = (clock() - start.tv_sec) + (clock() - start.tv_nsec) / 1e9;
        if (elapsed >= tasks[min_index].next_deadline) {
            switch (tasks[min_index].id) {
                case 1:
                    t1();
                    break;
                case 2:
                    t2();
                    break;
                case 3:
                    t3();
                    break;
            }
            tasks[min_index].next_deadline += tasks[min_index].period;
        }
        pthread_mutex_unlock(&lock);
        usleep(1000); // Sleep for 1 ms to reduce CPU usage
    }
    return NULL;
}

int main() {
    pthread_t scheduler_thread;
    pthread_mutex_init(&lock, NULL);

    tasks[0] = (task_t){1, 2.0, 0.1, 2.0};
    tasks[1] = (task_t){2, 3.0, 0.333, 3.0};
    tasks[2] = (task_t){3, 4.0, 0.5, 4.0};

    pthread_create(&scheduler_thread, NULL, scheduler, NULL);

    pthread_join(scheduler_thread, NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}