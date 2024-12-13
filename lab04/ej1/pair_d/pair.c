
#include "pair.h"
#include <stdlib.h>

struct s_pair_t {
    elem fst;
    elem snd;
};

/*
spec Pair where

constructors
    fun new(in x : T, in y : T) ret p : Pair of T
    {- crea un par con componentes (x, y) -}
    POS: {p --> (x, y)}
*/
pair_t pair_new(elem x, elem y) {
    pair_t q = malloc(sizeof(pair_t));
    q->fst = x;
    q->snd = y;
    return q;
}


/*
destroy
    proc destroy(in/out p : Pair of T)
    {- libera memoria en caso que sea necesario -}
*/
pair_t pair_destroy(pair_t p) {
    free(p);
    return NULL;
}


/*
operations

    PRE: {p --> (x, y)}
    fun first(in p : Pair of T) ret x : T
    {- devuelve el primer componente del par-}
    POS: {fst == x}
*/

elem pair_first(pair_t p){
    elem elem1 = p->fst;
    return elem1;
}

/*
    PRE: {p --> (x, y)}
    fun second(in p : Pair of T) ret y : T
    {- devuelve el segundo componente del par-}
    POS: {snd == y}

*/
elem pair_second(pair_t p){
    elem elem2 = p->snd;
    return elem2;
}


/*
    PRE: {p --> (x, y)}
    fun swapped(in p : Pair of T) ret s : Pair of T
    {- devuelve un nuevo par con los componentes de p intercambiados -}
    POS: {pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)}
*/
pair_t pair_swapped(pair_t p){
    pair_t q = malloc(sizeof(pair_t));
    q->fst = p->snd;
    q->snd = p->fst;
    return q;
}

