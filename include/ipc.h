#ifndef IPC_H
#define IPC_H

#include <sys/types.h>

void init_ipc(int pipefd[2]);
pid_t spawn_receiver_process(int pipefd[2]);
void send_command(int pipefd[2], char command);
char read_command(int pipefd[2]);

#endif
