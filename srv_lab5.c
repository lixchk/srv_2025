#include <stdio.h>
#include <time.h>
#include <sync.h>
#include <sys/neutrino.h>
barrier_t my_barrier;
void *func_thread1(void *arg)
{
    time_t cur_time;
    char time_buf[27];
    time(&cur_time);
    printf("Thread 1, start time: %s \n", ctime_r(&cur_time, time_buf));
    sleep(3);
    barrier_wait(&my_barrier);
    time(&cur_time);
    printf("Barrier in thread 1, trigger time: %s \n", ctime_r(&cur_time, time_buf));
}
void *func_thread2(void *arg)
{
    time_t cur_time;
    char time_buf[27];
    time(&cur_time);
    printf("Thread 2, start time: %s \n", ctime_r(&cur_time, time_buf));
    sleep(6);
    barrier_wait(&my_barrier);
    time(&cur_time);
    printf("Barrier in thread 2, trigger time: %s \n", ctime_r(&cur_time, time_buf));
}
int main(void)
{
    time_t cur_time;
    char time_buf[27];
    barrier_init(&my_barrier, NULL, 3);
    printf("Start \n");
    pthread_create(NULL, NULL, func_thread1, NULL);
    pthread_create(NULL, NULL, func_thread2, NULL);
    time(&cur_time);
    printf("Main(): waiting at barrier, time: %s \n", ctime_r(&cur_time, time_buf));
    barrier_wait(&my_barrier);
    time(&cur_time);
    printf("Barrier in main(), trigger time: %s \n", ctime_r(&cur_time, time_buf));
    sleep(5);

    return 0;
}

