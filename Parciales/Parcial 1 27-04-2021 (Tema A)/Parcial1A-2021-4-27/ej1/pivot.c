#include <stdbool.h>

#include "pivot.h"


bool is_pivot(int array[], unsigned int length, unsigned int piv) {
    bool espivot = true;
    unsigned int i = 0;
    while (espivot && i<length)
    {
        if ((i < piv && array[i] > array[piv]) || (i > piv && array[i] < array[piv]))
        {
            espivot = false;
        }       
        i = i+1;
    }
    return espivot;
}

