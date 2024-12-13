#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "domino.h"

struct _s_domino {
    unsigned int p_top;
    unsigned int p_bottom;
};


/* auxiliary functions for dumping */

static char mark(bool b) {
    return b ? 'O' : ' ';
}

static void dump_num(int num) {
  printf("      | %c     %c |\n",
         mark(num > 1), mark(num > 3));
  printf("      | %c  %c  %c |\n",
         mark(num > 5), mark(num % 2 == 1), mark(num > 5));
  printf("      | %c     %c |\n",
         mark(num > 3), mark(num > 1));
}

static void dump_double_num(int num) {
  printf(" --------------------- \n");
  printf(" | %c  %c  %c ", mark(num > 3), mark(num > 5), mark(num > 1));
  printf( "| %c  %c  %c |\n", mark(num > 3), mark(num > 5), mark(num > 1));

  printf(" |    %c    ", mark(num % 2 == 1));
  printf( "|    %c    |\n", mark(num % 2 == 1));

  printf(" | %c  %c  %c ", mark(num > 1), mark(num > 5), mark(num > 3));
  printf( "| %c  %c  %c |\n", mark(num > 1), mark(num > 5), mark(num > 3));
  printf(" --------------------- \n");
}

void dump(int num_up, int num_down) {
    /* Pretty dump funcion for cool visualization :) */
    if (num_up != num_down)  {
        printf("      ----------- \n");
        dump_num(num_up);
        printf("      |---------| \n");
        dump_num(num_down);
        printf("      ----------- \n");
    } else {
        dump_double_num(num_up);
    }
}

/* Representation invariant */

static bool invrep(domino p) {

    return p != NULL  &&  p->p_top <= 6  &&  p->p_bottom <= 6;
}

/* Public functions */

domino domino_new(int num_up, int num_down) {
    domino p = malloc(sizeof(struct _s_domino));
    if (p == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    p->p_top = num_up;
    p->p_bottom = num_down;
    assert(invrep(p));
    return p;
}

bool domino_is_double(domino p) {
    assert(invrep(p));
    return p->p_bottom == p->p_top;
}

bool domino_eq(domino p1, domino p2) {
    assert(invrep(p1) && invrep(p1));
    bool equals=true;

    equals = p1->p_bottom == p2->p_bottom && p1->p_top == p2->p_top;

    if (!equals) // Si no son iguales pruebo dando vuelta p2
    {
        equals = p1->p_bottom == p2->p_top && p1->p_top == p2->p_bottom;
    }
    assert(invrep(p1) && invrep(p1));
    return equals;
}

bool domino_matches(domino p_top, domino p_bottom) {
    assert(invrep(p_top) && invrep(p_bottom));
    return p_top->p_bottom == p_bottom->p_top;
}

domino domino_flip(domino p) {
    assert(invrep(p));
    unsigned int aux = p->p_bottom;

    p->p_bottom = p->p_top;
    p->p_top = aux;
    assert(invrep(p));
    return p;
}

void domino_dump(domino p) {
    assert(invrep(p));
    dump_num(p->p_top);
    dump_num(p->p_bottom);
    printf("      |---------| \n");
}

domino domino_destroy(domino p) {
    free(p);
    p = NULL;
    return p;
}

