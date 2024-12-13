#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */
#include <assert.h>  /* assert()        */

struct s_pair_t {
    elem fst;
    elem snd;
};

static
void show_pair(pair_t p) {
    printf("(%d, %d)\n", pair_first(p), pair_second(p));
}

int main(void) {
    pair_t p, q;
    // Nuevo par p
    p = pair_new(3, 4);
    //POS: {p --> (x, y)}
    assert(pair_first(p) == 3 && pair_second(p) == 4);
    // Se muestra el par por pantalla
    printf("p = ");
    show_pair(p);
    // Nuevo para q con elementos de p intercambiados
    q = pair_swapped(p);
    // POS: {pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)}
    assert(pair_first(q)== pair_second(p) && pair_second(q) == pair_first(p));
    // Se muestra q
    printf("q = ");
    show_pair(q);
    // Se destruyen p y q
    p = pair_destroy(p);
    q = pair_destroy(q);
    return EXIT_SUCCESS;
}

