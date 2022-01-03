## Simple automaton reader
This program allows you to read an automaton proprely described in a .aut file, and then following user input, tell if a word is or not accepted by the langage associated to the automaton.
# How to :
This program takes a filepath to a correct .aut file to run.
for example, to run the file dyck.aut, simply run
```
./automaton dyck.aut
```
Once the file is loaded, you can input words and the program will indicate if it is an Accepted word or Rejected one.
If the word rejected, the program indicate with a `^` symbol below the letter where the word failed to be accepted.
For example :
```
file "example/dyck.aut" correctly read. Please enter your inputs.
()()))()
Rejected :()()))()
error at :    ^
```

To quit the program, simply break out of it (with `Ctrl-C` for example).
# Note
This program does **not** check if the given `.aut` file is correct.
