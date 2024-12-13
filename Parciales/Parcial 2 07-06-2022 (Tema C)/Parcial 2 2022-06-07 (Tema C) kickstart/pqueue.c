#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "pqueue.h"

typedef struct s_node *node;

struct s_node
{
    pqueue_elem elem;
    node next;
};

struct s_pqueue
{
    node *array;
    priority_t min_priority;
    unsigned int cantidad_de_elementos;
    priority_t first_priority;
    priority_t last_priority;
};

static node create_node(pqueue_elem e)
{
    node new_node = malloc(sizeof(struct s_node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static node destroy_node(node n)
{
    if (n != NULL)
    {
        node next_node = n->next;

        free(n);
        n = NULL;
        destroy_node(next_node);
    }
    return n;
}

static unsigned int first_priority(pqueue q)
{
    unsigned int first = q->first_priority;

    while (first <= q->last_priority && q->array[first] == NULL)
    {
        first = first + 1;
    }
    return first;
}

/* La usaria si quisiese eliminar algun otro elemento que no sea el de mas prioridad.
static unsigned int last_priority (pqueue q){
    unsigned int last = q->last_priority;

    while (last >= q->first_priority && q->array[last] != NULL)
    {
            last = last - 1;
    }
    return last;
}
*/

static bool invrep(pqueue q)
{
    bool b = q != NULL;
    unsigned int i = 0;

    if (b && q->cantidad_de_elementos != 0)
    {
        b = q->first_priority <= q->last_priority;
        b = b && q->last_priority <= q->min_priority;
    }

    while (b && i < q->first_priority)
    {
        b = q->array[i] == NULL;
        i = i + 1;
    }

    i = b ? q->min_priority : 0;
    while (b && i > q->last_priority)
    {
        b = q->array[i] == NULL;
        i = i - 1;
    }
    return b;
}

pqueue pqueue_empty(priority_t min_priority)
{
    pqueue q = malloc(sizeof(struct s_pqueue));
    if (q == NULL)
    {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }

    q->array = calloc(min_priority + 1, sizeof(node));
    if ((min_priority + 1) > 0 && q->array == NULL)
    {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }

    q->cantidad_de_elementos = 0;
    q->first_priority = min_priority;
    q->last_priority = 0;
    q->min_priority = min_priority;

    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority)
{
    assert(invrep(q));
    if (q->min_priority < priority)
    {
        fprintf(stderr, "En este pqueue no se pueden almacenar prioridades de menor importancia que %u \n", priority);
        exit(EXIT_FAILURE);
    }

    node new_node = create_node(e);
    node p = q->array[priority];

    // Si no hay mas elementos con la misma prioridad pongo el elemento y actualizo de ser necesario la primer y ultima prioridad.
    if (p == NULL)
    {
        q->array[priority] = new_node;
        if (q->first_priority > priority)
        {
            q->first_priority = priority;
        }
        if (q->last_priority < priority)
        {
            q->last_priority = priority;
        }
    }

    // Si ya hay elementos con la misma prioridad, lo dejo al final.
    else
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = new_node;
    }

    // Sumo 1 a la cantidad de elementos
    q->cantidad_de_elementos = q->cantidad_de_elementos + 1;
    assert(invrep(q) && !pqueue_is_empty(q));

    return q;
}

bool pqueue_is_empty(pqueue q)
{
    assert(invrep(q));
    return q->cantidad_de_elementos == 0;
}

pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->array[q->first_priority]->elem;
}

priority_t pqueue_peek_priority(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first_priority;
}

size_t pqueue_size(pqueue q)
{
    assert(invrep(q));
    return q->cantidad_de_elementos;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    node Killme = q->array[q->first_priority];

    // Elimino y libero el elemento (se que existe por el assert y que esta ubicado en first_priority)
    q->array[q->first_priority] = Killme->next;
    free(Killme);
    Killme = NULL;

    // actualizo la primer prioridad de ser necesario
    if (q->array[q->first_priority] == NULL)
    {
        q->first_priority = first_priority(q);
    }

    // Resto 1 a la cantidad de elementos
    q->cantidad_de_elementos = q->cantidad_de_elementos - 1;

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));
    unsigned int start = q->first_priority;
    unsigned int end = q->last_priority;
    for (unsigned int i = start; i <= end; i++) // libero cada nodo del arreglo
    {
        q->array[i] = destroy_node(q->array[i]);
    }
    free(q->array); // libero espacio reservado para el arreglo
    q->array = NULL;
    free(q); // libero pqueue
    q = NULL;

    return q;
}
