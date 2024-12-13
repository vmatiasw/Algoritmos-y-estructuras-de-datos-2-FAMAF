#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

typedef struct stack_node *node;

struct stack_node {
    stack_elem elem;
    struct stack_node *next;
};

struct _s_stack {
    unsigned int size;
    struct stack_node *first;
};


stack stack_empty(){
    stack s = malloc(sizeof(struct stack_node));;
    s->size = 0;
    s->first = NULL;
    return s;
}

bool stack_is_empty(stack s){
    return s == NULL;
}

stack stack_push(stack s, stack_elem e){

    if (stack_is_empty(s))
    {
        s = stack_empty();
    }
    
    node p = malloc(sizeof(struct stack_node));
    if (p == NULL)
    {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }

    p->elem = e;
    p->next = s->first;
    s->first = p;
    s->size = s == NULL ? 0 : s->size + 1;
    return s;
}

stack stack_pop(stack s){
    
    assert(!stack_is_empty(s));

    s->size = s->size - 1;
    node pop = s->first;
    s->first = pop->next;
    free(pop);
    return s;
}


unsigned int stack_size(stack s){
    return s == NULL ? 0 : s->size;
}


stack_elem stack_top(stack s){

    assert(!stack_is_empty(s));

    return (s->first)->elem;
}


stack_elem *stack_to_array(stack s){
    unsigned int length = stack_size(s);
    stack_elem *a = length == 0 ? NULL : calloc(length, sizeof(stack_elem));
    if (a == NULL && length > 0)
    {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    
    node p = !stack_is_empty(s) ? s->first : NULL; // s null, devolver array vacio. siempre asegurarme de eso. 
    unsigned int i = length;
    while (p != NULL && i!=0)
    {
        a[i-1] = p->elem;
        p = p->next;
        i = i - 1;
    }
    return a;
}


stack stack_destroy(stack s){
    node q = s->first;
    node p;
    while (q != NULL)
    {
        p = q;
        q = q->next;
        free(p);
    }
    p = NULL;
    q = NULL;
    free(s);
    s = NULL;
    return s;
}
