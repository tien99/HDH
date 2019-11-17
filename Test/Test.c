#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_THREADS 4

int n;
pthread_t thdArr[NUM_THREADS];
pthread_attr_t attr;

void *runner(void *arg)
{
    long t = (long)arg;
    double x, y;
    long i, count;
    count = 0;
    for (i = 0; i < n; ++i)
    {
        x = ((double)rand() / RAND_MAX);
        y = ((double)rand() / RAND_MAX);
        if (x * x + y * y - 1 <= 0)
        {
            ++count;
        }
    }
    pthread_exit((void *)count);
}

int main(int argc, char *argv[])
{
    clock_t t1, t2;
    srand(time(NULL));
    int count, rc, nPoints;
    long t;
    if (argc != 2)
    {
        fprintf(stderr, "usage: pi_multi-thread <integer value>\n");
        return -1;
    }
    nPoints = atoi(argv[1]);
    if (nPoints <= 0)
    {
        fprintf(stderr, "%d must be > 0\n", nPoints);
        return -1;
    }
    n = nPoints / NUM_THREADS;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    t1 = clock();
    for (t = 0; t < NUM_THREADS; ++t)
    {
        rc = pthread_create(&thdArr[t], &attr, runner, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    count = 0;
    for (t = NUM_THREADS; t >= 0; --t)
    {
        void *ret;
        pthread_join(thdArr[t], &ret);
        count += (long)ret;
    }
    t2 = clock();
    printf("Time to Execute: %lf\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
    printf("PI = %lf\n", 4 * (double)count / nPoints);
    return 0;
}