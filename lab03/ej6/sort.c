/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    bool x_antes_que_y = (*x).rank <= (*y).rank;
    return x_antes_que_y;
}



bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

void swap (player_t a[], unsigned int i, unsigned int j) {
    player_t aux = a[i];
    player_t *p = &a[i];
    *p = a[j];
    p = &a[j];
    *p = aux;
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int i,j,ppiv;
    ppiv = izq;
    i = izq+1u;
    j = der;
    while (i <= j)
    {
        if (goes_before(a[i], a[ppiv]))
        {
            i = i+1u;
        }
        else if (goes_before(a[ppiv], a[j]))
        {
            j = j-1u;
        }
        else //if (goes_before(a[ppiv], a[i]) && goes_before(a[j] , a[ppiv]))
        {
            swap(a,i,j);
            i = i+1u;
            j = j-1u;
        }
    }
    swap(a,ppiv,j);
    return j;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    ppiv = izq;
    if (izq < der)
    {
        ppiv = partition(a,izq,der);
        quick_sort_rec(a,izq,(ppiv == 0u) ? 0u : ppiv - 1u);
        quick_sort_rec(a,ppiv+1,der);
    }
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}

