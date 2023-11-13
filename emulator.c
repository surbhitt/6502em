#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define MEM_SIZE 64*1024

typedef uint8_t BYTE; 
typedef uint16_t WORD;

// does it make sense for the memory to be outside the cpu??
BYTE memory[MEM_SIZE];

typedef struct CPU {
    // registers
    BYTE a, x, y;
    // PC: program counter
    // SP: stack pointer
    WORD prg_cntr, stk_pntr;
    // status flag
    // N V . B D I Z C
    // Negative, Overflow, unused, Break, Decimal, IRQ disable, Zero, Carry
    BYTE flag_reg;
} CPU;

void update_status_flag(BYTE*, const char*);

void reset_routine(CPU cpu) {
    cpu.a = 0;
    cpu.x = 0;
    cpu.y = 0;
    update_status_flag(&cpu.flag_reg, "R");
    cpu.prg_cntr = 0xfffc;
    cpu.stk_pntr = 0x0100;
}

void update_status_flag(BYTE* flag_reg, const char* flags) {
    while (*flags) {
        switch (*(flags++)) { 
            case 'N':
                *flag_reg = *flag_reg | 0b10000000; break;
            case 'V':
                *flag_reg = *flag_reg | 0b01000000; break;
            case 'B':
                *flag_reg = *flag_reg | 0b00010000; break;
            case 'D':
                *flag_reg = *flag_reg | 0b00001000; break;
            case 'I':
                *flag_reg = *flag_reg | 0b00000100; break;
            case 'Z':
                *flag_reg = *flag_reg | 0b00000010; break;
            case 'C':
                *flag_reg = *flag_reg | 0b00000001; break;
            case 'R':
                *flag_reg = *flag_reg & 0b00000000; break;
            default:
                printf("UNREACHABLE"); exit(0);
        }
    }
}

int connect(CPU cpu) {
    // should this return a reference to a cpy object 
    // instead of taking an object
    reset_routine(cpu);
    memset(memory, 0, sizeof(memory));
    // create a try catch to catch for error while reset
    return 1;
}

int disconnect(CPU cpu) {
    assert("TOOD: --");
    // manage status code
    return 1;
}

int main(void) {
    CPU cpu;
    int ret = connect(cpu);
    if (ret) {
        printf("\x1b[32m[Success]\x1b[39m connected\n"); 
    } else {
        printf("\x1b[31m[Failed]\x1b[39m during connection with err %d\n", ret);
        exit(0);
    }
    /* printf("this is the value before => %d\n", cpu.flag_reg); */
    /* update_status_flag(&cpu.flag_reg, "IZC"); */
    /* printf("this is the value after => %d\n", cpu.flag_reg); */
    disconnect(cpu);
}
