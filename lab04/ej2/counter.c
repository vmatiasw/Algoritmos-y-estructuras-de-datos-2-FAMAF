#include <stdbool.h>
#include <stdlib.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

/*
    Create a new counter with initial value. Allocates new memory.
    Being c the returned counter, counter_is_init(c) should be true.
*/
counter counter_init(void) {
    counter p;
    p = malloc(sizeof(struct _counter));
    p -> count = 0;
    return p;
    /*counter c = 0;
    return c;*/
}
/*
    Increments the counter c.
*/
void counter_inc(counter c) {
    c -> count = c -> count + 1;
}
/*
    Return whether the counter c has the initial value.
*/
bool counter_is_init(counter c) {
    return c -> count == 0;
}
/*
    Decrements the counter c.
    PRECONDITION: !counter_is_init(c)
*/
void counter_dec(counter c) {
    c -> count = c -> count - 1;
}
/*
    Makes a copy of counter c. Allocates new memory.
*/
counter counter_copy(counter c) {
    counter e = counter_init();
    e -> count = c -> count;
    return e;
}
/*
   Frees memory for c.
*/
void counter_destroy(counter c) {
    free(c);
}
