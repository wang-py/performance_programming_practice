#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

static char* sub_process_name = "../sim86/sim86";

int disassemble_code(char* argv[], char* disassembled_code) {
    int pipefd[2];
    pipe(pipefd);
    int pid = fork();

    if (pid == -1) {
        printf("Failed to call fork()\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(pipefd[0]);

        dup2(pipefd[1], 1);
        dup2(pipefd[1], 2);

        close(pipefd[1]);
        argv[0] = sub_process_name;
        execv(argv[0], argv);
        perror("execv");
        exit(2);
    }

    int status;
    int wait_result;
    char buffer[1024];

    close(pipefd[1]);

    while (read(pipefd[0], buffer, sizeof(buffer)) != 0) {
        strcpy(disassembled_code, buffer);
    }

    // printf("All children have finished.\n");
    return 0;
}

int main(int argc, char* argv[]) {
    char* disassembled_code = malloc(sizeof(char) * 1024);
    disassemble_code(argv, disassembled_code);
    printf(disassembled_code);
    free(disassembled_code);
    return 0;
}
