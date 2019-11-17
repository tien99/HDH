#include "ex1.h"

/* Tim block trong */
memNode *findFree(size_t size)
{
    memNode *cur = head;
    while (cur != NULL)
    {
        if (cur->isFree == 1 && cur->size >= size)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

void *aligned_malloc(unsigned int size, unsigned int align)
{
    if (size == 0)
        return NULL;
    /* Kiem tra so mu cua 2 */
    if (ceil(log2((float)align)) != floor(log2((float)align)))
        return NULL;
    /* Tong gia tri do lon cua block can xin */
    unsigned int total_size = size + align - 1 + sizeof(memNode);
    memNode *header = findFree(total_size);
    void *ret = NULL;
    if (header != NULL)
    {
        header->isFree = 0;
        ret = (void *)(((size_t)header + sizeof(memNode) + align - 1) & ~((size_t)align - 1));
        *((void **)((size_t)ret - sizeof(memNode))) = header;
        return ret;
    }
    void *block = sbrk(total_size);
    if (block == (void *)-1)
        return NULL;
    header = block;
    header->size = total_size;
    header->block = (size_t)block;
    header->isFree = 0;
    header->next = NULL;
    if (head == NULL)
        head = header;
    if (tail != NULL)
        tail->next = header;
    tail = header;
    /* Tim vi tri tra ve thoa man */
    ret = (void *)(((size_t)header + sizeof(memNode) + align - 1) & ~((size_t)align - 1));
    /* Luu tru thong tin block tai khong gian truoc gia tri tra ve */
    *((void **)((size_t)ret - sizeof(memNode))) = header;
    return ret;
}

void aligned_free(void *ptr)
{
    if (ptr == NULL)
        return;
    /* Lay lai thong tin cua block */
    memNode *header = (memNode *)((size_t)ptr - sizeof(memNode));
    void *prgBrk = sbrk(0);
    /* Neu block nam o sat diem break */
    if (header->block + header->size == (size_t)prgBrk)
    {
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            memNode *tmp = head;
            while (tmp != NULL)
            {
                if (tmp->next == tail)
                {
                    tmp->next = NULL;
                    tail = tmp;
                }
                tmp = tmp->next;
            }
        }
        sbrk(0 - (unsigned int)header->size - sizeof(memNode));
        return;
    }
    header->isFree = 1;
}
