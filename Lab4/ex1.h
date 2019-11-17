#ifndef EX1_H
#define EX1_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ALIGN(size, align) ((((size_t)size) + (align - 1)) & ~((size_t)align - 1))
#define IS_POWER_OF_2(num) ((num != 0) && ((num & (num - 1)) == 0))

struct newStruct
{
    unsigned int size;
    unsigned int is_free;
    struct newStruct *next;
};

typedef struct newStruct blk;

static blk *head = NULL, *tail = NULL;

blk *find_fit(unsigned int size);
void *aligned_malloc(unsigned int size, unsigned int align);
void *aligned_free(void *ptr);

#endif // EX1_H
