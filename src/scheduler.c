#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue* q, int processId) {
    node* temp = (node*)malloc(sizeof(node));
    temp->processId = processId;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

int dequeue(Queue* q) {
    if (q->front == NULL)
        return -1;
    node* temp = q->front;
    int pid = temp->processId;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return pid;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

void schedule(PcbTable* pcbTable, Queue* readyQueue, Queue* blockedQueue, int* runningProcess, int TIME_SLICE, int* currentTime) {
    if (*runningProcess == -1 && !isEmpty(readyQueue)) {
        *runningProcess = dequeue(readyQueue);
        pcbTable->pcb[*runningProcess - 1].state = RUNNING;
        printf("process %d is now running.\n", *runningProcess);
    }

    if (*runningProcess != -1) {
        PCB* pcb = &pcbTable->pcb[*runningProcess - 1];
        pcb->timeUsed += 1;
        pcb->programCounter += 1; // simulating instruction execution
        (*currentTime)++;

        if (pcb->timeUsed % TIME_SLICE == 0) {
            pcb->state = READY;
            enqueue(readyQueue, *runningProcess);
            printf("time slice expired for process %d.\n", *runningProcess);
            *runningProcess = -1;
        }
    }
}
