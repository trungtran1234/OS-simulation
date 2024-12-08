#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESSES 100

typedef enum { READY, RUNNING, BLOCKED, TERMINATED } process_state;

typedef struct {
    int programCounter;
    int accumulator;  
} CPU;

typedef struct {
    int processId;
    int parentProcessId;
    int programCounter;
    int priority;
    process_state state;
    int startTime;
    int timeUsed;
    int endTime;
    CPU cpu;
    char** instructions;
    int instructionCount;
} PCB;

typedef struct {
    PCB pcb[MAX_PROCESSES];
    int count;
} PcbTable;

void initPcbTable(PcbTable* table);
int createProcess(PcbTable* table, int parentId, int priority);
void printPcbTable(PcbTable* table);

#endif
