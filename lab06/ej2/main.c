#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "string.h"

#define N_WORDS 5

int main(void) {
    char *words[N_WORDS]={"hola", "mundo", "auto","automovil", "automovil"};

    printf("\nProbando string_less()\n"
           "----------------------\n\n");

    for (int i=0; i < N_WORDS - 1; i++) {
        printf("%s < %s = %s\n",
                                words[i],
                                words[i+1],
                                string_less(string_create(words[i]),string_create(words[i+1])) ? "True" : "False");
    }
    printf("\n\nProbando string_eq()\n"
           "--------------------\n\n");

    for (int i=0; i < N_WORDS - 1; i++) {
        printf("%s == %s = %s\n",
                                words[i],
                                words[i+1],
                                string_eq(string_create(words[i]),string_create(words[i+1])) ? "True" : "False");
    }
    return EXIT_SUCCESS;
}
