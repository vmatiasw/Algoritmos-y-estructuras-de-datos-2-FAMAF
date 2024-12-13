    #include <stdlib.h>
    #include "assert.h"
    #include "stack.h"

    struct _s_stack {
        stack_elem elem;
        stack next;
    };

    stack stack_empty() {
        return NULL;
    }

    stack stack_push(stack s, stack_elem e) {
        stack new = calloc(1, sizeof(struct _s_stack));
        assert(new != NULL);
        new->elem = e;
        if (s == NULL) {
            s = new;
        } else {
            stack last=s;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = new;
        }
        return s;
    }

    stack stack_pop(stack s) {
        assert(s != NULL);
        stack aux = NULL, last = s;
        while (last->next != NULL) {
            aux = last;
            last = last->next;
        }

        free(last);
        last = NULL;

        if (aux != NULL)
        {
            aux->next = NULL;
        } else {s=NULL;}

        return s;
    }

    unsigned int stack_size(stack s) {
        unsigned int count = 0;
        stack aux = s;
        while (aux != NULL) {
            aux = aux->next;
            ++count;
        }
        return count;
    }

    stack_elem stack_top(stack s) {
        assert(s != NULL);
        stack last=s;
        while (last->next != NULL) {
                last = last->next;
        }
        return last->elem;
    }

    bool stack_is_empty(stack s) {
        return (s == NULL);
    }

    stack stack_destroy(stack s) {
        while (!stack_is_empty(s)) {
            s = stack_pop(s);
        }
        return NULL;
    }

// Error arreglado. Si solo hay un elemento y lo eliminamos en stack_pop se debe devolver NULL. 
// El error estaba en que estabamos devolviendo la direccion de s cuando ya habia sido liberada. 
/* Error: 

106         while (!stack_is_empty(letters_lifo)) {
1: i = 18
(gdb) 
107             is_palindrome = is_palindrome && stack_top(letters_lifo) == phrase_noblank[i];
1: i = 18
(gdb) 
108             letters_lifo = stack_pop(letters_lifo);
1: i = 18
(gdb) s
stack_pop (s=0x5555555596d0) at ./helpers/stack.c:32
32          assert(s != NULL);
(gdb) n
33          stack aux = NULL, last = s;
(gdb) display aux
2: aux = (stack) 0x0
(gdb) display last
3: last = (stack) 0x5555555596d0
(gdb) n
34          while (last->next != NULL) {
2: aux = (stack) 0x0
3: last = (stack) 0x5555555596d0
(gdb) 
39          free(last);
2: aux = (stack) 0x0
3: last = (stack) 0x5555555596d0
(gdb) 
double free or corruption (fasttop)

Program received signal SIGABRT, Aborted.
__pthread_kill_implementation (no_tid=0, signo=6, threadid=140737353770816) at ./nptl/pthread_kill.c:44
44      ./nptl/pthread_kill.c: No existe el archivo o el directorio.
(gdb) 
*/
