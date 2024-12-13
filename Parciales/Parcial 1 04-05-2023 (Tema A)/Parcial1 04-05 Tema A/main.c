/*
  @file main.c
  @brief Defines main program function
*/

/* First, the standard lib includes, alphabetically ordered */
/* Primero, la biblioteca estándar incluye, ordenada alfabéticamente */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
/* Entonces, este proyecto incluye, ordenados alfabéticamente */
#include "array_helpers.h"

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name)
{
    /* Print the usage help of this program. */
    printf(
        "Usage: %s <input file path>\n\n"
        "Load bakery product data from a given file in disk.\n"
        "\n"
        "The input file must exist in disk and every line in it must have the following format:\n\n"
        "##<uint>\?\?<uint> (<uint>,<uint>) (<uint>,<uint>) (<uint>,<uint>) <uint> \n\n"
        "where each value represent: \n\n"
        "##<city_code>\?\?<season> (<flour_cant>,<flour_price>) (<yeast_cant>,<yeast_price>) (<butter_cant>,<butter_price>) <sales_value> \n\n"
        "Those elements must be integers and will be copied into the multidimensional integer array 'a'.\n"
        "\n\n",
        program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return An string containing read filepath
 * 
 * * @brief lee la ruta del archivo desde la línea de comando
 *
 * @param[in] argc cantidad de argumentos de línea de comando
 * Argumentos de la línea de comando @param[in] argv
 *
 * @return Una cadena que contiene la ruta del archivo de lectura
 */
char *parse_filepath(int argc, char *argv[])
{
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2)
    {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 * 
 * * @brief Función del programa principal
 *
 * @param[in] argc cantidad de argumentos de línea de comando
 * Argumentos de la línea de comando @param[in] argv
 *
 * @return EXIT_SUCCESS cuando los programas se ejecutan correctamente, EXIT_FAILURE de lo contrario


 */
int main(int argc, char *argv[])
{
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    /* analiza la ruta del archivo dada en los argumentos de la línea de comandos */
    filepath = parse_filepath(argc, argv);

    /* create an array with the type of flight */
    /* creamos un arreglo con el tipo de vuelo */
    BakeryProductTable array;

    /* parse the file to fill the array and obtain the actual length */
    /* analizar el archivo para llenar la matriz y obtener la longitud real */
    array_from_file(array, filepath);

    /* show the data on the screen */
    /* mostrar los datos en pantalla */
    array_dump(array);

    printf("La maxima ganancia fue de %d\n",best_profit(array));
    return (EXIT_SUCCESS);
}
//caracter ? = \?