# Simple automaton reader
This program allows you to read an automaton proprely described in a `.aut` file and following user inputs, tell if a given word is or not accepted by the langage associated to the automaton.
## How to :
This program takes a filepath to an `.aut` file as its only parameter to run.  
For example to run the file `dyck.aut`, simply type :
```
./automaton dyck.aut
```

Once the file is loaded you can input words and the program will indicate if it is an accepted or rejected word.  
If the word is rejected, the program indicates below with a `^` symbol at which letter the it failed to be accepted.  
```
file "example/dyck.aut" correctly read. Please enter your inputs.
()()))()
Rejected :()()))()
error at :    ^
```

To quit the program, simply break out of it (`Ctrl-C` command).
## Note
This program does **not** check if the given `.aut` file is correct.