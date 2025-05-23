#include <stdbool.h>
#include <stdio.h>
#include "emulator.c"
#include "utils.c"

typedef char Cmd[100];

void print_regs_n_mem(Emulator em) {
    printf("a=%d x=%d y=%d ", em.a, em.x, em.y);
    for (int i = 510; i < 520; i++) {
        printf("%d ", memory[i]);
    }
}

int main(int argc, char** argv) {
    Emulator em;
    // TODO exit if ready fails
    int ok = ready(&em);

    if (argc < 2) {
        printf("no file name provided");
        return 1;
    }
    // char cmd[100];
    // fgets(cmd, sizeof(cmd), stdin);

    const char* filename = argv[1];
    FILE* file = fopen(filename, "r");

    if (!file) {
        perror("Could not open file");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        // printf("%s", buffer);
        char** cmd_tokens = NULL;
        int cmd_tokens_count = 0;

        strip(buffer, '\n');
        strip(buffer, ' ');
        split_on_delim(buffer, ' ', &cmd_tokens, &cmd_tokens_count);
        assemble_line(&em, cmd_tokens, cmd_tokens_count);

        free(cmd_tokens);
    }

    print_regs_n_mem(em);
    return 0;
}
