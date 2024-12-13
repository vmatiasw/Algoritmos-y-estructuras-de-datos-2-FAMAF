/*
  @file bakery_product.c
  @brief Implements bakery product structure and methods
*/
#include <stdlib.h>
#include "bakery_product.h"

static const int AMOUNT_OF_PRODUCT_VARS = 7;

BakeryProduct bakery_product_from_file(FILE* file)
{
    BakeryProduct product;
    // ##1??0 (954,1) (16,4) (36,3) 1146
    int res = fscanf(file, " (%u,%u) (%u,%u) (%u,%u) %u\n", &product.flour_cant, &product.flour_price, &product.yeast_cant, &product.yeast_price, &product.butter_cant, &product.butter_price, &product.sale_value);
    //                                              (<cantidad_harina>,  <precio_harina>)     (<cantidad_levadura>, <precio_levadura>)   (<cantidad_manteca>,    <precio_manteca>)     <valor_de_mercado>
    // harina (flour), Levadura (yeast) y Manteca (butter)

    if (res != AMOUNT_OF_PRODUCT_VARS)
    {
        fprintf(stderr, "Invalid product data.\n");
        exit(EXIT_FAILURE);
    }
    return product;
}