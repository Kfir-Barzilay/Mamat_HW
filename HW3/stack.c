#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
/*-------------------------------------------------------------------------*/
typedef struct node {
    elem_t elem;
    struct node *next;
} node_t;

typedef struct stack {
    node_t *top;
    size_t size;
    size_t max;
    clone_t clone;
    destroy_t destroy;
    print_t print;
} stack_t;

//create an empty stack
pstack_t stack_create(size_t max_num_of_elem, 
                      clone_t clone,
                      destroy_t destroy,
                      print_t print) {  
    if(clone == NULL || destroy == NULL || print == NULL)
        return NULL;
    pstack_t stack = (pstack_t) malloc(sizeof(stack_t)); 
    if (stack == NULL) {
        return NULL;
    }
    
    stack->top = NULL;
    stack->size = 0;
    stack->max = max_num_of_elem;
    stack->clone = clone;
    stack->destroy = destroy;
    stack->print = print;
    return stack;
}

/*destroy the stack by freeing each node,
the element inside them and the stack*/
Result stack_destroy(pstack_t stack) { 
    if(stack == NULL)
        return FAIL;
    for (size_t i = 0; i< stack->size ; i++) {
        stack_pop(stack);
    }
    free(stack);
    return SUCCESS;
}

//adding node to the stack
Result stack_push(pstack_t stack, elem_t elem) { 
    if(stack == NULL || elem == NULL)
        return FAIL;
    if (stack->size >= stack->max) {
        return FAIL;
    }
    node_t *node = (node_t*) malloc(sizeof(node_t)); 
    if (node == NULL) {
        return FAIL;
    }
    node->elem = stack->clone(elem); 
    node->next = stack->top;
    stack->top = node;
    stack->size++;
    return SUCCESS;
}

//extract the top node from the stack and free the memory
void stack_pop(pstack_t stack) { 
    if(stack == NULL)
        return;
    if (stack->size > 0) {
        node_t *temp = stack->top->next;
        stack->destroy(stack->top->elem); 
        free(stack->top); //second free
        stack->top = temp;
        stack->size--;
    }
}

elem_t stack_peek(pstack_t stack) { 
    if(stack == NULL)
        return NULL;
    if (stack->size != 0) {
        return stack->top->elem;
    }
    return NULL;
}

//return the number of elements in the stack
size_t stack_size(pstack_t stack) {
    if(stack == NULL)
        return 0;
    return stack->size;
}

//check if the stack is empty
bool stack_is_empty(pstack_t stack) {
    if(stack == NULL)
        return false;
    return (stack->size == 0);
}

/*return the maximum elements that
the stack can hold of the stack*/
size_t stack_capacity(pstack_t stack) {
    if(stack == NULL)
        return 0;
    return stack->max - stack->size;
}

//print the stack according to LIFO
void stack_print(pstack_t stack) { 
    if(stack == NULL)
        return;
    node_t *temp = stack->top;
    for (size_t i = 0; i< stack->size ; i++) {
        stack->print(temp->elem);
        temp = temp->next;
    }
}
