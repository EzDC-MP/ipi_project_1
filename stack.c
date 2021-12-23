#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack{
    char val;
    struct stack *next;
};

stack empty_stack(){
    return NULL;
}

int is_empty_stack(stack s){
    return (s == NULL);
}

void push_stack(char c, stack *s){
    stack a = malloc(sizeof(struct stack));
    a->val = c;
    a->next = *s;
    *s = a;
}

char pop_stack(stack *s){
    stack f = *s;
    char e = (*s)->val;
    (*s) = (*s)->next;
    free(f);
    return e;
}

char peek_stack(stack s){
    return s->val;
}

/*  requires : s stack;
    assigns : nothing;
    ensures : prints s;*/
void print_debug_stack(stack s){
    stack q = s;
    while (q != NULL){
        printf("\\/\n[  %c  ]\n", q->val);
        q = q->next;
    }
    printf("=======\n");
}

/*
int main(){
    stack s = empty_stack();
    print_debug_stack(s);
    push_stack('c', &s);
    push_stack('o', &s);
    push_stack('w', &s);
    push_stack('o', &s);
    print_debug_stack(s);
    print_debug_stack(s);
    print_debug_stack(s);
    printf("is_empty : %i\n", is_empty_stack(s));
    printf("popped %c\n", pop_stack(&s));
    printf("popped %c\n", pop_stack(&s));
    print_debug_stack(s);
    printf("peeked top is : %c\n", peek_stack(s));
    printf("popped %c\n", pop_stack(&s));
    printf("popped %c\n", pop_stack(&s));
    printf("is_empty : %i\n", is_empty_stack(s));
    print_debug_stack(s);
    return 0;
}
*/