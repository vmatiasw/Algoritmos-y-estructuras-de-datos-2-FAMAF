#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "string.h"

struct _s_string {
    char *content;
    unsigned int length;
};

string string_create(const char *word) {
    string str = calloc(1, sizeof(struct _s_string)); 
    if (str == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i=0;
    while (word[i] != '\0')
    {
        i++;
    }
    
    str->length = i;
    str->content = calloc(i + 1, sizeof(char)); // Tomo en cuenta '\0'
    if (i > 0 && str->content == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    str->content = strncpy(str->content, word, str->length + 1); /* Copy no more than N characters of SRC to DEST.*/
    str->length = i; // * (unsigned int)sizeof(char); ??
    //Aunque es raro, no se puede garantizar que siempre sea 1 byte en todas las implementaciones de C. By ChatGPT
    return (str);
}

unsigned int string_length(string str) {
    return (str != NULL ? str->length : 0);
}

static unsigned int max(int a, int b) {
    return (a > b) ? a : b;
}

bool string_less(const string str1, const string str2) {
    bool s1menor = str1 != NULL && str2 != NULL;
    unsigned int i = 0;
    unsigned int sizemax = max(string_length(str1),string_length(str2));
    while (i < sizemax && s1menor && str1->content[i]!='\0')
    {
        if (str1->content[i] > str2->content[i])
        {
            s1menor = false;
        }
        if (str1->content[i] < str2->content[i])
        {
            i = sizemax;
        }
        i = i + 1;
    }
    return s1menor;
}

bool string_eq(const string str1, const string str2) {
    int cmp = (str1 != NULL && str2 != NULL) ? strcmp(str1->content, str2->content) : 1;
    return (cmp == 0);
}   

string string_clone(const string str) {
    return (string_create(str->content));
}

string string_destroy(string str) {
    if (str != NULL)
    {
        free(str->content);
        str->content = NULL;
        str->length = 0;
        free(str);
        str = NULL;
    }
    return (str);
}

/*struct _s_string {
    char *content;
    unsigned int length;
};
*/

void string_dump(string str, FILE *file) {
    assert(str != NULL);
    fprintf(file, "%s", str->content);
}

const char *string_ref(string str) {
    return (str->content);
}
