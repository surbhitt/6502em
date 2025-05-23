#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void report_alloc_failure(char*** tokens) {
    if (*tokens == NULL) {
        printf("Failed to allocated enough memory to store tokens");
        exit(1);
    }
}

void split_on_delim(char* text, char delim, char*** tokens, int* tokens_count) {
    *tokens_count = 0;
    int max_tokens = 10;
    *tokens = malloc(max_tokens * sizeof(char*));

    report_alloc_failure(tokens);

    char* token = strtok(text, &delim);
    while (token != NULL) {
        if (*tokens_count >= max_tokens) {
            max_tokens *= 2;
            *tokens = realloc(*tokens, max_tokens * sizeof(char*));
            report_alloc_failure(tokens);
        }

        (*tokens)[*tokens_count] = token;
        (*tokens_count)++;

        token = strtok(NULL, &delim);
    }
}

void strip(char* text, char char_to_strip) {
    int i = strlen(text) - 1;
    while (i >= 0 && text[i] == char_to_strip) {
        i--;
    }
    text[i + 1] = '\0';
}
