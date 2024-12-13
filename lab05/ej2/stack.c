#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"



struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));
    s->elems = calloc(50, sizeof(stack_elem));
    if (s == NULL || s->elems == NULL)
    {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    s->size = 0;
    s->capacity = 50;
    return s;
}

/**
* @brief Inserts an element at the top of the stack
* @param s A stack
* @param e An element to push into the stack
* @return The new stack with 'e' at the top
*/
stack stack_push(stack s, stack_elem e){
    stack p = s == NULL ? stack_empty() : s;
    if (p->capacity == p->size)
    {
        p = realloc(p->elems,sizeof(p->elems)*2);
        if (p == NULL)
        {
            fprintf(stderr, "Not enough memory\n");
            exit(EXIT_FAILURE);
        }
        p->capacity = p->capacity*2;
    }
    p->elems[p->size] = e;
    p->size = p->size+1;
    s = p;
    return s;
}

/**
* @brief Removes the element at the top of the stack
* @param s A stack
* @return The new stack with the top element removed
* @note Only applies to non-empty stacks
*/
stack stack_pop(stack s){
    
    assert(s != NULL && s->size != 0);

    s->elems[s->size-1]=0;
    s->size = s->size - 1;

    return s;
}

/**
* @brief Returns the size of the stack
* @param s A stack
* @return The size of the stack
*/
unsigned int stack_size(stack s){
    return s == NULL ? 0 : s -> size;
}

/**
* @brief Returns the element at the top of the stacks
* @param s A stacks
* @return The element at the top of the stack
* @note Only applies to non-empty stacks
*/
stack_elem stack_top(stack s){

    assert(s != NULL && s->size != 0);

    return s->elems[s->size-1];
}

/**
* @brief Check if the given stack is empty
* @param s A stack
* @return true if the stack is empty, false otherwise
*/
bool stack_is_empty(stack s){
    return s == NULL || s->size == 0;
}

/**
* @brief Creates an array with all the elements of the stack
* @param s A stack
* @return An array containing all the elements of the stack. The stack top element
* becomes the rightmost element of the array. The size of the resulting
* array is determined by 'stack_size(s)'
*/
stack_elem *stack_to_array(stack s){
    unsigned int length = stack_size(s);
    stack_elem *a = length == 0 ? NULL : calloc(length, sizeof(stack_elem));

    if (a == NULL && length > 0)
    {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    
    for (unsigned int i = 0u; i < length; i++)
    {
        a[length-1 - i] = s->elems[i];
    }
    return a;
}

/**
* @brief Destroys the stack
* @param s A stack
* @note All memory resources are freed
*/
stack stack_destroy(stack s){
    free(s->elems);
    free(s);
    s = NULL;
    return s;
}
