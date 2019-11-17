#include "ex1.h"

/* Tim block trong dau tien co size thich hop */
blk *find_fit(unsigned int size)
{
    blk *cur = head;
    while (cur != NULL)
    {
        if (cur->is_free == 1 && cur->size >= size)
            break;
        cur = cur->next;
    }
    return cur;
}

void *aligned_malloc(unsigned int size, unsigned int align)
{
    if (size == 0)
        return NULL;
    /* Kiem tra align la so mu cua 2 */
    if (IS_POWER_OF_2(align) == 0)
        return NULL;
    /* Tong gia tri do lon cua block can xin */
    unsigned int total_size = size + align - 1 + sizeof(blk) + sizeof(blk *);
    /* Tim block trong thich hop (neu co) */
    blk *blk_head = find_fit(total_size);
    void *ret;
    if (blk_head != NULL)
    {
        /* Gan gia tri "da duoc dung" */
        blk_head->is_free = 0;
        /* Tim vi tri tra ve thich hop */
        ret = (void *)(ALIGN(blk_head + sizeof(blk) + sizeof(blk *), align));
        /* Luu con tro den vi tri giu thong tin cua block */
        *(blk **)((size_t)ret - sizeof(blk *)) = blk_head;
        return ret;
    }
    void *block = sbrk(total_size);
    if (block == (void *)-1)
        return NULL;
    /* Vi tri luu thong tin cua block */
    blk_head = block;
    blk_head->size = total_size;
    blk_head->is_free = 0;
    blk_head->next = NULL;
    if (head == NULL)
        head = blk_head;
    if (tail != NULL)
        tail->next = blk_head;
    tail = blk_head;
    /* Tim vi tri tra ve thich hop */
    ret = (void *)(ALIGN(block + sizeof(blk) + sizeof(blk *), align));
    /* Luu con tro den vi tri giu thong tin cua block */
    *(blk **)((size_t)ret - sizeof(blk *)) = blk_head;
    return ret;
}

/* Ham nay khong nhat thiet phai tra ve con tro (void *), tuy nhien em lam theo prototype de bai yeu cau */
void *aligned_free(void *ptr)
{
    if (ptr == NULL)
        return NULL;
    /* Tro den vi tri luu thong tin cua block */
    blk *blk_head = *((blk **)((size_t)ptr - sizeof(blk *)));
    void *prg_brk = sbrk(0);
    /* Neu block nam o sat diem break, (neu co thi block nay phai o tail) */
    if ((size_t)blk_head + blk_head->size == (size_t)prg_brk)
    {
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            blk *tmp = head;
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
        sbrk(0 - (unsigned int)blk_head->size);
        return NULL;
    }
    /* Neu khong giai phong duoc vung nho, danh dau block la "trong" */
    blk_head->is_free = 1;
    /* Tra ve con tro toi vi tri luu thong tin cua block (co the dung de debug) */
    return (void *)blk_head;
}
