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
    if (argv < 2) {
        printf("Usage: ./8086_disassembler assembly_bin\n");
        return 1;
    }

    printf("number of arguments: %d\n", argv);
    printf("arguments:\n");
    for (int i = 0; i < argv; i++) {
        printf("%s ", argc[i]);
    }
    printf("\n");

    FILE* assembly_ptr;
    assembly_ptr = fopen(argc[1], "rb");

    unsigned char* buffer;
    printf("initializing buffer...\n");
    buffer = initialize_buffer(buffer);
    fread(buffer, sizeof(buffer), 1, assembly_ptr);
    printf("deleting buffer...\n");
    delete_buffer(buffer);
    
    return 0;
}
