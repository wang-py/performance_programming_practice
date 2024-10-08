#include <stdio.h>
#include <stdlib.h>
#define OPCODE_BITS 252
#define OPCODE_BITS_IMMEDIATE 176
#define DIRECTION_BIT 2
#define WIDTH_BIT 1
#define WIDTH_BIT_IMMEDIATE 8
#define SRC_BITS 56
#define DES_BITS 7
#define REG_IMMEDIATE_MASK 7
#define IMMEDIATE_MODE 1
#define MOD_BITS 3

unsigned char* initialize_buffer(unsigned char* buffer, int buffer_size);
int is_wide(unsigned char byte_1);
int is_wide_immediate(unsigned char byte_1);
void decode_reg(unsigned char reg);
void decode_reg_wide(unsigned char reg);
void decode_effective_address_calc(unsigned char rm);
int decode_byte_1(unsigned char byte_1);
void decode_byte_2(unsigned char byte_2, int width);
void decode_byte_2_i(unsigned char byte_2, int width);
void decode_assembly(unsigned char* buffer, int inst_size);
void delete_buffer(unsigned char* buffer);
int check_mod(unsigned char byte_2);
int check_rm(unsigned char byte_2);

unsigned char* initialize_buffer(unsigned char* buffer, int buffer_size) {
    buffer = (unsigned char*)malloc(sizeof(unsigned char) * buffer_size);
    return buffer;
}


int is_src_des(unsigned char instruction) {
    return instruction & DIRECTION_BIT;
}

int decode_byte_1(unsigned char byte_1) {
    int opcode = byte_1 & OPCODE_BITS;
    int opcode_immediate = byte_1 & OPCODE_BITS_IMMEDIATE;
    int retval = 0;
    switch (opcode_immediate) {
        case 176:
            printf("mov ");
            if ((byte_1 & WIDTH_BIT_IMMEDIATE) == WIDTH_BIT_IMMEDIATE) {
                decode_reg_wide(byte_1 & REG_IMMEDIATE_MASK);
            } else {
                decode_reg(byte_1 & REG_IMMEDIATE_MASK);
            }
            retval = IMMEDIATE_MODE;
            break;
    }
    switch (opcode) {
        case 136:
            printf("mov ");
            break;
    }

    return retval;
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

void decode_effective_address_calc(unsigned char rm) {
    switch (rm) {
        case 0:
            printf("[bx + si]\n");
            break;
        case 1:
            printf("[bx + di]\n");
            break;
        case 2:
            printf("[bp + si]\n");
            break;
        case 3:
            printf("[bp + di]\n");
            break;
        case 4:
            printf("[si]\n");
            break;
        case 5:
            printf("[di]\n");
            break;
        case 6:
            printf("[bp]\n");
            break;
        case 7:
            printf("[bx]\n");
            break;
    }
}

void decode_byte_2(unsigned char byte_2, int width) {
    unsigned char mod = (byte_2 >> 6) & MOD_BITS;
    unsigned char src = byte_2 & SRC_BITS;
    unsigned char des = byte_2 & DES_BITS;

    switch (mod) {
        case 0:
            decode_effective_address_calc(des);
            break;
        case 1:
            decode_effective_address_calc(des);
            break;
        case 2:
            decode_effective_address_calc(des);
            break;
        case 3:
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
            break;
    }

}

// decode byte 2 in immediate mode
void decode_byte_2_i(unsigned char byte_2, int width) {
    signed char data_8 = 0;
    signed short data_16 = 0;

    if (width == 1) {
        data_16 = (signed short) byte_2;
        printf(", ");
        printf("%hi", data_16);
        printf("\n");
    } else if (width == 0) {
        data_8 = (signed char) byte_2;
        printf(", ");
        printf("%d", data_8);
        printf("\n");
    }
}

int is_wide(unsigned char byte_1) {

    return byte_1 & WIDTH_BIT;
}

int is_wide_immediate(unsigned char byte_1) {
    if ((byte_1 & WIDTH_BIT_IMMEDIATE) == WIDTH_BIT_IMMEDIATE) {
        return 1;
    }

    return 0;
}

void decode_assembly(unsigned char* buffer, int inst_size) {
    printf("bits 16\n\n");
    int i = 0;
    int mode = 0;
    int width = 0;
    int width_immediate = 0;
    while (i < inst_size) {
        // printf("%x %x\n", buffer[i], buffer[i + 1]);
        width = is_wide(buffer[i]);
        mode = decode_byte_1(buffer[i]);
        if (mode == IMMEDIATE_MODE) {
            width_immediate = is_wide_immediate(buffer[i]);
            decode_byte_2_i(buffer[i + 1], width_immediate);
            if (width_immediate == 1) {
                i += 3;
            } else {
                i += 2;
            }
        } else {
            decode_byte_2(buffer[i + 1], width);
            i += 2;
        }
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
    fseek(assembly_ptr, 0L, SEEK_END);
    int inst_size = ftell(assembly_ptr);
    rewind(assembly_ptr);

    unsigned char* buffer;
    int buffer_size = inst_size;
    // printf("initializing buffer of %d bytes...\n", buffer_size);
    buffer = initialize_buffer(buffer, buffer_size);
    fread(buffer, buffer_size, 1, assembly_ptr);
    decode_assembly(buffer, inst_size);
    // printf("deleting buffer...\n");
    delete_buffer(buffer);
    
    return 0;
}
