#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"




struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
};

stack stack_empty(){
    return NULL;
}

/**
* @brief Inserts an element at the top of the stack
* @param s A stack
* @param e An element to push into the stack
* @return The new stack with 'e' at the top
*/
stack stack_push(stack s, stack_elem e){
    stack p = malloc(sizeof(struct _s_stack));

    if (p == NULL)
    {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }

    p->elem = e;
    p->next = s;
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
    
    assert(s != NULL);

    stack pop = s;
    s = s->next;
    free(pop);
    return s;
}

/**
* @brief Returns the size of the stack
* @param s A stack
* @return The size of the stack
*/
unsigned int stack_size(stack s){
    stack p = s;
    unsigned int n = 0u;
    while (p != NULL)
    {
        n = n + 1;
        p = p -> next;
    }   
    return n;
}

/**
* @brief Returns the element at the top of the stacks
* @param s A stacks
* @return The element at the top of the stack
* @note Only applies to non-empty stacks
*/
stack_elem stack_top(stack s){

    assert(s != NULL);

    return s->elem;
}

/**
* @brief Check if the given stack is empty
* @param s A stack
* @return true if the stack is empty, false otherwise
*/
bool stack_is_empty(stack s){
    return s == NULL;
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
    
    stack p = s;
    unsigned int i = length;
    while (p != NULL && i!=0)
    {
        a[i-1] = p->elem;
        p = p->next;
        i = i - 1;
    }
    return a;
}

/**
* @brief Destroys the stack
* @param s A stack
* @note All memory resources are freed
*/
stack stack_destroy(stack s){
    stack p;
    while (s != NULL)
    {
        p = s;
        s = s->next;
        free(p);
    }
    p = NULL;
    return s;
}
