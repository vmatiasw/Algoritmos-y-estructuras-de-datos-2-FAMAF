/*
  @file bakery_product.h
  @brief Defines bakery products information

  @archivo panadería_producto.h
  @brief Define información de productos de panadería


*/

#ifndef _BAKERY_PRODUCT_H
#define _BAKERY_PRODUCT_H
#define EXPECTED_PRODUCT_FILE_FORMAT //COMPLETAR
typedef enum
{
    low,
    high
} season_t;

#include <stdio.h>

/** @brief Type used to represent bakery product data.*/
/** @brief Tipo utilizado para representar datos de productos de panadería.*/
typedef struct _product
{
    unsigned int flour_cant;
    unsigned int flour_price;
    unsigned int yeast_cant;
    unsigned int yeast_price;
    unsigned int butter_cant;
    unsigned int butter_price;
    unsigned int sale_value;
} BakeryProduct;

/**
 * @brief reads bakery product data from file line
 * @details
 * Bakery product file line must contain:
 * (<unsigned int>,<unsigned int>) (<unsigned int>,<unsigned int>) (<unsigned int>,<unsigned int>) <unsigned int>
 *
 * @param[in] file Opened file stream
 * @return BakeryProduct structure which contains read information from file
 * 
 * @brief lee datos de productos de panadería de la línea de archivo
 * @detalles
 * La línea de archivo de productos de panadería debe contener:
 * (<int sin signo>,<int sin signo>) (<int sin signo>,<int sin signo>) (<int sin signo>,<int sin signo>) <int sin signo>
 *
 * @param[in] archivo Flujo de archivo abierto
 * Estructura @return BakeryProduct que contiene información de lectura del archivo
 */
BakeryProduct bakery_product_from_file(FILE *file);

#endif  //_BAKERY_PRODUCT_H
