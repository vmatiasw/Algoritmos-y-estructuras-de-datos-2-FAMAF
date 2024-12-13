
#include <stdbool.h> /* True and False  */
#include <stdio.h>   /* printf()...     */
#include <assert.h>  /* assert()        */
#include <stdlib.h>  /* EXIT_SUCCESS... */
#include "list.h"    /* spec TAD list   */



struct _list {
    list_elem elem;
    struct _list *next;
};

//typedef struct node *_list;

// Constructors 

list empty(){
    return NULL;
}
/*{- crea una lista vacía. -}*/

list addl( list l, list_elem e){
    list p = malloc(sizeof(struct _list));
    p->elem = e;
    p->next = l;
    l = p;
    return l;
}
/*{- agrega el elemento e al comienzo de la lista l. -}*/

// Destroy

list destroy(list l){
    list r;
        while (l != NULL)
    {
        r = l;
        l = l->next;
        free(r);
    }
    return NULL;
}
/*{- Libera memoria en caso que sea necesario. -}*/

// Operations
bool is_empty(list l){
    return (l == NULL);
}
/*{- Devuelve True si l es vacía. -}*/

list_elem head(list l){
    return l->elem;
}
/*{- Devuelve el primer elemento de la lista l -}
 *{- PRE: not is_empty(l) -}
 */

list tail(list l){
    list r = l;
    l = l->next;
    free(r);
    return l;
}
/*{- Elimina el primer elemento de la lista l -}
 *{- PRE: not is_empty(l) -}
 */

list addr(list l, list_elem e){
    list new = malloc(sizeof(struct _list));
    new->elem = e;
    new->next = NULL;
    list p = l;
    if (l != NULL)
    {
        while (p -> next != NULL)
        {
            p = p -> next;
        }
        p -> next = new;
        
    } else { l = new;}
    return l;
}
/*{- agrega el elemento e al final de la lista l. -}*/

list_elem length(list l){
    list p = l;
    unsigned int n = 0;
    while (p != NULL)
    {
        n = n + 1;
        p = p -> next;
    }   
    return n;
}
/*{- Devuelve la cantidad de elementos de la lista l -}*/

list concat(list l, list r){
    list p = l;
    if (l != NULL && r != NULL)
    {
        while (p -> next != NULL)
        {
            p = p -> next;
        }
        p -> next = r;
    } else if (l == NULL)
    {
        l = r;
    }
    return l;
}
/*{- Agrega al final de l todos los elementos de r en el mismo orden.-}*/

list_elem index(list l, list_elem n){
    list p = l;
    while (n > 0)
    {
        p = p -> next;
        n = n-1;
    }
    return p -> elem;
    
}
/*{- Devuelve el n-ésimo elemento de la lista l -}
 *{- PRE: length(l) > n -}*/

list take(list l, list_elem n){
    list p = l;
    while (n > 0)
    {
        p = p -> next;
        n = n - 1;
    }
    destroy(p -> next);
    p -> next = NULL;
    return l;
}
/*{- Deja en l sólo los primeros n elementos, eliminando el resto -}*/

list drop(list l, list_elem n){
    list aux;
    n = n + 1;
    while (n > 0)
    {
        aux = l;
        l = l -> next;
        free(aux);
        n = n - 1;
    }   
    return l;
}
/*{- Elimina los primeros n elementos de l -}*/

list copy_list(list l){
    list p = l;
    list copy = empty();
    while (p != NULL)
    {
        addr(copy,p->elem);
        p = p -> next;
    }
    return copy;
}
/*{- Copia todos los elementos de l en la nueva lista l2 -}*/