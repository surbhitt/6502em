#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "emulator.c"

typedef char Cmd[100];
CPU cpu;

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

void assemble(Cmd cmd) {
    char* oprtr = strtok(cmd, " ");
    if (strcmp(oprtr, "LDA") == 0) {
        // instruction is LDA
        // move operand value to a register
        char* oprnd = strtok(NULL, " ");
        if (is_oprnd_val(oprnd)) {
            cpu.a += hex_to_int(oprnd);
        } else {
            // TODO
            printf("TO BE IMPLEMENTED\n");
        }
    } else if (strcmp(oprtr, "STA") == 0) {
        // instruction is STA
        // move a register value to operand(memory location)
        char* oprnd = strtok(NULL, " ");
        if (is_oprnd_val(oprnd)) {
            assert(1 == 0, "Operand with STA should be a memory location")
        } else {
            // TODO
            printf("TO BE IMPLEMENTED\n");
        }
    }
}

void print_cpu_reg(CPU cpu) {
    printf("a = %d\n", cpu.a);
}

int main(void) {
    int ok = connect(cpu);
    char cmd[100];
    fgets(cmd, sizeof(cmd), stdin);
    assemble(cmd);
    print_cpu_reg(cpu);
    return 0;
}
