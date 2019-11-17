#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    clock_t t1, t2;
    srand(time(NULL));
    double x, y;
    int count, nPoints, i;
    if (argc != 2)
    {
        fprintf(stderr, "usage: pi_serial <integer value>\n");
        return -1;
    }
    nPoints = atoi(argv[1]);
    if (nPoints < 0)
    {
        fprintf(stderr, "%d must be >= 0\n", nPoints);
        return -1;
    }
    time(&t1);
    count = 0;
    unsigned int state = rand();
    for (i = 0; i < nPoints; ++i)
    {
        x = (double)rand_r(&state) / RAND_MAX;
        y = (double)rand_r(&state) / RAND_MAX;
        if (x * x + y * y - 1 <= 0)
        {
            ++count;
        }
    }
    time(&t2);
    printf("Time to Execute: %lds\n", (t2 - t1));
    printf("PI = %lf\n", 4 * (double)count / nPoints);
    return 0;
}