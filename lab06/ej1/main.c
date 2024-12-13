/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
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

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

static void dump_tree(abb tree) { // 1 ........ Mostrar árbol por pantalla
    if (!abb_is_empty(tree)) {
        printf("Arbol:");
        abb_dump(tree);
    } else {
        printf("\nÁrbol vacío\n");
    }
}

static void dump_rmm(abb tree) { // 6 ........ Mostrar raiz, máximo y mínimo del árbol
    if (!abb_is_empty(tree)) {
        printf("Raiz: %d\nMinimo: %d\nMaximo: %d\n",   abb_root(tree),
                                                       abb_min(tree),
                                                       abb_max(tree));
    } else {
        printf("\nÁrbol vacío\n");
    }
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    // Ciclo
    bool b = true;
    unsigned int readed, input;
    abb_elem elem;
    while (b)
    {
        printf( "\n//-----------------------------------------------//\n"
                "1 ........ Mostrar árbol por pantalla              \n"
                "2 ........ Agregar un elemento                     \n"
                "3 ........ Eliminar un elemento                    \n"
                "4 ........ Chequear existencia de elemento         \n"
                "5 ........ Mostrar longitud del árbol              \n"
                "6 ........ Mostrar raiz, máximo y mínimo del árbol \n"
                "7 ........ Salir                                   \n");
        printf("\nEscribir numero de comando:");
        readed = scanf("%u", &input);
        printf("\n");

        if (readed != 1 || input-1 > 7)
        {
            printf(readed != 1  ? "Formato invalido\n" : "Numero invalido\n");
        }
        else if (input == 1) {
            dump_tree(tree);
            printf("\n");
        }
        else if (input == 2)
        {
            printf("Pase un elemento para agregar:");
            readed = scanf("%d", &elem);
            tree = readed == 1 ? abb_add(tree,elem) : tree;
            printf("\n");
        }
        else if (input == 3)
        {
            printf("Pase un elemento para borrar:");
            readed = scanf("%d", &elem);
            if (readed != 1 || !abb_exists(tree, elem))
            {
                printf("\nEl elemento no existe");
            }
            else {tree = abb_remove(tree,elem);}
            printf("\n");
        }
        else if (input == 4)
        {
            printf("Pase un elemento para ver si existe:");
            readed = scanf("%d", &elem);
            printf(readed == 1 && abb_exists(tree, elem) ? "\nEl elemento existe" : "\nEl elemento no existe");
            printf("\n");
        }
        else if (input == 5)
        {
            printf("Longitud: %u\n", abb_length(tree));
        }
        else if (input == 6)
        {
            dump_rmm(tree);
            printf("\n");
        }
        else if (input == 7)
        {
            b = false;
        }
    }
    
    abb_destroy(tree); // Al salir debe liberarse toda la memoria utilizada.
    tree = NULL;

    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */

    return (EXIT_SUCCESS);
}
