# BigInt calculator
This is a command line program from a school project. This big Int calculator suport 3 operation type `+` `*` `^` addition, multiplication and exponentiation.

The operation should be prefix, meaning the operation type comes first and then the operands. The result of a binary operation is used for the next binary operation:
```
+ 5 10 20 = 35
* 2 3 10 = 30
```

The program accept an argument:

`-h` : provide an help on how to use the software.

`-v`: a verbose mode, useful when the input is a text file. If a text file is used as input comment starting with `#` are omitted. 

Type `quit` to exit the program.

## Installation
To compile the program on linux use the command:

`g++ --std=c++11 calc.cpp calculator.cpp`
