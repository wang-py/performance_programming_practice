#include <stdio.h>
#include <stdlib.h>

unsigned char* initialize_buffer(unsigned char* buffer, int buffer_size);
char hex_to_bin(char hex);
void decode_assembly(unsigned char* buffer);
void delete_buffer(unsigned char* buffer);

unsigned char* initialize_buffer(unsigned char* buffer, int buffer_size) {
    buffer = (unsigned char*)malloc(sizeof(unsigned char) * buffer_size);
    return buffer;
}

char hex_to_bin(char hex) {

}

void decode_assembly(unsigned char* buffer) {
    printf("bits 16\n\n");
    int i = 0;
    while (buffer[i + 1] != 0) {
        printf("%x%x\n", buffer[i], buffer[i + 1]);
        i += 2;
    }
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
    int buffer_size = 64;
    printf("initializing buffer of %d bytes...\n", buffer_size);
    buffer = initialize_buffer(buffer, buffer_size);
    fread(buffer, buffer_size, 1, assembly_ptr);
    decode_assembly(buffer);
    printf("deleting buffer...\n");
    delete_buffer(buffer);
    
    return 0;
}
