#include "ipc.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

void init_ipc(int pipefd[2]) {
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

pid_t spawn_receiver_process(int pipefd[2]) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        // child - receiver
        close(pipefd[1]);
        while (1) {
            char buffer;
            ssize_t n = read(pipefd[0], &buffer, 1);
            if (n > 0) {
                printf("received command: %c\n", buffer);
                if (buffer == 'T')
                    break;
            }
        }
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    } else {
        // parent - sender
        close(pipefd[0]);
    }
    return pid;
}

void send_command(int pipefd[2], char command) {
    if (write(pipefd[1], &command, 1) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

char read_command(int pipefd[2]) {
    char buffer;
    ssize_t n = read(pipefd[0], &buffer, 1);
    return (n > 0) ? buffer : '\0';
}
