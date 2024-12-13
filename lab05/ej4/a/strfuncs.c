#include <stdio.h>
#include <stdlib.h>
#include "strfuncs.h"


size_t string_length(const char *str){
    unsigned int i = 0;
    size_t length = 0;
    while (str[i] != '\0')
    {
        length = length + sizeof(*str);
        i = i + 1;
    }
    
    return length;
}
/*Calcula la longitud de la cadena apuntada por str*/

char *string_filter(const char *str, char c){
    size_t length = string_length(str);
    char *cadena = NULL;
    unsigned int cont = 1;
    for (size_t i = 0; i < length; i++)
    {
        if (str[i]!=c && str[i] != '\0')
        {
            cont = cont + 1;
        }   
    }
    cadena = malloc(sizeof(char)*cont);
    unsigned int next_available = 0u;
    for (size_t i = 0; i < length; i++)
    {
        if (str[i]!=c)
        {
            cadena[next_available] = str[i];
            ++next_available;
        }   
    }
    cadena[length] = '\0';
    return cadena;
}
/*Devuelve una nueva cadena en memoria dinámica que se obtiene tomando los
caracteres de str que son distintos del caracter c.*/
