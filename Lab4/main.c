#include "ex1.h"
#include <math.h>

int main(int argc, char *argv[])
{
    printf("PID: %d\n", getpid());
    for (unsigned int align = 2; align <= pow(2, 22); align *= 2)
    {
        void *p = aligned_malloc(1024, align);
        printf("%10d %p %15ld %ld \n", align, p,
               (unsigned long)p, ((unsigned long)p) % align);
        aligned_free(p);
    }
    return 0;
}