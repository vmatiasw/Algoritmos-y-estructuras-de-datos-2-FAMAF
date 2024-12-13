#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node * first;
};

struct s_node {
    unsigned int elem;
    unsigned int priority;
    struct s_node * next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    if (new_node == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    assert(new_node!=NULL);

    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;

    assert(new_node->elem==e && new_node->priority == priority); 
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    bool b = q != NULL; // Verifica que se cumpla el orden de prioridades y que la relacion entre q->size y la cantidad de elementos sea correcta.
    bool z = true; // Verifica que el ultimo elemento N tenga N->next == NULL

    if (b && q->size == 0)
    {
        b = q->first == NULL;
    } 

    if (b && q->size > 0)
    {
        struct s_node * p = q->first;
        
        b = q->first != NULL;
        z = p->next == NULL;
        for (unsigned int i = 0 ; b && i < q->size - 1 ; i++)
        {
            b = p->next != NULL; // Verifico que el tamaño de la cola este bien. 
            b = b && p->priority <= p->next->priority; // Verifico que los de mayor prioridad (menor o igual numero) esten adelante.
            z = p->next->next == NULL;
            p = p->next;
        }
    }
    return (b && z);
}

pqueue pqueue_empty(void) {
    pqueue q = malloc(sizeof(struct s_pqueue));
    if (q == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    q->first = NULL;
    q->size = 0;
    assert(q != NULL);
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node * before_new = q->first; // Señala al elemento que debe apuntar a new_node
    struct s_node * new_node = create_node(e, priority);
    assert(new_node->elem==e && new_node->priority==priority);

    if (pqueue_is_empty(q))
    {
        q->first = new_node;
    } 
    else if (q->first->priority > priority)
    {
        new_node->next = q->first;
        q->first = new_node;
    }
    else
    {
        while (before_new->next != NULL && priority >= before_new->next->priority)
        {
            before_new = before_new->next;
        }
        new_node->next = before_new->next;
        before_new->next = new_node;
    }

    q->size = q->size + 1;
    
    assert(invrep(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q)); 
    return q->first == NULL;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->priority;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    
    struct s_node * Killme = q->first;
    
    q->first = Killme->next;
    free(Killme);
    Killme = NULL;

    q->size = q->size - 1;

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    
    struct s_node * Killme;
    struct s_node * p = q->first;

    for (unsigned int i = 0; i < q->size; i++)
    {
        Killme = p;
        p = p->next;
        destroy_node(Killme);
    }
    Killme = NULL;
    free(q);
    q = NULL;

    assert(q == NULL);
    return q;
}
