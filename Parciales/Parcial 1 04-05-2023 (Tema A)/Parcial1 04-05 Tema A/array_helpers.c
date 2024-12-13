/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char* SEASON_NAMES[SEASONS] = {"low", "high"};

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

unsigned int best_profit(BakeryProductTable a)
{
    unsigned int max_profit = 0u;
    unsigned int profit;
    for (unsigned int i = 0; i < CITIES; i++)
    {
        for (unsigned int j = 0; j < SEASONS; j++)
        {
            profit =  a[i][j].sale_value  -  ((a[i][j].flour_cant * a[i][j].flour_price) + (a[i][j].yeast_cant * a[i][j].yeast_price) + (a[i][j].butter_cant * a[i][j].butter_price));
            if (max_profit < profit)
            {
                max_profit = profit;
            }
        }
    }
    return max_profit;
}

void array_from_file(BakeryProductTable array, const char* filepath)
{
    FILE* file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    int res;
    int unsigned city;
    int unsigned temporada;

    unsigned int lista[CITIES][SEASONS] = {
    {1, 1},
    {1, 1},
    {1, 1},
    {1, 1},
    {1, 1}};

    while (!feof(file))
    {
        res = fscanf(file, "##%u\?\?%u", &city, &temporada);
        if (res != EXPECTED_DIM_VALUE) //2
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }

        if (city > 4) // Los códigos de ciudades van del 0 al 4 (5 ciudades)
        {
            fprintf(stderr, "Hay un codigo de ciudad mal subido (van del 0 al 4).\n");
            exit(EXIT_FAILURE);
        }

        if (temporada > 1) // Los códigos de temporada van del 0 al 1 
        {
            fprintf(stderr, "Hay un codigo de temporada mal subido (solo pueden ser 0 o 1).\n");
            exit(EXIT_FAILURE);
        }  
        /* COMPLETAR: Leer y guardar product en el array multidimensional*/
        /* Agregar las validaciones que considere necesarias*/
        BakeryProduct bakery_product = bakery_product_from_file(file);

        //No se podrá repetir la secuencia ciudad - temporada. Es decir, no puede existir dos entradas
        //distintas para una combinación de ciudad y temporada.
        if (lista[city][temporada] == 1)
        {
            lista[city][temporada] = 0;
        }
        else {
            fprintf(stderr, "Alguna ciudad o temporada se repite.\n");
            exit(EXIT_FAILURE);
        }
        


        array[city][temporada] = bakery_product;
        ++i;
    }
    fclose(file);
}
// ##1??0 (954,1) (16,4) (36,3) 1146