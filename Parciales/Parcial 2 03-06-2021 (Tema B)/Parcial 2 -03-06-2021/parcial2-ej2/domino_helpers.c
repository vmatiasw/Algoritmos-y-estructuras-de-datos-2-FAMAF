#include <stdio.h>
#include <assert.h>
#include "domino.h"

domino scan_domino(void) {
    int up, down, readed;
    printf("Ingrese los valores de un domino (up:down): ");
    readed = scanf("%d:%d", &up, &down);
    return readed == 2 ? domino_new(up, down) : NULL;
}

unsigned int chain_dominoes(domino pieces[], unsigned int size) {
    bool is_match=true;
    unsigned int match_count=1;  // Counts how many matches were made
    unsigned int i=0;
    assert(size > 0 && domino_is_double(pieces[0]));
    while (is_match && i + 1 < size) {
        domino p1=pieces[i], p2=pieces[i+1];

        is_match = domino_matches(p1,p2);
        if (!is_match) // si no son iguales de un lado pruebo dando vuelta p2
        {
            is_match = domino_matches(p1,domino_flip(p2));
        }
        
        match_count += is_match;
        i++;
    }
    assert(match_count <= size);
    return match_count;
}

// Se puede implementar ademas que si con uno no machea, pruebe con el siguiente y asi pero eso no lo pide la consigna.