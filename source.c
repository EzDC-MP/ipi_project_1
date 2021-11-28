/*AUTOMAT READER*/
/*NE COMPILE PAS*/

#include <stdio.h>
#include <errno.h> /*include to handle error*/
#include <string.h>

/*  @requires   : filename links to an existing file name
    @assigns    : n_states, action_matrix, reduce_n, reduce_state, shift_matrix, link_matrix 
    @ensures    : 
        n_states is the number of states of the given automaton,
        action_matrix is the matrix encoding the action function of the automaton,
        reduce_n is an array encoding the first values of the function reduce of the automaton,
        reduce_state is an array encoding the second values of the function reduce of the automaton,
        shift_matrix is the matrix encoding the shift function of the automaton,
        link_matrix is the matrix encoding the link function of the automaton,
*/
unpack(char *filename, int *n_state, char *(**action_matrix), int * *reduce_n, {

}

int main(int argc, char **argv) {
   /*Look for valid input*/
   if (argc != 2) {
       fprintf(stderr, "%s : Error : expected 1 arguments, got %i.\n", argv[0], (argc-1));
       return 1;
    }
    typedef enum action 
        {REJECT = 0, ACCEPT = 1, SHIFT = 2, REDUCE = 3}
        action ;




    /*debug commands*/
    action a = REJECT;
    printf("value a is : %i\n", a);
    printf("a==0 : %i\n", (a==0));
    int b = ACCEPT;
    printf("b : %i\n", b);
    return 0;
}