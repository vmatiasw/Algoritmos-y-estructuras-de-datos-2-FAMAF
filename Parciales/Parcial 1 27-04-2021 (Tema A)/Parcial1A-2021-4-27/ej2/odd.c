#include <stdbool.h>

#include "odd.h"

bool is_odd_sorted(int array[], unsigned int length) {
    bool ordenado = true;
    unsigned int i = 3;
    int aux = array[1];
    while (i < length)
    {
        if (array[i] >= aux)
        {
            ordenado = false;
        }
        aux = array[i];
        i = i+2;
    }
    return ordenado;
}


