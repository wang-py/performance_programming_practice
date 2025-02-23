#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

static char* sub_process_name = "../sim86/sim86";

int call_disassembler(char* argv[]) {
    int pid = fork();
    if (pid == -1) {
        printf("Failed to call fork()\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        argv[0] = sub_process_name;
        execv(argv[0], argv);
        perror("execv");
        exit(2);
    }

    int status;
    int wait_result;
    while ((wait_result = wait(&status)) != -1) {
        printf("Process %lu returned result: %d\n", wait_result, status);
    }

    printf("All children have finished.\n");
    return 0;
}

int main(int argc, char* argv[]) {
    call_disassembler(argv);
    return 0;
}
