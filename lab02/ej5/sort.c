#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"

static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int i,j,ppiv;
    ppiv = izq;
    i = izq+1u;
    j = der;
    while (i <= j)
    {
        if (goes_before(a[i], a[ppiv]) || a[i] == a[ppiv])
        {
            i = i+1u;
        }
        else if (goes_before(a[ppiv], a[j]) || a[j] == a[ppiv])
        {
            j = j-1u;
        }
        else
        {
            swap(a,i,j);
            i = i + 1u;
            j = j - 1u;
        }
    }
    swap(a,ppiv,j);
    return j;
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    if (izq < der)
    {
        ppiv = partition(a,izq,der);
        quick_sort_rec(a,izq,(ppiv == 0u) ? 0u : ppiv - 1u);
        quick_sort_rec(a,ppiv+1,der);
    }
}

void quick_sort(fixstring a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1u);
}