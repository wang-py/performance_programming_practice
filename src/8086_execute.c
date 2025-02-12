#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int pid = fork();
    printf("the pid is %d\n", pid);
    printf("the argc is %d\n", argc);
    printf("the argv is %s\n", *argv);

    return 0;
}
