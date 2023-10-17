#ifndef __STACK__
#define __STACK__

#include <stddef.h>  /* size_t */
#include <stdbool.h> /* bool   */ 
/*---------------------------------------------------------------------------*/
typedef enum { SUCCESS = 0, FAIL } Result; 

typedef struct stack *pstack_t;
typedef void *elem_t;
typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);

pstack_t stack_create(size_t max_num_of_elem,
                      clone_t clone,
                      destroy_t destroy,
                      print_t print);

Result stack_destroy(pstack_t stack);

Result stack_push(pstack_t stack, elem_t elem);

void stack_pop(pstack_t stack);

elem_t stack_peek(pstack_t stack);

size_t stack_size(pstack_t stack);

bool stack_is_empty(pstack_t stack);

size_t stack_capacity(pstack_t stack);

void stack_print(pstack_t stack);

#endif /* __STACK__ */
