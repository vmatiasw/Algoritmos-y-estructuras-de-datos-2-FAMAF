#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "truco.h"

struct _s_truco_card {
    unsigned int numero;
    char palo;
};

#define ESPADA "ESPADA"
#define BASTO  "BASTO"
#define ORO    "ORO"
#define COPA   "COPA"

static const char *suit_str(char p) {
    const char *str;
    if (p == 'e') {
        str = ESPADA;
    } else if (p=='b') {
        str = BASTO;
    } else if (p=='o') {
        str = ORO;
    } else if (p=='c') {
        str = COPA;
    }
    return str;
}

static void dump(int num, char suit) {
    printf(" ----------------\n"
           " : %2d          :\n"
           " :              :\n"
           " :              :\n"
           " :    ""%-7s""  :\n"
           " :              :\n"
           " :              :\n"
           " :              :\n"
           " :          %2d :\n"
           " ----------------\n",
           num, suit_str(suit), num);
}

static int card_rank(int num, char suit) {
    int rank=0;

    if (4 <= num && num <= 12) { // 4 ~ 12
    } else { // 1 ~ 3
    }
    // 0 <= rank <= 11
    if (num==1 && suit == 'e') {      // Ancho de espadas
    } else if (num==1 && suit=='b') { // Ancho de bastos
    } else if (num==7 && suit=='e') { // Siete de espadas
    } else if (num==7 && suit=='o') { // Siete de oro
    }
    return rank;
}

static bool numero_de_truco(unsigned int n) {
    return n != 8 && n != 9 && n <= 12 && n >= 1;
}

static bool palo_de_truco(char c) {
    return c == 'e' || c == 'b'|| c == 'o' || c == 'c';
}

static bool invrep(truco_card c) {

    bool valid_card = c != NULL && numero_de_truco(c->numero) && palo_de_truco(c->palo);

    return valid_card;
}

truco_card scan_card(void) {
    unsigned int n, readed;
    char p;
    truco_card card;
    printf("Ingrese los valores de la carta (numero:palo): ");
    readed = scanf("(%u:%c)", &n, &p);

    card = readed == 2 && numero_de_truco(n) && palo_de_truco(p)? truco_card_new(n, p) : NULL;
    return card;
}

truco_card truco_card_new(int num, char p) {
    truco_card card = malloc(sizeof(struct _s_truco_card));
    if (card == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    card->numero = num;
    card->palo = p;

    assert(invrep(card));
    return card;
}

bool truco_card_win(truco_card a, truco_card b) {
    assert(invrep(a) && invrep(b));

    return card_rank(a->numero,a->palo) > card_rank(b->numero, b->palo);
}

bool truco_card_tie(truco_card a, truco_card b) {
    assert(invrep(a) && invrep(b));

    return card_rank(a->numero,a->palo) == card_rank(b->numero, b->palo);
}

void truco_card_dump(truco_card c) {
    assert(invrep(c));

    dump(c->numero, c->palo);
}

truco_card truco_card_destroy(truco_card c) {
    assert(invrep(c));

    free(c);
    c = NULL;

    assert(c == NULL);
    return c;
}
