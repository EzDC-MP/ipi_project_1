/*AUTOMAT READER*/
/*NE COMPILE PAS*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h> /*include to handle error*/
#include <string.h>

/* since the function use integers, I used an enum type to add better readability to the code*/
typedef enum action 
    {REJECT = 0, ACCEPT = 1, SHIFT = 2, REDUCE = 3}
    action ;

/*  @requires   : filename links to an existing file name
    @assigns    : *n_states, *action_matrix, *reduce_n, *reduce_state, *shift_matrix, *link_matrix 
    @ensures    : 
        n_states is the number of states of the given automaton,
        action_matrix is a matrix encoding the action function of the automaton,
        reduce_n is a char array encoding the first values of the function reduce of the automaton,
        reduce_state is an array encoding the second values of the function reduce of the automaton,
        shift_matrix is a matrix encoding the shift function of the automaton,
        link_matrix is a matrix encoding the link function of the automaton,
*/
void unpack(char *filename, int *n_state, char * **action_matrix, char * *reduce_n, char * *reduce_state, char * **shift_matrix, char * **link_matrix) {
    FILE *f = fopen(filename, "r");
    char buf[256];

    /*get the number of states*/
    fgets(buf,256,f);
    *n_state = atoi(&buf[2]);

    /*fills the action_matrix from file*/
    (*action_matrix) = malloc((*n_state)*sizeof(char *));
    for(int i; i<(*n_state); i+=1) {
        (*action_matrix)[i] = malloc(127*sizeof(char));
        fread((*action_matrix)[i],127,sizeof(char),f);
    }
    fgets(buf,256,f); /*clear the buffer and "skip" the '\n' octal (see fgets doc ; fgets stop when reading newline)*/

    /*fills the reduce_n array from file*/
    (*reduce_n) = malloc((*n_state)*sizeof(char));
    fread((*reduce_n),sizeof(char),(*n_state),f);
    fgets(buf,256,f); /*same thing here*/

    /*fills the reduce_n array from file*/
    (*reduce_state) = malloc((*n_state)*sizeof(char));
    fread((*reduce_n),sizeof(char),(*n_state),f);
    fgets(buf,256,f);

    /*fills the shift_matrix from file*/
    (*shift_matrix) = malloc((*n_state)*sizeof(char *));
    for(int i; i<(*n_state); i+=1) {
        (*shift_matrix)[i] = malloc(127*sizeof(char));
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
        (*link_matrix)[i] = malloc(127*sizeof(char));
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
    @ensures    : print the different matrix and table;*/
void debug_print_tab(int n_state, char **action_matrix, char *reduce_n, char *reduce_state, char **shift_matrix, char **link_matrix, FILE *stream){
    printf("isok");
    fprintf(stream, "n_state :\n %i", n_state);
    for (int i=0; i<(n_state); i+=1){
        fprintf(stream, "action_matrix[%i] :", i);
        for (int j=0; j<(127); j+=1)
            fprintf(stream, "\\%o", action_matrix[i][j]);
        fprintf(stream, "\n");
    }

    fprintf(stream, "reduce_n :");
    for (int i=0; i<(n_state); i+=1)
        fprintf(stream, "\\%o", reduce_n[i]);
    fprintf(stream, "\n");

    fprintf(stream, "reduce_state :");
    for (int i=0; i<(n_state); i+=1)
        fprintf(stream, "\\%o", reduce_state[i]);
    fprintf(stream, "\n");

    for (int i=0; i<(n_state); i+=1){
        fprintf(stream, "shift_matrix[%i] :", i);
        for (int j=0; j<(127); j+=1)
            fprintf(stream, "\\%o", shift_matrix[i][j]);
        fprintf(stream, "\n");
    }

    for (int i=0; i<(n_state); i+=1){
        fprintf(stream, "link_matrix[%i] :", i);
        for (int j=0; j<(127); j+=1)
            fprintf(stream, "\\%o", link_matrix[i][j]);
        fprintf(stream, "\n");
    }
    fflush(stream);
}

int main(int argc, char **argv) {
   /*Look for valid input*/
   if (argc != 2) {
       fprintf(stderr, "%s : Error : expected 1 arguments, got %i.\n", argv[0], (argc-1));
       return 1;
    }

    /*debug*/
    /*
    action a = REJECT;
    printf("value a is : %i\n", a);
    printf("a==0 : %i\n", (a==0));
    int b = ACCEPT;
    printf("b : %i\n", b);
    */

    /*
    FILE *f = fopen("example/dyck.aut", "r");
    char buf_n_state[5];
    fgets(buf_n_state,5,f);
    printf("%c\n", buf_n_state[0]);
    printf("%c\n", buf_n_state[1]);
    printf("%c\n", buf_n_state[2]);
    printf("%c\n", buf_n_state[3]);

    int n_state = atoi(&buf_n_state[2]);
    printf("%d\n", n_state);

    printf("sizeof char : %i\n", sizeof(char));
    */

    int n_state;
    char **action_matrix;
    char *reduce_n;
    char *reduce_state;
    char **shift_matrix;
    char **link_matrix;
    FILE *f2 = fopen("log", "w+"); //probablement une erreur de permission
    unpack(argv[1], &n_state, &action_matrix, &reduce_n, &reduce_state, &shift_matrix, &link_matrix);
    debug_print_tab(n_state, action_matrix, reduce_n, reduce_state, shift_matrix, link_matrix, f2);
    return 0;
}