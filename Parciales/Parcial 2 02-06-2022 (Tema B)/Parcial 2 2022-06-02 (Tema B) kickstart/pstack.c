#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node * first;
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node  * next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    if (new_node == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }

    new_node->elem = e;
    new_node->next = NULL;
    new_node->priority = priority;

    assert(new_node != NULL && new_node->elem==e && new_node->priority == priority && new_node->next == NULL);
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    bool b = s != NULL;
    unsigned int i = 0;

    if (b && s->first != NULL)
    {
        struct s_node * p = s->first;

        while (b && p->next != NULL)
        {
            b = p->priority >= p->next->priority;
            p = p->next;
            i++;
        }
        i++;
    }
    b = b && s->size == i;
    return b;
}

pstack pstack_empty(void) {
    pstack s = malloc(sizeof(struct s_pstack));
    if (s == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    s->first = NULL;
    s->size = 0;
    assert(invrep(s));
    return s;
}

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

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return s->first == NULL;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->first->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    return s->first->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    struct s_node * Killme = s->first;
    s->first = Killme->next;
    free(Killme);
    Killme = NULL;

    s->size = s->size -1;

    assert(invrep(s) && Killme == NULL);
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node * Killme;
    struct s_node * p = s->first;

    for (unsigned int i = 0; i < s->size; i++)
    {
        Killme = p;
        p = p->next;
        Killme = destroy_node(Killme);
    }

    free(s);
    s = NULL;
    
    assert(s == NULL);
    return s;
}

