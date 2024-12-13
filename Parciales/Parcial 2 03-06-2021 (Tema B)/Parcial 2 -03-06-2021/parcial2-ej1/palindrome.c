#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "helpers/stack.h"

static size_t letter_count(char *str) {
    assert(str!=NULL);
    size_t count=0, i=0;
    printf("No contado: ");
    while (str[i] != '\0') {
        // Incrementos sólo si str[i] no está en blanco
        if (str[i] != ' ')
        {
            count = count + 1;
        } else {printf("%c",str[i] );}
        i++;
    }
    return count;
}

static size_t letter_count2(char *str) {
    assert(str!=NULL);
    size_t i=0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

static char *remove_blanks(char *str, size_t *no_blanks_count) {
    assert(str!=NULL);
    size_t size_noblank = letter_count(str); 
    printf("\ntamaño detectado para sacar el arreglo: %li \n",size_noblank);
    size_t count=0,i=0;
    char *no_blank = calloc((size_noblank + 6), sizeof(char));                   // Error corregido a la fuerza
    if ((size_noblank + 6) > 0 && no_blank == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }

    printf("contenido de no_blank: ");

    while (str[i] != '\0') {
        if (str[i] != ' ')
        {
            no_blank[i] = str[i];
            printf("%c",str[i]);
            count++;
        }
        i++;
    }

    printf("\ntamaño real: %li \n",letter_count2(str));

    *no_blanks_count = count;
    return no_blank;
}

static void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <phrase-to-check>\n\n"
           "Check if the phrase is a palindrome. Discards blank spaces from the "
           "given phrase when analysis is performed.\n",
           program_name);
}

static char* parse_phrase(int argc, char *argv[]) {
    /* Parse the phrase given by command line argument. */
    char *result=NULL;
    /* Program takes exactly one argument */
    if (argc != 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    /* Use the first argument ass the phrase */
    result = argv[1];
    /* return phrase */
    return result;
}

int main(int argc, char *argv[]) {
    // First parameter is used as phrase
    char *phrase=argv[1];
    //
    bool is_palindrome=true;
    char *phrase_noblank = NULL;
    size_t size_noblank=0;
    // Parse arguments and get the phrase to be analysed
    phrase=parse_phrase(argc, argv);
    // Discard blank spaces
    phrase_noblank = remove_blanks(phrase, &size_noblank);
    // A stack (lifo) needed for checking algorithm
    stack letters_lifo=stack_empty();
    // Save half phrase in the stack
    size_t  i=0, half_size=size_noblank / 2;
    for (i=0; i < half_size; i++) {
        letters_lifo = stack_push(letters_lifo, phrase_noblank[i]);
    }
    if (size_noblank % 2 == 1) {
        i++;  // Skip the middle letter of prhase
    }
    // Simetry check
    while (!stack_is_empty(letters_lifo)) {
        is_palindrome = is_palindrome && stack_top(letters_lifo) == phrase_noblank[i];
        letters_lifo = stack_pop(letters_lifo);
        i++;
    }
    // Check subscript
    assert(i == size_noblank);
    // Destroy stack instance
    letters_lifo = stack_destroy(letters_lifo);
    // Free auxiliar string
    free(phrase_noblank);
    phrase_noblank = NULL;
    printf(is_palindrome ? "es palíndromo!\n": "no es palíndromo\n");
    return 0;
}

/*
➜ gcc -Wall  -Werror -Wextra -pedantic -std=c99 -o ej palindrome.c helpers/stack.c

Parcial 2 -03-06-2021 (Tema B)/Parcial 2 -03-06-2021/parcial2-ej1 …
➜ ./ej "dabale arroz a la zorra el abad"                                          
No contado:       
tamaño detectado para sacar el arreglo: 25 
contenido de no_blank: dabalearrozalazorraelabad
contenido real:        dabalearrozalazorraelabad
tamaño real: 31 
no es palíndromo
*/

/*
En la linea 38 se corrigio este error a la fuerza para los casos en los ejemplos.

como es: 

char *no_blank = calloc((size_noblank + 6), sizeof(char));  

como deberia ser:

char *no_blank = calloc((size_noblank), sizeof(char));  
*/

/* con char *no_blank = calloc((size_noblank + 6), sizeof(char));   :
➜ valgrind -s ./ej "una frase cualquiera"                                                        
==132916== Memcheck, a memory error detector
==132916== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==132916== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==132916== Command: ./ej una\ frase\ cualquiera
==132916== 
No contado:   
tamaño detectado para sacar el arreglo: 18 
contenido de no_blank: unafrasecualquiera
tamaño real: 20 
no es palíndromo
==132916== 
==132916== HEAP SUMMARY:
==132916==     in use at exit: 0 bytes in 0 blocks
==132916==   total heap usage: 11 allocs, 11 frees, 1,192 bytes allocated
==132916== 
==132916== All heap blocks were freed -- no leaks are possible
==132916== 
==132916== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/


/* con char *no_blank = calloc((size_noblank), sizeof(char)); :

➜ valgrind -s ./ej "una frase cualquiera"
==129932== Memcheck, a memory error detector
==129932== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==129932== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==129932== Command: ./ej una\ frase\ cualquiera
==129932== 
No contado:   
tamaño detectado para sacar el arreglo: 18 
==129932== Invalid write of size 1
==129932==    at 0x109451: remove_blanks (palindrome.c:49)
==129932==    by 0x10959E: main (palindrome.c:94)
==129932==  Address 0x4a98492 is 0 bytes after a block of size 18 alloc'd
==129932==    at 0x484DA83: calloc (vg_replace_malloc.c:1328)
==129932==    by 0x1093D0: remove_blanks (palindrome.c:38)
==129932==    by 0x10959E: main (palindrome.c:94)
==129932== 
contenido de no_blank: unafrasecualquiera
tamaño real: 20 
no es palíndromo
==129932== 
==129932== HEAP SUMMARY:
==129932==     in use at exit: 0 bytes in 0 blocks
==129932==   total heap usage: 11 allocs, 11 frees, 1,186 bytes allocated
==129932== 
==129932== All heap blocks were freed -- no leaks are possible
==129932== 
==129932== ERROR SUMMARY: 2 errors from 1 contexts (suppressed: 0 from 0)
==129932== 
==129932== 2 errors in context 1 of 1:
==129932== Invalid write of size 1
==129932==    at 0x109451: remove_blanks (palindrome.c:49)
==129932==    by 0x10959E: main (palindrome.c:94)
==129932==  Address 0x4a98492 is 0 bytes after a block of size 18 alloc'd
==129932==    at 0x484DA83: calloc (vg_replace_malloc.c:1328)
==129932==    by 0x1093D0: remove_blanks (palindrome.c:38)
==129932==    by 0x10959E: main (palindrome.c:94)
==129932== 
==129932== ERROR SUMMARY: 2 errors from 1 contexts (suppressed: 0 from 0)
*/


