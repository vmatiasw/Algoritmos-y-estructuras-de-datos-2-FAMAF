/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include "helpers.h"
#include "sort.h"
#include "song.h"


bool goes_before(song_t s1, song_t s2) {
    return s1.seconds <= s2.seconds;
}

bool array_is_sorted(song_t playlist[], unsigned int length) {
    unsigned int i = 0u;
    bool sorted = true;
    while (i + 1 < length && sorted) {
        sorted = goes_before(playlist[i], playlist[i + 1]);
        i = i + 1;
    }
    return sorted;
}

bool array_is_odd_sorted(song_t playlist[], unsigned int length) {
    bool ordenado = true;
    unsigned int i = 3;
    song_t aux = playlist[1];
    while (i < length)
    {
        if (goes_before(playlist[i], aux))
        {
            ordenado = false;
        }
        aux = playlist[i];
        i = i+2;
    }
    return ordenado;
}

