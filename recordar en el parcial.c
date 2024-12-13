// Luego de malloc, calloc... (reservar memoria) chequear con:
    int *array = malloc(sizeof(int)*size);
    * lenght = size;

    if (size > 0 && array == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    
* incluir la libreria:
#include <stdio.h>

// No olvidar sumar y restar s->size!!

// Chequear todo en la invariante


// No hace falta hacer un caso para s->size == 1 en este caso:

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    if (s->first == NULL)
    {
        s->first = new_node;
    } else if (priority >= s->first->priority)
    {
        new_node->next = s->first;
        s->first = new_node;
    } 
    else
    {
        struct s_node * p = s->first;

        while (p->next != NULL && priority < p->next->priority)
        {
            p = p->next;
        }
        new_node->next = p->next;
        p->next = new_node;
        
    }

    s->size = s->size + 1;
    
    assert(invrep(s)); 
    return s;
}
        
        
//
