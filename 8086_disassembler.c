#include <stdio.h>
#include <stdlib.h>

unsigned char* initialize_buffer(unsigned char* buffer);
void delete_buffer(unsigned char* buffer);

unsigned char* initialize_buffer(unsigned char* buffer) {
    buffer = (unsigned char*)malloc(sizeof(unsigned char) * 32);
    return buffer;
}

void delete_buffer(unsigned char* buffer) {
    free(buffer);
}

int main(int argv, char* argc[]) {
    printf("number of arguments: %d\n", argv);
    printf("arguments:\n");
    for (int i = 0; i < argv; i++) {
        printf("%s ", argc[i]);
    }
    printf("\n");

    unsigned char* buffer;
    printf("initializing buffer...\n");
    buffer = initialize_buffer(buffer);
    printf("deleting buffer...\n");
    delete_buffer(buffer);
    
    return 0;
}
