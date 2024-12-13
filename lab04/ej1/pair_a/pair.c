
#include "pair.h"

/*
spec Pair where

constructors

    fun new(in x : int, in y : int) ret p : Pair
    {- crea un par con componentes (x, y) -}
    POS: {p --> (x, y)}
*/
pair_t pair_new(int x, int y) {
    pair_t q;
    q.fst = x;
    q.snd = y;
    return q;
}


/*
destroy
  
  
    proc destroy(in/out p : Pair)
    {- libera memoria en caso que sea necesario -}
*/
pair_t pair_destroy(pair_t p) {
    return NULL;
}


/*
operations

    PRE: {p --> (x, y)}
    fun first(in p : Pair) ret x : int
    {- devuelve el primer componente del par-}
    POS: {fst == x}
*/

int pair_first(pair_t p){
    int elem1 = p.fst;
    return elem1;
}

/*
    PRE: {p --> (x, y)}
    fun second(in p : Pair) ret y : int
    {- devuelve el segundo componente del par-}
    POS: {snd == y}

*/
int pair_second(pair_t p){
    int elem2 = p.snd;
    return elem2;
}


/*
    PRE: {p --> (x, y)}
    fun swapped(in p : Pair) ret s : Pair
    {- devuelve un nuevo par con los componentes de p intercambiados -}
    POS: {pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)}
*/
pair_t pair_swapped(pair_t p){
    pair_t q;
    q.fst = p.snd;
    q.snd = p.fst;
    return q;
}

