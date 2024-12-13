#ifndef _PQUEUE_H_
#define _PQUEUE_H_

#include <stdbool.h>

typedef struct s_pqueue * pqueue;

typedef unsigned int pqueue_elem;

typedef unsigned int priority_t;

pqueue pqueue_empty(priority_t min_priority);
/*
* DESC: Crea una nueva instancia de pqueue con límite 'min_priority' 
* Esta pqueue no podía almacenar elementos con prioridad > min_priority
 *
 * PRE: {true}
 *  q = pqueue_empty();
 * POS: {q --> pqueue && pqueue_is_empty(q)}
 *
 */

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority);
/*
* DESC: Añade el elemento 'e' en la pcola 'q' con la 'prioridad' dada 
* 
* PRE: {q --> pqueue && priority min_priority} 
* q = pqueue_enqueue(q, e, prioridad); 
* POS: {q --> pqueue && !pqueue_is_empty()} 
*
 */

bool pqueue_is_empty(pqueue q);
/*
 * DESC: Indica si la pqueue 'q' está vacía o no
 *
 */

size_t pqueue_size(pqueue q);
/*
 * DESC: Devolver el número de elementos dentro de la pqueue 'q'
 *
 */

pqueue_elem pqueue_peek(pqueue q);
/*
 * DESC: Devolver el elemento con la prioridad más urgente de la pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  e = pqueue_peek(q);
 * POS: {q --> pqueue}
 */

priority_t pqueue_peek_priority(pqueue q);
/*
 * DESC: Devolver la prioridad que es más urgente desde la pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  priority = pqueue_peek_priority(q);
 * POS: {q --> pqueue}
 */

pqueue pqueue_dequeue(pqueue q);
/*
 * DESC: Quitar el elemento con la prioridad más urgente de la pqueue 'q'
 *
 * PRE: {q --> pqueue && !pqueue_is_empty(q)}
 *  q = pqueue_dequeue(q);
 * POS: {q --> pqueue}
 *
 */

pqueue pqueue_destroy(pqueue q);
/*
 * DESC: Destruye la instancia de pqueue, liberando toda la memoria utilizada por 'q'.
 *
 * PRE: {q --> pqueue}
 *  q = pqueue_destroy(q);
 * POS: {q == NULL}
 *
 */

#endif
