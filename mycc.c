#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mycc.h"

Token *token;
char *user_input;

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Error: args count\n");
        return 1;
    } 
    user_input = argv[1];
    token = tokenize(user_input);
    Node *node = expr();

    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");
    gen(node);

    printf("  pop rax\n");
    printf("  ret\n");
    return 0;
}