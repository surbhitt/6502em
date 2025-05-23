#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE;
typedef uint16_t WORD;

#define MEM_SIZE 64 * 1024
BYTE memory[MEM_SIZE];

typedef struct Emulator {
    // registers
    BYTE a, x, y;
    // pc: program counter
    // sp: stack pointer
    WORD pc, sp;
    // status flag
    // N V . B D I Z C
    // Negative, Overflow, unused, Break, Decimal, IRQ disable, Zero, Carry
    BYTE sf;
} Emulator;

void update_status_flag(BYTE* sf, const char* flags) {
    while (*flags) {
        switch (*(flags++)) {
            case 'N':
                *sf = *sf | 0b10000000;
                break;
            case 'V':
                *sf = *sf | 0b01000000;
                break;
            case 'B':
                *sf = *sf | 0b00010000;
                break;
            case 'D':
                *sf = *sf | 0b00001000;
                break;
            case 'I':
                *sf = *sf | 0b00000100;
                break;
            case 'Z':
                *sf = *sf | 0b00000010;
                break;
            case 'C':
                *sf = *sf | 0b00000001;
                break;
            case 'R':
                *sf = *sf & 0b00000000;
                break;
            default:
                printf("UNREACHABLE");
                exit(0);
        }
    }
}

void reset_routine(Emulator* em) {
    em->a = 0;
    em->x = 0;
    em->y = 0;
    update_status_flag(&em->sf, "R");
    em->pc = 0xfffc;
    em->sp = 0x0100;
}

int ready(Emulator* em) {
    reset_routine(em);
    memset(memory, 0, sizeof(memory));
    return 1;
}

int hex_to_int(const char* str) {
    // convert the val from hex to int
    // after removing the $ and #
    if (str[0] == '#')
        str++;
    if (str[0] == '$')
        str++;
    return (int)strtol(str, NULL, 16);
}

bool is_oprnd_val(char val[4]) {
    // check for the # symbol that indicates the operand is an absolute value
    // else it is a memory location
    if (val[0] == '#')
        return true;
    return false;
}

// -----------------------------------------------------------------------
// -------------------------INSTRUCTIONS----BEGIN-------------------------
// -----------------------------------------------------------------------
void LDA(Emulator* em, char* operand) {
    int operand_val = hex_to_int(operand);
    em->a = operand_val;
}

void STA(Emulator* em, char* operand) {
    int address = hex_to_int(operand);
    memory[address] = em->a;
}
void TAX(Emulator* em) {
    em->x = em->a;
}
void INX(Emulator* em) {
    em->x++;
}
void ADC(Emulator* em, char* operand) {
    int operand_val = hex_to_int(operand);
    em->a += operand_val;
}
void BRK() {
    // TODO: some kind of exit
    printf("\n== DONE ==\n");
}
// -----------------------------------------------------------------------
// --------------------------INSTRUCTIONS----END--------------------------
// -----------------------------------------------------------------------

void assemble_line(Emulator* em, char* cmd_tokens[], int cmd_tokens_count) {
    char* operator= cmd_tokens[0];
    char* operand = NULL;
    if (cmd_tokens_count > 1)
        operand = cmd_tokens[1];

    if (strcmp(operator, "LDA") == 0) {
        LDA(em, operand);
    } else if (strcmp(operator, "STA") == 0) {
        STA(em, operand);
    } else if (strcmp(operator, "TAX") == 0) {
        TAX(em);
    } else if (strcmp(operator, "INX") == 0) {
        INX(em);
    } else if (strcmp(operator, "ADC") == 0) {
        ADC(em, operand);
    } else if (strcmp(operator, "BRK") == 0) {
        BRK();
    } else {
        printf("[ERR] Unrecognised operator: %s", operator);
    }
}
