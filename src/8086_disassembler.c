#include <stdio.h>
#include <stdlib.h>
#define OPCODE_BITS 252
#define DIRECTION_BIT 2
#define WIDTH_BIT 1
#define SRC_BITS 56
#define DES_BITS 7

unsigned char* initialize_buffer(unsigned char* buffer, int buffer_size);
int is_wide(unsigned char byte_1);
void decode_byte_1(unsigned char byte_1);
void decode_byte_2(unsigned char byte_2, int width);
void decode_assembly(unsigned char* buffer);
void delete_buffer(unsigned char* buffer);

unsigned char* initialize_buffer(unsigned char* buffer, int buffer_size) {
    buffer = (unsigned char*)malloc(sizeof(unsigned char) * buffer_size);
    return buffer;
}


int is_src_des(unsigned char instruction) {
    return instruction & DIRECTION_BIT;
}

void decode_byte_1(unsigned char byte_1) {
    int opcode = byte_1 & OPCODE_BITS;
    switch (opcode) {
        case 136:
            printf("mov ");
            break;
    }
}

void decode_reg_wide(unsigned char reg) {
    switch (reg) {
        case 0:
            printf("ax");
            break;
        case 1:
            printf("cx");
            break;
        case 2:
            printf("dx");
            break;
        case 3:
            printf("bx");
            break;
        case 4:
            printf("sp");
            break;
        case 5:
            printf("bp");
            break;
        case 6:
            printf("si");
            break;
        case 7:
            printf("di");
            break;
    }
}

void decode_reg(unsigned char reg) {
    switch (reg) {
        case 0:
            printf("al");
            break;
        case 1:
            printf("cl");
            break;
        case 2:
            printf("dl");
            break;
        case 3:
            printf("bl");
            break;
        case 4:
            printf("ah");
            break;
        case 5:
            printf("ch");
            break;
        case 6:
            printf("dh");
            break;
        case 7:
            printf("bh");
            break;
    }
}

void decode_byte_2(unsigned char byte_2, int width) {
    unsigned char src = byte_2 & SRC_BITS;
    unsigned char des = byte_2 & DES_BITS;

    if (width == 1) {
        decode_reg_wide(des);
        printf(", ");
        decode_reg_wide(src >> 3);
        printf("\n");
    } else if (width == 0) {
        decode_reg(des);
        printf(", ");
        decode_reg(src >> 3);
        printf("\n");
    }
}

int is_wide(unsigned char byte_1) {
    return byte_1 & WIDTH_BIT;
}

void decode_assembly(unsigned char* buffer) {
    printf("bits 16\n\n");
    int i = 0;
    while (buffer[i + 1] != 0) {
        // printf("%x%x\n", buffer[i], buffer[i + 1]);
        int width = is_wide(buffer[i]);
        decode_byte_1(buffer[i]);
        decode_byte_2(buffer[i + 1], width);
        i += 2;
    }
    // printf("is_src_des: %d\n", is_src_des(buffer[0]));
}

void delete_buffer(unsigned char* buffer) {
    free(buffer);
}

int main(int argv, char* argc[]) {
    if (argv < 2) {
        printf("Usage: ./8086_disassembler assembly_bin\n");
        return 1;
    }

    // printf("number of arguments: %d\n", argv);
    // printf("arguments:\n");

    FILE* assembly_ptr;
    assembly_ptr = fopen(argc[1], "rb");

    unsigned char* buffer;
    int buffer_size = 64;
    // printf("initializing buffer of %d bytes...\n", buffer_size);
    buffer = initialize_buffer(buffer, buffer_size);
    fread(buffer, buffer_size, 1, assembly_ptr);
    decode_assembly(buffer);
    // printf("deleting buffer...\n");
    delete_buffer(buffer);
    
    return 0;
}
