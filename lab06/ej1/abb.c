#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree)
{
    bool b = true;
    if (tree != NULL)
    {
        b = (tree->right != NULL ? elem_less(tree->elem, tree->right->elem) && invrep(tree->right) : true);
        
        b = b && (tree->left != NULL ? elem_less(tree->left->elem, tree->elem) && invrep(tree->left) : true);
    }
    return b;
}

static abb create_node(abb_elem e)
{
    struct _s_abb *new_node = malloc(sizeof(struct _s_abb));
    if (new_node == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->left = NULL;
    new_node->right = NULL;
    assert(invrep(new_node));
    return new_node;
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e)
{
    assert(invrep(tree));
    if (abb_is_empty(tree))
    {
        tree = create_node(e);
    }
    else if (elem_less(e, tree->elem))
    {
        tree->left = abb_add(tree->left, e);
    }
    else if (elem_less(tree->elem, e))
    {
        tree->right = abb_add(tree->right, e);
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    assert(invrep(tree));
    bool exists=false;
    if (!abb_is_empty(tree))
    {
        if (elem_eq(tree->elem, e))
        {
            exists = true;
        } else {
            exists = !elem_less(tree->elem, e) 
            ? (abb_is_empty(tree->left) ? false : abb_exists(tree->left, e)) 
            : (abb_is_empty(tree->right) ? false : abb_exists(tree->right, e));
            }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (!abb_is_empty(tree))
    {
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    abb menmay, aux = tree;
    abb nodo = tree;

    if (!abb_is_empty(tree)) 
    {
        
        while (!abb_is_empty(nodo) && !elem_eq(nodo->elem, e)) // Busca el elemento
        {
            aux = nodo;
            if (elem_less(e, nodo->elem))
            {
            nodo = nodo->left;
            } else {nodo = nodo->right; }   
        }
        assert(nodo->elem == e);
        if (!abb_is_empty(nodo)) // Si el elemento existe, lo eliminamos:
        {
            if (abb_is_empty(nodo->left)) // Caso en el que el nodo es hoja o no tiene mayor elemento
            {
                if (elem_less(nodo->elem, aux->elem))
                {
                    aux->left = nodo->right;
                } else {aux->right = nodo->right;}
                free(nodo);
                nodo = NULL;
            }
            else if (abb_is_empty(nodo->right)) // Caso en el que el nodo no tiene menor elemento
            {
                if (elem_less(nodo->elem, aux->elem))
                {
                    aux->left = nodo->left;
                } else {aux->right = nodo->left;}
                free(nodo);
                nodo = NULL;
            }
            else // Caso en el que el nodo tiene menor y mayor elemento
            {
                menmay = nodo->left; // Sub-arbol de elementos menores a e
                if (!abb_is_empty(menmay->right))
                {
                    while (!abb_is_empty(menmay->right)) // Busca el mayor elemento del sub-arbol de elementos menores a e.
                    {
                        aux = menmay;
                        menmay = menmay->right;
                    }
                    assert(menmay->elem == abb_max(nodo->left));
                    aux->right = menmay->left; // Rescatamos la posible ramificacion izquierda de menmay
                } else {
                    nodo->left = menmay->left; // Rescatamos la posible ramificacion izquierda de menmay
                }
                nodo->elem = menmay->elem; // Sobreescribimos el elemento a eliminar
                free(menmay);
                menmay = NULL;
            }
        }
    }

    assert(invrep(tree));
    assert(!abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    abb nodo = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while (!abb_is_empty(nodo->right))
    {
        nodo = nodo->right;
    }
    max_e = nodo->elem;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    abb nodo = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while (!abb_is_empty(nodo->left))
    {
        nodo = nodo->left;
    }
    min_e = nodo->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if ((!abb_is_empty(tree))) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        //printf("%d ", tree->elem);
        // Si llamamos a abb_dump(tree->left) antes, nos devolvera los elementos en orden
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (!abb_is_empty(tree))
    {
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}

