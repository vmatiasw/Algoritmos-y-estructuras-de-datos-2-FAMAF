#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"                              

#include <stdbool.h>

void array_swap(int a[], unsigned int i, unsigned int j) {
    int aux;
    aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

bool array_is_sorted(int a[], unsigned int length) {
    bool ordenado = true;
    unsigned int i = 0;
    while (ordenado && i < length - 1)
    {
        if (a[i] > a[i+1])
        {
            ordenado = false;
        }
        
        i = i + 1;
    }
    return ordenado;
}


unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    
    FILE * f = fopen(filepath,"r");
    unsigned int maxf;
    int elem;
    int scanRes;

    // Verificamos posibles errores
    if (f == NULL)
    {
        printf("No se pudo acceder al archivo %s\n",filepath);
        exit (EXIT_FAILURE);
    }

    fscanf (f, "%u", &maxf);
    if (maxf <= max_size)
    {
        for (unsigned int i = 0; i < maxf; ++i)
        {
            scanRes = fscanf(f,"%d",&elem);
            if (scanRes != EOF)
            {
                array[i] = elem;
            }
            else {
                printf("Formato invalido \n");
                exit(EXIT_FAILURE);
            }
        }
        
    }
    else {
        printf("La longitud exece el maximo del arreglo \n");
        exit(EXIT_FAILURE);
    }
    fclose(f);
    return maxf;
}


void array_dump(int a[], unsigned int length) {
    printf("[");
    int j;
    if (length != 0u)
    {
        for (unsigned int i = 0u; i < length; ++i)
        {
            j = i;
            printf("%d",a[j]);
            if (i < length - 1)
            {
                printf(", ");
            }
            
        }
    }
    printf("]\n");
}