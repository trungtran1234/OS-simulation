#include "cpu.h"
#include <stdio.h>
#include <ctype.h>

int executeInstruction(PCB* pcb, int* currentTime) {
    if (pcb->programCounter >= pcb->instructionCount) {
        printf("process %d has no more instructions.\n", pcb->processId);
        return -1; // indicate termination
    }

    char* instr = pcb->instructions[pcb->programCounter];
    char command;
    int value;

    sscanf(instr, "%c %d", &command, &value);
    command = toupper(command);

    CPU* cpu = &pcb->cpu;

    switch (command) {
        case 'S':
            cpu->accumulator = value;
            printf("process %d: set accumulator to %d.\n", pcb->processId, cpu->accumulator);
            break;
        case 'A':
            cpu->accumulator += value;
            printf("process %d: added %d. accumulator: %d.\n", pcb->processId, value, cpu->accumulator);
            break;
        case 'D':
            cpu->accumulator -= value;
            printf("process %d: decremented accumulator by %d. accumulator: %d.\n", pcb->processId, value, cpu->accumulator);
            break;
        case 'F':
            printf("process %d: fetched data from file %d.\n", pcb->processId, value);
            break;
        case 'R':
            printf("process %d: read data from file %d.\n", pcb->processId, value);
            break;
        case 'E':
            pcb->endTime = *currentTime;
            printf("process %d: end of program.\n", pcb->processId);
            return -1; // termination
        default:
            printf("process %d: unknown instruction %c.\n", pcb->processId, command);
            break;
    }

    cpu->programCounter++;
    return 0; // continue execution
}
