#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */
#include <assert.h>  /* assert()        */

static
void show_pair(pair_t p) {
    printf("(%d, %d)\n", p.fst, p.snd);
}


int main(void) {
    pair_t p, q;
    // Nuevo par p
    p = pair_new(3, 4);
    //POS: {p --> (x, y)}
    assert(p.fst == 3 && p.snd == 4);
    // Se muestra el par por pantalla
    printf("p = ");
    show_pair(p);
    // Nuevo para q con elementos de p intercambiados
    q = pair_swapped(p);
    // POS: {pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)}
    assert(q.fst == p.snd && q.snd == p.fst);
    // Se muestra q
    printf("q = ");
    show_pair(q);
    // Se destruyen p y q
    p = pair_destroy(p);
    q = pair_destroy(q);
    return EXIT_SUCCESS;
}
