#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
    fgets(user_input, sizeof(user_input), stdin);

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    return EXIT_SUCCESS;
}

/*
Ingrese su nombre y apellido: matias viola
Te damos la bienvenida matias a este maravilloso programa!

error de scanf: termina en los espacios. 
*/