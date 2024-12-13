/*
  @file array_helpers.h
  @brief defines array helpers methods. These methods operates over multidimensional array of prices
*/
#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H
#include <stdbool.h>
#include "bakery_product.h"

#define CITIES 5
#define SEASONS 2

typedef BakeryProduct BakeryProductTable[CITIES][SEASONS];

/**
 * @brief Write the content of the array 'a' into stdout.
 * @param[in] a array to dump in stdout
 * 
 * @brief Escriba el contenido de la matriz 'a' en stdout.
 * @param[in] una matriz para volcar en stdout
 */
void array_dump(BakeryProductTable a);

/**
 * @brief calculates best bakery/season profit
 * @param[in] a array with data
 * 
 * @brief calcula el mejor beneficio de panadería/temporada
 * @param[in] una matriz con datos
 */
unsigned int best_profit(BakeryProductTable a);

/**
 * @brief reads an array of prices information from file
 * @details
 *
 *  Each element is read from the file located at 'filepath'.
 *  The file must exist in disk and must have its contents in a sequence of
 *  lines, each with the following format:
 *
 *   ##<city_number>??<season_number> (<f_c>,<f_p>) (<y_c>,<y_p>) (<b_c>,<b_p>) <s_v>
 *
 *   Those elements are copied into the multidimensional array 'a'.
 *   The dimensions of the array are given by the macros noted above.
 *
 * @param a array which will contain read file
 * @param filepath file with prices data
 * 
 * 
 * @brief lee una serie de información de precios del archivo
 * @detalles
 *
 * Cada elemento se lee del archivo ubicado en 'filepath'.
 * El archivo debe existir en disco y debe tener su contenido en una secuencia de
 * líneas, cada una con el siguiente formato:
 *
 * ##<número_ciudad>??<número_temporada> (<f_c>,<f_p>) (<y_c>,<y_p>) (<b_c>,<b_p>) <s_v>
 *
 * Esos elementos se copian en la matriz multidimensional 'a'.
 * Las dimensiones de la matriz están dadas por las macros mencionadas anteriormente.
 *
 * @param una matriz que contendrá el archivo de lectura
 * Archivo @param filepath con datos de precios
 */

void array_from_file(BakeryProductTable a, const char *filepath);

#endif
