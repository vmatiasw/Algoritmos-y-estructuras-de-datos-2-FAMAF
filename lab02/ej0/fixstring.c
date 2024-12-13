#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"
    /*
fstring_length() devuelve la longitud de la cadena guardada en el parámetro s.
No se permite usar librerías de C como string.h ni strings.h. Una vez implementadas
pueden probarlas compilando junto con main.c.
     */

unsigned int fstring_length(fixstring s) {
    unsigned int i = 0;
    while (i < FIXSTRING_MAX && s[i] != '\0')
    {
        i = i + 1;
    }
    return i;
}

//fstring_eq() indica si las cadenas s1 y s2 son iguales (contienen la misma cadena).
bool fstring_eq(fixstring s1, fixstring s2) {
    unsigned int i = 0;
    unsigned int lenghts1 = fstring_length(s1);
    unsigned int lenghts2 = fstring_length(s2);
    bool iguales = true;
    if (lenghts1 != lenghts2)
    {
        iguales = false;
    }
    while (i < lenghts2 && iguales && s1[i]!='\0')
    {
           if (s1[i] != s2[i])
           {
               iguales = false;
           }
           i = i + 1; 
    }
    return iguales; 
}

//fstring_less_eq() indica si la cadena guardada en s1 es menor o igual que la guardada
//en s2 en el sentido del orden alfabético. 
bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool s1menor = true;
    unsigned int i = 0;
    while (i < FIXSTRING_MAX && s1menor && s1[i]!='\0')
    {
        if (s1[i] > s2[i])
        {
            s1menor = false;
        }
        if (s1[i] < s2[i])
        {
            i = FIXSTRING_MAX;
        }
        i = i + 1;
    }
    return s1menor;
}