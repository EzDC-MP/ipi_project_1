/*AUTOMAT READER*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> /*include to handle error*/
#include <string.h>
#include "stack.h"

/* since the function use integers, I used an enum type to add better readability to the code*/
typedef enum action 
    {REJECT = 0, ACCEPT = 1, SHIFT = 2, REDUCE = 3}
    action ;

/*  @requires   : filename links to an existing file name
    @assigns    : *n_states, *action_matrix, *reduce_n, *reduce_letter, *shift_matrix, *link_matrix 
    @ensures    : 
        n_states is the number of states of the given automaton,
        action_matrix is a matrix encoding the action function of the automaton,
        reduce_n is a char array encoding the first values of the function reduce of the automaton,
        reduce_letter is an array encoding the second values of the function reduce of the automaton,
        shift_matrix is a matrix encoding the shift function of the automaton,
        link_matrix is a matrix encoding the link function of the automaton,*/
void unpack(char *filename, int *n_state, char * **action_matrix, char * *reduce_n, char * *reduce_letter, char * **shift_matrix, char * **link_matrix) {
    FILE *f = fopen(filename, "r");
    char buf[256];

    /*get the number of states*/
    fgets(buf,256,f);
    *n_state = atoi(&buf[2]);

    /*fills the action_matrix from file*/
    (*action_matrix) = malloc((*n_state)*sizeof(char *));
    for(int i; i<(*n_state); i+=1) {
        (*action_matrix)[i] = malloc(128*sizeof(char));
        fread((*action_matrix)[i],128,sizeof(char),f);
    }
    fgets(buf,256,f); /*clear the buffer and "skip" the '\n' octal (see fgets doc ; fgets stop when reading newline)*/

    /*fills the reduce_n array from file*/
    (*reduce_n) = malloc((*n_state)*sizeof(char));
    fread((*reduce_n),sizeof(char),(*n_state),f);
    fgets(buf,256,f); /*same thing here*/

    /*fills the reduce_letter array from file*/
    (*reduce_letter) = malloc((*n_state)*sizeof(char));
    fread((*reduce_letter),sizeof(char),(*n_state),f);
    fgets(buf,256,f);

    /*fills the shift_matrix from file*/
    (*shift_matrix) = malloc((*n_state)*sizeof(char *));
    for(int i; i<(*n_state); i+=1) {
        (*shift_matrix)[i] = malloc(128*sizeof(char));
    }
    fread(buf,sizeof(char),3,f);
    while (buf[0]!='\255' && buf[1]!='\255' && buf[2]!='\255'){ /* terminating instruction */ // <-- Justifier que la boucle termine !!
        //printf("allocating shift_matrix[%i][%i]\n", (int) buf[0], (int) buf[1]);
        (*shift_matrix)[(int) buf[0]][(int) buf[1]] = buf[2];
        fread(buf,sizeof(char),3,f);
    }
    
    /*fills the link_matrix from file*/
    (*link_matrix) = malloc((*n_state)*sizeof(char *));
    for(int i; i<(*n_state); i+=1) {
        (*link_matrix)[i] = malloc(128*sizeof(char));
    }
    fread(buf,sizeof(char),3,f);
    while (buf[0]!='\255' && buf[1]!='\255' && buf[2]!='\255'){ /* terminating instruction */ // <-- Là aussi.
        (*link_matrix)[(int) buf[0]][(int) buf[1]] = buf[2];
        fread(buf,sizeof(char),3,f);
    }
    fclose(f);
}

/*  @requires   : valid entries;
    @assigns    : nothing;
    @ensures    : print the different matrix and table into stream;*/
void debug_print_tab(int n_state, char **action_matrix, char *reduce_n, char *reduce_letter, char **shift_matrix, char **link_matrix, FILE *stream){
    fprintf(stream, "n_state : %i\n", n_state);
    for (int i=0; i<(n_state); i+=1){
        fprintf(stream, "action_matrix[%i] :", i);
        for (int j=0; j<(128); j+=1)
            fprintf(stream, "%i ", action_matrix[i][j]);
        fprintf(stream, "\n");
    }

    fprintf(stream, "reduce_n :");
    for (int i=0; i<(n_state); i+=1)
        fprintf(stream, "%i ", reduce_n[i]);
    fprintf(stream, "\n");

    fprintf(stream, "reduce_letter :");
    for (int i=0; i<(n_state); i+=1)
        fprintf(stream, "%c  ", reduce_letter[i]);
    fprintf(stream, "\n");

    for (int i=0; i<(n_state); i+=1){
        fprintf(stream, "shift_matrix[%i] :\n", i);
        for (int j=0; j<(128); j+=1)
            fprintf(stream, "%i ", shift_matrix[i][j]);
        fprintf(stream, "\n");
    }

    for (int i=0; i<(n_state); i+=1){
        fprintf(stream, "link_matrix[%i] :", i);
        for (int j=0; j<(128); j+=1)
            fprintf(stream, "%i ", link_matrix[i][j]);
        fprintf(stream, "\n");
    }
    fflush(stream);
}

/*  @requires   : state < n_state, letter <= 127;
    @assigns    : nothing;
    @ensures    : returns action(state,letter) from action_matrix[state][letter];*/
action action_func(char state, char letter, char **action_matrix){
    return action_matrix[(int) state][(int) letter];
}

/*  @requires   : state < n_state, letter <= 127;
    @assigns    : *s;
    @ensures    : pushes shift(state,letter) from shift_matrix[state][letter]
                  ontop *s;*/
void shift_func(char state, char letter, char **shift_matrix, stack *s){
    char pushed_state = shift_matrix[(int) state][(int) letter];
    push_stack(pushed_state, s);
}

/*  @requires   : state < n_state, letter <= 127;
    @assigns    : *s;
    @ensures    : pushes link(state,letter) from link_matrix[state][letter]
                  ontop *s;*/
void link_func(char state, char letter, char **link_matrix, stack *s){
    char pushed_state = link_matrix[(int) state][(int) letter];
    push_stack(pushed_state, s);
}

/*  @requires   : char *word of length n, i<n;
    @assigns    : nothing;
    @ensures    : prints in stdout word with a '^' under the ith character of word;*/
void raise_error(char *word, int i){
    char *word_ = malloc(256);
    sscanf(word, "%[^\n]\n", word_);
    printf("%s\n", word_);
    printf("error at :");
    for(int j=0;j<i;j+=1){
        printf(" ");
    }
    printf("^\n");
    free(word_);
}

int main(int argc, char **argv) {
   /*Look for valid input, and raises error if file not given*/
    if (argc != 2) {
       fprintf(stderr, "%s : Error : expected 1 arguments, got %i.\n", argv[0], (argc-1));
       return 1;
    }

    /*if true, executable while print various values used for debugging*/
    int DEBUG_FLAG = 0;

    /*init values and fills them with data from file*/
    int n_state;
    char **action_matrix;
    char *reduce_n;
    char *reduce_letter;
    char **shift_matrix;
    char **link_matrix;
    unpack(argv[1], &n_state, &action_matrix, &reduce_n, &reduce_letter, &shift_matrix, &link_matrix);
    if (DEBUG_FLAG)
        debug_print_tab(n_state, action_matrix, reduce_n, reduce_letter, shift_matrix, link_matrix, stdout);

    /*init the state stack*/
    stack state_stack = empty_stack();

    /*init procedure*/
    printf("file \"%s\" correctly read. Please enter your inputs.\n", argv[1]);
    char *user_input = malloc(256);/*buffer of length 256 to stock user input*/
    while (1){
        /*get user input*/
        fgets(user_input, 256, stdin);
        if (DEBUG_FLAG){
            printf("user_input : %s\n", user_input);
        }

        /*empty the stack before reading word and then init the stack at state 0*/
        while (state_stack != NULL)
            pop_stack(&state_stack);
        push_stack(0, &state_stack);

        /*init index i at the first character of user input
          and the first current letter and state read from user_input*/
        int i=0;
        char current_letter = user_input[i];
        char current_state = peek_stack(state_stack);

        /*Boolean flag to quit while loop*/
        int DONE_FLAG = 0;

        //Pareil ! détailler plus la boucle while ici !!!
        while (DONE_FLAG != 1){
            current_letter = user_input[i];
            current_state = peek_stack(state_stack);
            action action = action_func(current_state, current_letter, action_matrix);

            switch (action){
                case REJECT:{
                    printf("Rejected :");
                    DONE_FLAG = 1;
                    raise_error(user_input, i);
                    break;
                }
                case ACCEPT:{
                    printf("Accepted\n");
                    DONE_FLAG = 1;
                    break;
                }
                case SHIFT:{
                    shift_func(current_state, current_letter, shift_matrix, &state_stack);
                    i+=1;
                    break;
                }
                case REDUCE:{
                    int j=0;
                    int n = reduce_n[(int) current_state];
                    char state_letter = reduce_letter[(int) current_state]; 
                    while(j<n){
                        pop_stack(&state_stack);
                        j+=1;
                    }
                    current_state = peek_stack(state_stack);
                    link_func(current_state, state_letter, link_matrix, &state_stack);
                    break;
                }
            }
        }
    }
    return 0;
}