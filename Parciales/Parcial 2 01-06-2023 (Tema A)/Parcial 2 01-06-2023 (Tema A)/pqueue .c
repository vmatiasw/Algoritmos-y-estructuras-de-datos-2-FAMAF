#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    struct s_node *front;
};

struct s_node
{
    pqueue_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    float p = 0.5 * (average_grade/MAX_GRADE) + 0.5 * (approved_courses/TOTAL_COURSES);
    return p;
}

// Fijarme si se debe comprobar que no se pase del MAX_GRADE....

static struct s_node *create_node(pqueue_elem e,
                                  float average_grade,
                                  unsigned int approved_courses)
{
    float priority = calculate_priority(average_grade, approved_courses);
    struct s_node *new_node = malloc(sizeof(struct s_node));
    if (new_node == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }

    new_node->approved_courses = approved_courses;
    new_node->average_grade = average_grade;
    new_node->elem = e;
    new_node->next = NULL;
    new_node->priority = priority;

    assert(new_node != NULL);
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);

    node->next = NULL;
    free(node);
    node = NULL;

    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q)
{
    bool b = q != NULL;
    unsigned int i = 0;

    if (b && q->front != NULL)
    {
        struct s_node * p = q->front;

        while (b && p->next != NULL)
        {
            b = p->priority >= p->next->priority; // Chequea que las prioridades esten ordenadas de mayor a menor.
            b = b && p->average_grade <= MAX_GRADE; // Chequea que el promedio de notas no se pasen de lo debido.
            b = b && p->approved_courses <= TOTAL_COURSES; // Chequea que los cursos aprobados no se pasen de lo debido.
            p = p->next;
            i++;
        }
        i++;
    }
    b = b && q->size == i; // chequea que el tamaño sea correcto
    return true;
}

pqueue pqueue_empty(void)
{
    pqueue q = malloc(sizeof(struct s_pqueue));
    if (q == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }

    q->front = NULL;
    q->size = 0u;

    assert(q != NULL && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q,
                      pqueue_elem e,
                      float average_grade,
                      unsigned int approved_courses)
{
    assert(invrep(q));
    struct s_node * new_node = create_node(e, average_grade, approved_courses);
    struct s_node * before_new = q->front; // Señala al elemento que debe apuntar a new_node
    float priority = new_node->priority;

    if (pqueue_is_empty(q))
    {
        q->front = new_node;
    } 
    else if (priority > q->front->priority)
    {
        new_node->next = q->front;
        q->front = new_node;
    }
    else
    {
        while (before_new->next != NULL && priority <= before_new->next->priority)
        {
            before_new = before_new->next;
        }
        new_node->next = before_new->next;
        before_new->next = new_node;
    }

    q->size = q->size + 1;
    assert(invrep(q) && !pqueue_is_empty(q)); 
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    assert(invrep(q));
    return q->front == NULL;
}


pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->elem;
}

float pqueue_peek_average_grade(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));

    return q->front->average_grade;
}

unsigned int pqueue_peek_approved_courses(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));

    return q->front->approved_courses;
}

float pqueue_peek_priority(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));

    return q->front->priority;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_copy(pqueue q)
{
    assert(invrep(q));
    pqueue copy = pqueue_empty();


    if (!pqueue_is_empty(q))
    {
        struct s_node * p = q->front;
        copy = pqueue_enqueue(copy, p->elem, p->average_grade, p->approved_courses); // Pongo el primer elemento 

        while (p->next != NULL)
        {
            p = p->next;
            copy = pqueue_enqueue(copy, p->elem, p->average_grade, p->approved_courses); // Pongo los demas elementos
        }
        p = NULL;
    }
    
    assert(invrep(copy));
   return copy;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    
    struct s_node * Killme = q->front;
    
    q->front = Killme->next;
    Killme = destroy_node(Killme);

    q->size = q->size - 1;

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));
    
    struct s_node * Killme;
    struct s_node * p = q->front;

    for (unsigned int i = 0; i < q->size; i++)
    {
        Killme = p;
        p = p->next;
        Killme = destroy_node(Killme);
    }

    free(q);
    q = NULL;

    assert(q == NULL);
    return q;
}
