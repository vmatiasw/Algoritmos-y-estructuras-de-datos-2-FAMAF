#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "truco.h"



int main(void) // no hay argumentos por lo que borro int argc, char const *argv[]
{ 
    // Obtengo las cartas
    printf("ESPADA: e \nBASTO: b \nORO: o \nCOPA: c\n");
    truco_card card1 = NULL;
    card1 = scan_card();
    if (card1 == NULL)
    {
        printf("ERROR DE LECTURA\n\n");
        exit(EXIT_FAILURE);
    }

    truco_card card2 = NULL;
    card2 = scan_card();
    if (card2 == NULL)
    {
        printf("ERROR DE LECTURA\n\n");
        exit(EXIT_FAILURE);
    }

    // Veo si las cartas empataron o quien gano
    bool empate = truco_card_tie(card1, card2);
    unsigned int n_ganador =2;
    n_ganador -= truco_card_win(card1, card2);

    printf(empate ? "¡La mano está parda!\n\n Cartas:\n" : "Gano la carta %u\n\n Cartas:\n", n_ganador);

    // Muestro las cartas:

    for (unsigned int i = 0; i < 2; i++)
    {
        if ((n_ganador == 1 && i == 0) || ((n_ganador == 2 && i == 1)))
        {
            truco_card_dump(card1);
        }
        if ((n_ganador == 2 && i == 0) || ((n_ganador == 1 && i == 1)))
        {
            truco_card_dump(card2);
        }
    }
    
    // Destruyo las cartas:
    card1 = truco_card_destroy(card1);
    card2 = truco_card_destroy(card2);

    return EXIT_SUCCESS;
}