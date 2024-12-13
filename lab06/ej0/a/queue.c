#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h" // Cola

struct s_queue {
    unsigned int size;
    struct s_node *first;
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
};

static struct s_node *
create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return q != NULL;
}

queue queue_empty(void) {
    queue q = malloc(sizeof(struct s_queue));
    assert(q!=NULL);
    q->first = NULL;
    q->size = 0;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

/*Modifique el assert y esta operacion no es de orden constante para no hacer el punto c en el a y poder comparar ambas implementaciones*/
queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    struct s_node *p = q->first;
    
    q->size=q->size+1;
    if (q->first==NULL) {
        q->first = new_node;
    } else {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = new_node;
    }
    p = NULL;
    assert(invrep(q) && !queue_is_empty(q) && queue_last(q) == e);
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}

queue_elem queue_last(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node *p = q->first;
    
    while (p->next != NULL)
    {
        p = p->next;
    }

    queue_elem e = p->elem;
    p = NULL;
    return e;
}

unsigned int queue_size(queue q) {
    assert(invrep(q));
    return q->size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    q->size=q->size-1;
    killme = destroy_node(killme);
    assert(invrep(q));
    return q;

}

void queue_dump(queue q, FILE *file) {
    file = file==NULL ? stdout: file;
    struct s_node *node=q->first;
    fprintf(file, "[ ");
    while(node!=NULL) {
        fprintf(file, "%d", node->elem);
        node = node->next;
        if (node != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]\n");
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}

