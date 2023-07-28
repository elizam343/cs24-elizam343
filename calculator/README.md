# Calculator

_Due Wednesday, July 26th, before midnight Pacific Time._

In this assignment you'll implement a simple calculator that understands Reverse
Polish Notation (also known as postfix notation).  This is an alternative way to
write mathematical expressions.  Each operator is written _after_  its operands.
For example, the standard (infix) expression...

```
7 - 4
```

...would become:

```
7 4 -
```

And the more complicated equation...

```
((1 + 2) * (7 - 3)) ^ 2
```

...would become:

```
1 2 + 7 3 - * 2 ^
```

Reverse Polish Notation is much easier for computers to work with (notice how no
parentheses  are required),  so many  old calculators used it.  In fact, You can
think of Reverse Polish Notation  as a stream of instructions  for a very simple
type of computer: a **stack machine**.


## Stack Machines

A stack machine is a  computer that stores its data  on a stack.  To evaluate an
RPN expression, a stack machine starts with an empty stack.  It then reads input
as a sequence of **tokens**, from left to right:

- If the token is a number, the stack machine pushes it onto the stack.
- If the token is an operator,  the stack machine pops numbers off of the stack,
  performs the operation on those numbers, and pushes the result onto the stack.

If everything goes well,  there will be one number on the stack after all tokens
have been processed.  This is the final value of the input expression.


## Your Assignment

- Implement a stack that stores doubles.
- Implement an RPN calculator using your stack class.
- You can't use any container types from the standard library.
- Make sure you don't print anything that isn't explicitly allowed.
- Make sure you don't have any memory leaks.


## The Stack

The  `Stack.h`  file describes an  abstract  Stack  data structure.  Implement a
concrete Stack in  `MyStack.h` and `MyStack.cpp`.  You'll probably want to write
a vector or a singly linked list for the underlying structure.


## The Calculator

Now use your stack  to power a calculator.  Your calculator should read one line
at a time from standard input. Each line will be a sequence of tokens, separated
by whitespace. Tokens will either be numbers  (`double`s like `-12`, `0.443`, or
`+57000.2`) or one of the following operators:

- `+` adds two numbers (`3 4 +` is `7`).
- `-` subtracts one number from another (`2 6 -` is `-4`).
- `*` multiplies two numbers (`2 7 *` is `14`).
- `/` divides one number by another (`7 -4 /` is `-1.75`).
- `%` returns the remainder after dividing one number by another (`0.7 0.3 %` is `0.1`).
- `^` raises one number to the power of another (`3 2 ^` is `9`).
- `~` negates a number (`8 ~` is `-8`).

There are  a few things that could go wrong.  If you hit these cases,  print the
correct error message and move on to the next line of input.  If multiple errors
apply, print whichever comes first in this list:

- Print `Unknown token.` if you encounter a token that's not a number or one of
  the operators described above.
- Print `Not enough operands.` if there aren't enough numbers on the stack for
  the current operator.
- Print `Division by zero.` if you ever attempt to divide (or take a remainder
  after division) by zero.
- Print `Too many operands.` if there's more than one number on the stack after
  evaluating the entire expression.
- Print `No expression.` if the stack is empty after evaluating the entire
  expression (this can only happen if there are no tokens at all).

If no error occurred, print the result prefixed by `= ` and move on  to the next
line of input.  You don't need to format  the number;  the default  C++ `double`
format will give you the expected output:

```cpp
double result = ???
std::cout << "= " << result << std::endl;
```

When you reach  the end of the input stream,  your program should exit.  You can
simulate this by sending an end-of-file (EOF) signal to your program. Do this by
pressing  `Ctrl` + `D` on Linux and Mac,  or by pressing  `Ctrl` + `Z`  and then
`Enter` on Windows.

Once your program is working, you'll be able to interact with it:

```
[alice@lookingglass calculator]$ ./calc
hello
Unknown token.
7 4 -
= 3
1 2 + 7 3 - * 2 ^
= 144
```

## Hints

- The `double` type doesn't support all the operators you need, but the standard
  `cmath` header contains additional math functions.
- Using `std::getline()` makes reading one line at a time very easy.
- A `std::stringstream` will be useful for splitting a line into tokens.
- The  `>>`  operator has an annoying tendency  to interpret  `+` and `-` as the
  `double` zero.  See if your tokens are  operators  before trying  to interpret
  them as numbers!
- For a token to be a valid number, the  entire token  must be a number.  `tuba`
  and `2ba` are both invalid tokens, but a lot of parsing methods will parse the
  latter as `2`, ignoring the trailing non-digits.  Watch out for this!
- https://xkcd.com/645/
