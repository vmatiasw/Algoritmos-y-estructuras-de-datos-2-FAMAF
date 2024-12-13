
#ifndef __STRFUNCS_H__
#define __STRFUNCS_H__

#include <stddef.h>

size_t string_length(const char *str);
/*Calcula la longitud de la cadena apuntada por str, y la función*/

char *string_filter(const char *str, char c);
/*Devuelve una nueva cadena en memoria dinámica que se obtiene tomando los
caracteres de str que son distintos del caracter c.*/
#endif