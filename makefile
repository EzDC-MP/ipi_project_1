all: exec

CC=gcc
FLAGS=-Wall -Wextra
OBJ=stack.o source.o 

stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c $^

stack_exec: stack.c stack.h
	$(CC) $(FLAGS) -o $@ $^

source.o: source.c stack.h
	$(CC) $(FLAGS) -c $^

exec: $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

exec_d: $(OBJ)
	$(CC) $(FLAGS) -g -o $@ $^