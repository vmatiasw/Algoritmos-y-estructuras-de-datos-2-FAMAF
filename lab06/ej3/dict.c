#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "dict.h"
#include "key_value.h"

struct _node_t 
{
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) 
{
    bool b = true;
    if (d != NULL)
    {
        b = (d->right != NULL && d->key != NULL && d->right->key != NULL ? string_less(d->key, d->right->key) && invrep(d->right) : true);
        
        b = b && ((d->left != NULL && d->key != NULL && d->left->key != NULL) ? string_less(d->left->key, d->key) && invrep(d->left) : true);
    }
    return b;
}

static dict_t create_node(key_t k, value_t v)
{
    struct _node_t *new_node = malloc(sizeof(struct _node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    assert(new_node != NULL);
    new_node->key = k;
    new_node->value = v;
    new_node->left = NULL;
    new_node->right = NULL;
    assert(invrep(new_node));
    return new_node;
}

dict_t dict_empty(void) 
{
    dict_t dict = NULL;
    assert(invrep(dict) && dict_is_empty(dict));
    return dict;
}

bool dict_is_empty(dict_t dict) 
{
    assert(invrep(dict));
    return dict == NULL;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) 
{
    assert(invrep(dict));
    if (dict_is_empty(dict)) // Si esta vacia, creo el nodo con el nuevo word
    {
        dict = create_node(word,def); 
    }
    else if (string_less(word, dict->key)) // Si hay algun elemento y es mayor a word, word es menor y lo acomodo a la izq 
    {
        dict->left = dict_add(dict->left, word, def);
    }
    else if (string_less(dict->key, word)) // Si hay algun elemento y es menor a word, word es mayor y lo acomodo a la der
    {
        dict->right = dict_add(dict->right, word, def);
    } 
    else // Si ya existe ese elemento, actualizo la definicion. 
    {
        dict->value = string_destroy(dict->value);
        dict->value = def;
    }
    assert(invrep(dict));
    assert(dict_exists(dict, word));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) 
{
    assert(invrep(dict));
    dict_t p = dict;
    while (!dict_is_empty(p) && !string_eq(p->key, word))
    {
        if (string_less(word, p->key))
        {
            p = p->left;
        } else {p = p->right;}
    }
    assert(!dict_is_empty(dict) == (dict_exists(dict, word)));
    return (!dict_is_empty(p)) ? p->value : NULL;
}

bool dict_exists(dict_t dict, key_t word) 
{
    assert(invrep(dict));
    bool exists=false;
    if (!dict_is_empty(dict))
    {
        if (string_eq(dict->key, word))
        {
            exists = true;
        } else {
            exists = !string_less(dict->key, word) ? 
            (dict_is_empty(dict->left) ? false : dict_exists(dict->left, word)) : 
            (dict_is_empty(dict->right) ? false : dict_exists(dict->right, word));
            }
    }
    return exists;
}

unsigned int dict_length(dict_t dict) 
{
    unsigned int length=0;
    assert(invrep(dict));
    if (!dict_is_empty(dict))
    {
        length = 1 + dict_length(dict->left) + dict_length(dict->right);
    }
    assert(invrep(dict) && (dict_is_empty(dict) || length > 0));
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) 
{
    assert(invrep(dict));
    dict_t menmay; 
    dict_t anterior_nodo = dict;
    dict_t nodo = dict;

    if (!dict_is_empty(dict)) 
    {
        
        while (!dict_is_empty(nodo) && !string_eq(nodo->key, word)) // Busca la key
        {
            anterior_nodo = nodo;
            if (string_less(word, nodo->key))
            {
            nodo = nodo->left;
            } else {nodo = nodo->right; }   
        }
        assert(!dict_is_empty(nodo) ? string_eq(nodo->key, word) : true);

        if (dict == nodo) // si dict es el nodo que tengo que eliminar, pongo dict en null
        {
            dict = NULL;
        }
        

        if (!dict_is_empty(nodo)) // Si la key existe, lo eliminamos:
        {
            if (dict_is_empty(nodo->left)) // Caso en el que el nodo es hoja o no tiene menor key
            {
                if (string_less(nodo->key, anterior_nodo->key))
                {
                    anterior_nodo->left = nodo->right; // caso si el nodo a eliminar es mayor al anterior
                } else {anterior_nodo->right = nodo->right;} // caso si el nodo a eliminar es menor al anterior
                nodo->key = string_destroy(nodo->key);
                nodo->value = string_destroy(nodo->value);
                free(nodo);
                nodo = NULL;
            }
            else if (dict_is_empty(nodo->right)) // Caso en el que el nodo no tiene menor key
            {
                if (string_less(nodo->key, anterior_nodo->key))
                {
                    anterior_nodo->left = nodo->left; // caso si el nodo a eliminar es mayor al anterior
                } else {anterior_nodo->right = nodo->left;} // caso si el nodo a eliminar es menor al anterior
                nodo->key = string_destroy(nodo->key);
                nodo->value = string_destroy(nodo->value);
                free(nodo);
                nodo = NULL;
            }
            else // Caso en el que el nodo tiene menor y mayor key
            {
                menmay = nodo->left; // Sub-arbol de keys menores a word
                if (!dict_is_empty(menmay->right))
                {
                    while (!dict_is_empty(menmay->right)) // Busca la mayor key del sub-arbol de elementos menores a word.
                    {
                        anterior_nodo = menmay;
                        menmay = menmay->right;
                    }
                    anterior_nodo->right = menmay->left; // Rescatamos la posible ramificacion izquierda de menmay
                } else {
                    nodo->left = menmay->left; // Rescatamos la posible ramificacion izquierda de menmay
                }
                nodo->key = menmay->key; // Sobreescribimos la key a eliminar
                nodo->value = menmay->value;  // Sobreescribimos el value a eliminar
                menmay->key = string_destroy(menmay->key);
                menmay->value = string_destroy(menmay->value);
                free(menmay);
                menmay = NULL;
                anterior_nodo = NULL;
                nodo = NULL;

            }
        }
    }

    assert(invrep(dict));
    assert(nodo == NULL);
    assert(!dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) 
{
    dict = dict_destroy(dict);
    dict = dict_empty();
    return dict;
}

void dict_dump(dict_t dict, FILE *file) 
{
    assert(invrep(dict));
    if ((!dict_is_empty(dict))) {
        dict_dump(dict->left, file);
        printf("\n%s:",string_ref(dict->key)); // En el medio asi las palabras aparecen en orden
        printf("%s\n",string_ref(dict->value));
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) 
{
    assert(invrep(dict));
    if (!dict_is_empty(dict))
    {
        dict->key = string_destroy(dict->key);
        dict->value = string_destroy(dict->value);
        assert(dict->value == NULL && dict->key == NULL);

        dict_destroy(dict->left);
        dict_destroy(dict->right);

        free(dict);
        dict = NULL;
    }
    assert(dict == NULL);
    return dict;
}

