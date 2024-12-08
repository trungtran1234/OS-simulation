#include "process.h"
#include <stdio.h>

void initPcbTable(PcbTable* table) {
    table->count = 0;
}

int createProcess(PcbTable* table, int parentId, int priority) {
    if (table->count >= MAX_PROCESSES) {
        printf("max process limit reached.\n");
        return -1;
    }
    PCB* pcb = &table->pcb[table->count];
    pcb->processId = table->count + 1;
    pcb->parentProcessId = parentId;
    pcb->programCounter = 0;
    pcb->priority = priority;
    pcb->state = READY;
    pcb->startTime = 0;
    pcb->timeUsed = 0;
    pcb->endTime = 0;
    pcb->cpu.programCounter = 0;
    pcb->cpu.accumulator = 0;
    // instructions and instructionCount can be assigned later
    table->count++;
    return pcb->processId;
}

void printPcbTable(PcbTable* table) {
    printf("pid\tppid\tpc\tpriority\tstate\tstarttime\ttimeused\n");
    for (int i = 0; i < table->count; i++) {
        PCB pcb = table->pcb[i];
        char* stateStr;
        switch (pcb.state) {
            case READY: stateStr = "ready"; break;
            case RUNNING: stateStr = "running"; break;
            case BLOCKED: stateStr = "blocked"; break;
            case TERMINATED: stateStr = "terminated"; break;
            default: stateStr = "unknown"; 
        }
        printf("%d\t%d\t%d\t%d\t\t%s\t%d\t\t%d\n", 
               pcb.processId, pcb.parentProcessId, pcb.programCounter, 
               pcb.priority, stateStr, pcb.startTime, pcb.timeUsed);
    }
}
