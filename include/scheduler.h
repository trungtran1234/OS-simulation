#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef struct node {
    int processId;
    struct node* next;
} node;

typedef struct {
    node* front;
    node* rear;
} Queue;

void initQueue(Queue* q);
void enqueue(Queue* q, int processId);
int dequeue(Queue* q);
int isEmpty(Queue* q);

void schedule(PcbTable* pcbTable, Queue* readyQueue, Queue* blockedQueue, int* runningProcess, int TIME_SLICE, int* currentTime);

#endif
