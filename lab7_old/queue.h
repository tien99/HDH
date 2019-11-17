#ifndef QUEUE_H
#define QUEUE_H

#include "structs.h"

void initialize_queue(struct pqueue_t *q);
struct pcb_t *de_queue(struct pqueue_t *q);
void en_queue(struct pqueue_t *q, struct pcb_t *proc);
int empty(struct pqueue_t *q);

#endif