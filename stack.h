/*char stack*/

/* abstract type of stack*/
typedef struct stack *stack;

/*  requires: nothing;
    assigns : nothing;
    ensures : returns an empty stack (NULL)*/
stack empty_stack();

/*  requires: valid stack;
    assigns : nothing;
    ensures : returns 0 if stack empty, else 1;*/
int is_empty_stack(stack s);

/*  requires: '\0' <= c <= '\177', *s valid stack;
    assigns : *s;
    ensures : pushes c ontop of *s;*/
void push_stack(char c, stack *s);

/*  requires: *s not empty;
    assigns : *s;
    ensures : pop last element ontop of stack *s;*/
char pop_stack(stack *s);

/*  requires: s not NULL;
    assigns : nothing;
    ensures : returns the top value of the stack without popping it out;*/
char peek_stack(stack s);