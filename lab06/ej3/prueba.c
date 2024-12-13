/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "dict.h"
#include "dict_helpers.h"
#include "helpers.h"
#include "string.h"


int main(void) {
    dict_t d = dict_empty();

    assert(dict_is_empty(d));

    char *word = "cccc";
    char *def = "ccc";

    key_t word_ =  string_create(word);
    value_t def_ =  string_create(def);

    char *w1 = "bba";
    char *d1 = "ggzzzzss";

    key_t w1_ =  string_create(w1);
    value_t d1_ =  string_create(d1);

    char *w2 = "bcc";
    char *d2 = "ggsaaaas";

    key_t w2_ =  string_create(w2);
    value_t d2_ =  string_create(d2);

    char *w3 = "aaa";
    char *d3 = "aaa";

    key_t w3_ =  string_create(w3);
    value_t d3_ =  string_create(d3);

    char *w4 = "bbbb";
    char *d4 = "bbbb";

    key_t w4_ =  string_create(w4);
    value_t d4_ =  string_create(d4);

    d = dict_add(d, w4_, d4_);

    d = dict_add(d, w3_, d3_);

    d = dict_add(d, word_, def_);

    d = dict_add(d, w1_, d1_);

    d = dict_add(d, w2_, d2_);

    string_dump( dict_search(d, word_) , stdout);

    printf("%u",dict_length(d));

    d = dict_remove(d, w4_);

    d = dict_remove(d, word_);

    d = dict_remove(d, w1_);

    word = "sopa";
    def = "sopa";

    word_ =  string_create(word);
    def_ =  string_create(def);

    assert(!dict_exists(d, word_));

    //d = dict_empty();

    d = dict_add(d, word_, def_);

    dict_dump(d, stdout);

    d = dict_remove_all(d);

    assert(dict_is_empty(d));

    d = dict_destroy(d);

    assert(d == NULL);
}