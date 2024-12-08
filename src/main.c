#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ipc.h"
#include "process.h"
#include "scheduler.h"
#include "cpu.h"

int main() {
    PcbTable pcbTable;
    initPcbTable(&pcbTable);
    Queue readyQueue, blockedQueue;
    initQueue(&readyQueue);
    initQueue(&blockedQueue);

    int currentTime = 0;
    int runningProcess = -1;
    const int TIME_SLICE = 5;

    // create initial process
    int initPid = createProcess(&pcbTable, 0, 1);
    enqueue(&readyQueue, initPid);

    char command;
    while (1) {
        printf("$ ");
        fflush(stdout);
        command = getchar();
        while (getchar() != '\n' && !feof(stdin)); // consume newline

        command = toupper(command);
        if (command == 'Q') {
            // time unit passed
            schedule(&pcbTable, &readyQueue, &blockedQueue, &runningProcess, TIME_SLICE, &currentTime);
        } else if (command == 'U') {
            // unblock a process
            if (!isEmpty(&blockedQueue)) {
                int pid = dequeue(&blockedQueue);
                pcbTable.pcb[pid - 1].state = READY;
                enqueue(&readyQueue, pid);
                printf("process %d unblocked.\n", pid);
            } else {
                printf("no blocked processes.\n");
            }
        } else if (command == 'P') {
            // print system state
            printPcbTable(&pcbTable);
            printf("ready queue: ");
            for (node* temp = readyQueue.front; temp; temp = temp->next)
                printf("%d ", temp->processId);
            printf("\nblocked queue: ");
            for (node* temp = blockedQueue.front; temp; temp = temp->next)
                printf("%d ", temp->processId);
            printf("\n");
        } else if (command == 'T') {
            // terminate simulation
            printf("terminating simulation.\n");
            break;
        } else {
            printf("invalid command. use q, u, p, or t.\n");
        }
    }

    return 0;
}
