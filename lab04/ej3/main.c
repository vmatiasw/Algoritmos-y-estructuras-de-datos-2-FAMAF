/* First, the standard lib includes, alphabetically ordered */
#include <stdio.h>        /* printf()...     */
#include <stdlib.h>       /* EXIT_SUCCESS... */
#include <assert.h>  /* assert()        */

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h" /* array_helpers   */
#include "list.h"          /* TAD list        */



/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100000u;

struct _list {
    list_elem elem;
    struct _list *next;
};

//typedef struct node *_list;

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Compute average for the list of numbers in file.\n"
           "\n",
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

    return (result);
}


float average(list l,unsigned int length) {
    float n = 0.0f; //Promedio
    for (unsigned int  i = 0; i < length; ++i)
    {
        n = n + index(l,i)/ (float)length;
    }
    return n;
}

list array_to_list(int array[], unsigned int length) {
    list l = empty();
    for (unsigned int i = 0u; i < length; ++i) {
        l = addl(l,array[i]);
    }
    return l;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    //FILE *file = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /* show the array in the screen */
    array_dump(array, length);

    /* transform from array to our list type */
    list l = array_to_list(array, length);

    /* call the average function */
    printf("The average is: %.2f \n", average(l,length));
    l = destroy(l);

    return (EXIT_SUCCESS);
}
