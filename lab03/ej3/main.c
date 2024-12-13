#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length)
{
    printf("\"");
    for (unsigned int j = 0u; j < length; j++)
    {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size)//char sorted[], 
{
    FILE *file = fopen(path, "r");
    unsigned int i = 0;
    int scanRes;

    if (file == NULL)
    {
        fprintf(stderr, "El archivo no existe.\n");
        exit(EXIT_FAILURE);
    }

    while (feof(file) == 0 && i < max_size)
    {
        scanRes = fscanf(file, "%u -> *%c*\n", &indexes[i], &letters[i]); 
        if (scanRes != 2)
        {
            printf("Patron invalido\n");
            exit(EXIT_FAILURE);
        }
            if (indexes[i] > max_size)
        {
            printf("El índice %u es más grande que %u por lo que no se tomara en cuenta y el lugar faltante se vera identificado con un '_'.\n", indexes[i], MAX_SIZE);
        }
        i = i + 1;
    }
    fclose(file);
    return (i);
}

/*
argc: Es el número de argumentos que se han pasado al programa.
argv: Es un arreglo de punteros a caracteres que contiene los argumentos pasados al programa. argv[0] es el nombre del programa,
argv[1] es la ubicación del archivo y los siguientes elementos son los argumentos pasados al programa.
*/
int main(int argc, char *argv[])
{
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length = 0;
    if (argc > 1)
    {
        length = data_from_file(argv[1], indexes, letters, MAX_SIZE);
    }
    else
    {
        printf("No se han pasado suficientes argumentos al programa.\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0u; i < length; i++)
    {
        sorted[i]= '_';
    }
    for (unsigned int i = 0u; i < length; i++)
    {
        if (indexes[i] < length)
        {
            sorted[indexes[i]]=letters[i];
        }
    }
    
    dump(sorted, length);
    return EXIT_SUCCESS;
}
