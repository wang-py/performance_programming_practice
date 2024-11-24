#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define OPCODE_BITS 252
#define OPCODE_BITS_IMMEDIATE 176
#define WIDTH_BIT 1
#define WIDTH_BIT_IMMEDIATE 8
#define REG_BITS 7
#define RM_BITS 7
#define REG_IMMEDIATE_MASK 7
#define IMMEDIATE_MODE 1
#define MOD_BITS 3

const char* reg_list_wide[8] = {"ax", "cx", "dx", "bx",
                                "sp", "bp" , "si", "di"};

const char* reg_list[8] = {"ah", "ch", "dh", "bh",
                           "al", "cl", "dl", "bl"};

const char* rm_list_eac[8] = {"[bx + si]", "[bx + di]", "[bp + si]",
                              "[bp + di]", "si", "di", "bp", "bx"};

const char* rm_list_eac_disp[8] = {"[bx + si", "[bx + di", "[bp + si",
                                   "[bp + di", "[si", "[di", "[bp", "[bx"};

unsigned char* initialize_buffer(unsigned char* buffer, int buffer_size);
int is_wide(unsigned char byte_1);
int is_wide_immediate(unsigned char byte_1);
int get_direction_bit(unsigned char instruction);
void decode_reg_field(unsigned char reg, int width);
void decode_reg(unsigned char reg);
void decode_reg_wide(unsigned char reg);
void decode_eac(unsigned char* byte_2, unsigned char rm, unsigned char mod, int width);
void decode_effective_address_calc(unsigned char rm);
void decode_effective_address_calc_disp(unsigned char rm);
int decode_byte_1(unsigned char byte_1);
unsigned char decode_byte_2(unsigned char* byte_2, int width, int d);
void decode_byte_2_i(unsigned char* byte_2, int width);
void decode_assembly(unsigned char* buffer, int inst_size);
void delete_buffer(unsigned char* buffer);
int check_mod(unsigned char byte_2);
int check_rm(unsigned char byte_2);

unsigned char* initialize_buffer(unsigned char* buffer, int buffer_size) {
    buffer = (unsigned char*)malloc(sizeof(unsigned char) * buffer_size);
    return buffer;
}


int get_direction_bit(unsigned char instruction) {
    return (instruction >> 1) & 1;
}

int decode_byte_1(unsigned char byte_1) {
    int opcode = byte_1 & OPCODE_BITS;
    int opcode_immediate = byte_1 & OPCODE_BITS_IMMEDIATE;
    int retval = 0;
    switch (opcode_immediate) {
        case 176:
            printf("mov ");
            break;
        case 128:
            printf("add ");
            break;
        if ((byte_1 & WIDTH_BIT_IMMEDIATE) == WIDTH_BIT_IMMEDIATE) {
            decode_reg_wide(byte_1 & REG_IMMEDIATE_MASK);
        } else {
            decode_reg(byte_1 & REG_IMMEDIATE_MASK);
        }
        retval = IMMEDIATE_MODE;
    }
    switch (opcode) {
        case 0:
            printf("add ");
            break;
        case 136:
            printf("mov ");
            break;
    }

    return 0;
}

void decode_reg_wide(unsigned char reg) {
    printf("%s", reg_list_wide[reg]);
}

void decode_reg(unsigned char reg) {
    printf("%s", reg_list[reg]);
}

void decode_effective_address_calc(unsigned char rm) {
    printf("%s", rm_list_eac[rm]);
}

void decode_effective_address_calc_disp(unsigned char rm) {
    printf("%s", rm_list_eac_disp[rm]);
}
void decode_reg_field(unsigned char reg, int width) {
    if (width == 1) {
        decode_reg_wide(reg);
    } else if (width == 0) {
        decode_reg(reg);
    }
}

void decode_eac(unsigned char* byte_2, unsigned char rm, unsigned char mod, int width) {
    int8_t disp_8 = 0;
    int16_t disp_16 = 0;

    switch (mod) {
        case 0:
            decode_effective_address_calc(rm);
            break;
        case 1:
            decode_effective_address_calc_disp(rm);
            disp_8 = (int8_t)*(byte_2 + 1);
            if (disp_8 != 0) {
                printf(" + %d]", disp_8);
            } else {
                printf("]");
            }
            break;
        case 2:
            decode_effective_address_calc_disp(rm);
            disp_16 = *(int16_t*)(byte_2 + 1);
            if (disp_16 != 0) {
                printf(" + %d]", disp_16);
            } else {
                printf("]");
            }
            break;
        case 3:
            decode_reg_field(rm, width);
            break;
    }
}

unsigned char decode_byte_2(unsigned char* byte_2, int width, int d) {
    unsigned char mod = (*byte_2 >> 6) & MOD_BITS;
    unsigned char reg = (*byte_2 >> 3) & REG_BITS;
    unsigned char rm = *byte_2 & RM_BITS;
    unsigned char swap = 0;

    // check the direction of mov
    if (d == 1) {
        decode_reg_field(reg, width);
        printf(", ");
        decode_eac(byte_2, rm, mod, width);
    } else {
        decode_eac(byte_2, rm, mod, width);
        printf(", ");
        decode_reg_field(reg, width);
    }
    printf("\n");
    // printf("after swap reg: %d rm: %d d: %d\n", reg, rm, d);


    // if (width == 1) {
    //     decode_reg_wide(reg);
    //     printf("\n");
    // } else if (width == 0) {
    //     printf(", ");
    //     decode_reg(reg);
    //     printf("\n");
    // }
    return mod;
}

// decode byte 2 in immediate mode
void decode_byte_2_i(unsigned char* byte_2, int width) {
    int8_t data_8 = 0;
    int16_t data_16 = 0;

    if (width == 1) {
        data_16 = (int16_t) *byte_2;
        printf(", ");
        printf("%d", data_16);
        printf("\n");
    } else if (width == 0) {
        data_8 = (int8_t) *byte_2;
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
    unsigned char disp_mode = 0;
    int d = 0;
    // direction of mov
    while (i < inst_size) {
        // printf("%x %x\n", buffer[i], buffer[i + 1]);
        width = is_wide(buffer[i]);
        mode = decode_byte_1(buffer[i]);
        d = get_direction_bit(buffer[i]);

        if (mode == IMMEDIATE_MODE) {
            width_immediate = is_wide_immediate(buffer[i]);
            decode_byte_2_i(buffer + i + 1, width_immediate);
            if (width_immediate == 1) {
                i += 3;
            } else {
                i += 2;
            }
        } else {
            disp_mode = decode_byte_2(buffer + i + 1, width, d);
            switch (disp_mode) {
                // + D8
                case 1:
                    i += 3;
                    break;
                // + D16
                case 2:
                    i += 4;
                    break;
                default:
                    i += 2;
            }
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
