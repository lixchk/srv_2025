#include <stdio.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <sched.h>

pthread_t thread_id1;
pthread_t thread_id2;

// Функция для первого потока
void *long_thread1(void *notused)
{
    int n;
    for (n = 0; n < 5; n++) {
        printf("Eto pervii potok, TID %ld - N povtora %d \n", thread_id1, n);
        sleep(2);
    }
    return NULL;
}

// Функция для второго потока
void *long_thread2(void *notused)
{
    int m;
    for (m = 0; m < 5; m++) {
        printf("Eto vtoroi potok, TID %ld - N povtora %d \n", thread_id2, m);
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    printf("Prog threads  PID %d \n", getpid());

    struct sched_param param1, param2;
    int policy1, policy2;

    pthread_create(&thread_id1, NULL, long_thread1, NULL);
    // Параметры для первого потока
    pthread_getschedparam(thread_id1, &policy1, &param1);
    param1.sched_priority = 17; // Приоритет 17 для первого потока
    policy1 = SCHED_FIFO; // FIFO
    pthread_setschedparam(thread_id1, policy1, &param1);

    pthread_create(&thread_id2, NULL, long_thread2, NULL);
    // Параметры для второго потока
    pthread_getschedparam(thread_id2, &policy2, &param2);
    param2.sched_priority = 14; // Приоритет 14 для второго потока
    policy2 = SCHED_FIFO;
    pthread_setschedparam(thread_id2, policy2, &param2);

    sleep(40);
    printf("The end");

    return 0;
}
