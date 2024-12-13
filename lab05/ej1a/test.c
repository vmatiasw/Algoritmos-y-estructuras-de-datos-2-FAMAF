#include "stack.h"
#include <stdlib.h>
#include <assert.h>

int main()
{
    stack s = stack_empty();
    s = stack_push(s, 5);
    s = stack_pop(s);

    assert(stack_is_empty(s));

    stack_elem *a = stack_to_array(s);

    assert(a == NULL);

    s = stack_push(s, 7);

    assert(!stack_is_empty(s));

    s = stack_push(s, 8);

    a = stack_to_array(s);

    assert(a[0] == 7 && a[1] == 8);

    return 0;
}
