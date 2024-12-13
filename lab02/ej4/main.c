/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100000u;

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /* create a copy of the array */
    int copy[MAX_SIZE];
    array_copy(copy, array, length);
    
    /* reset counters and set time */
    reset_comparisons_counter();
    reset_swaps_counter();
    set_current_time();

    /* do the actual sorting */
    selection_sort(copy, length);

    /* show statistics for selection_sort */
    printf("statistics for selection_sort\n");
    printf("time elapsed=%g,    comparisons: %10u,    swaps: %10u\n", calculate_elapsed_time(), comparisons_number(), swaps_number());

    /* all the same for insertion_sort */
    /* Usando la idea de las líneas de códigos anteriores
       muestre las estadísticas (tiempo de ejecución, número de comparaciones e
       intercambios realizados) para insertion_sort. No te olvides que antes debes
       copiar el arreglo original, resetear los contadores y setear el tiempo.
    */
    //insertion_sort
        array_copy(copy, array, length);
    
        /* reset counters and set time */
        reset_comparisons_counter();
        reset_swaps_counter();
        set_current_time();

        /* do the actual sorting */
        insertion_sort(copy, length);

        /* show statistics for insertion_sort */
        printf("statistics for insertion_sort\n");
        printf("time elapsed=%g,    comparisons: %10u,    swaps: %10u\n", calculate_elapsed_time(), comparisons_number(), swaps_number());

    /* all the same for quick_sort */
    /* Usando la idea de las líneas de códigos anteriores
       muestre las estadísticas (tiempo de ejecución, número de comparaciones e
       intercambios realizados) para quick_sort. No te olvides que antes debes
       copiar el arreglo original, resetear los contadores y setear el tiempo.
    */
    //quick_sort
        array_copy(copy, array, length);
    
        /* reset counters and set time */
        reset_comparisons_counter();
        reset_swaps_counter();
        set_current_time();

        /* do the actual sorting */
        quick_sort(copy, length);

        /* show statistics for quick_sort */
        printf("statistics for quick_sort\n");
        printf("time elapsed=%g,    comparisons: %10u,    swaps: %10u\n", calculate_elapsed_time(), comparisons_number(), swaps_number());

    return EXIT_SUCCESS;
}

/*

* Ejemplo de input/empty.in  (Caso base) -->

statistics for selection_sort
time elapsed=0.029,    comparisons:          0,    swaps:          0
statistics for insertion_sort
time elapsed=0.007,    comparisons:          0,    swaps:          0
statistics for quick_sort
time elapsed=0.007,    comparisons:          0,    swaps:          0

// De base el selection_sort es el mas lento.



* Ejemplo de all-negative-100.in -->

statistics for selection_sort
time elapsed=0.158,    comparisons:       4950,    swaps:        100
statistics for insertion_sort
time elapsed=0.24,    comparisons:       7405,    swaps:       2458
statistics for quick_sort
time elapsed=0.055,    comparisons:        892,    swaps:        157

// En listas grandes el quick_sort es el mas rapido y optimizado. El insertion_sort todo lo contrario. 



* Ejemplo de unsorted-10000.in -->

statistics for selection_sort
time elapsed=459.626,    comparisons:   49995000,    swaps:      10000
statistics for insertion_sort
time elapsed=750.382,    comparisons:   74824453,    swaps:   24829459
statistics for quick_sort
time elapsed=2.588,    comparisons:     199186,    swaps:      31525

// Confirmamos la anterior conlucion en una lista desordenada



* Ejemplo de sorted-asc-10000.in -->

statistics for selection_sort
time elapsed=463.005,    comparisons:   49995000,    swaps:      10000
statistics for insertion_sort
time elapsed=449.035,    comparisons:   49995399,    swaps:        399
statistics for quick_sort
time elapsed=685.474,    comparisons:   96110645,    swaps:       9626

// En una lista ordenada ascendentemente el quick_sort ya no muestra la misma eficiencia. 
// El insertion_sort es de los mas eficientes cuanto mas ordenada correctamente este la lista. 



* Ejemplo de sorted-desc-10000.in -->

statistics for selection_sort
time elapsed=514.972,    comparisons:   49995000,    swaps:      10000
statistics for insertion_sort
time elapsed=1112.71,    comparisons:   99980001,    swaps:   49995000
statistics for quick_sort
time elapsed=516.827,    comparisons:   74990000,    swaps:       9999

// En una lista ordenada descendentemente es cuando el insertion_sort muestra de sus peores caras. 
// El selection_sort es muy efeciente aca, al igual casi el quick_sort.



* Ejemplo de example-unsorted.in -->

statistics for selection_sort
time elapsed=0.035,    comparisons:         10,    swaps:          5

statistics for insertion_sort
time elapsed=0.006,    comparisons:         13,    swaps:          5

statistics for quick_sort
time elapsed=0.012,    comparisons:          8,    swaps:          4

//El insertion_sort es el mas rapido en listas cortas pero sigue realizando mas comparaciones. 
*/
