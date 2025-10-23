# Devlog

## Day 1 Oct 20th 2:18 PM
I have chosen Flex and Bison instead of Jflex and cup because I'm more comfortable working with C than Java. Also Jflex and cup don't have much learning resources (examples, documentation and community help) when comparing with something like Flex and Bison.

Flex and Bison also have a more predictable syntax and also less verbose (i dig this) than Jflex and cup.

## Day 1 Oct 20th 2:40 PM
I have implemented a small parser and scanner with bison and flex, it was awesome.

## Day 1 Oct 20th 3:56 PM 
I have made it so that the parser can now read from a file called "input.test", the next step would be to make it so that we can specify the name of the test file.

I learnt that flex normally reads input from a variable called yyin which takes stdin as input (the command line input stream), what I did was that I made yyin point to a specific file (that is input.test), so the lexer read from there instead of from the command line.

## Day 1 Oct 20th 5:13 PM
The parser can now accept any file given to it (the main function is accepting arguements now) or even go with the command line. 

Also I have defined a bunch of keywords and implemented the ability to declare and instantiate a variable with a non negative number, but we still can't store the variables.

Next I have to setup proper error handling for the variable definition and instatiation.

## Day 1 Oct 20th 5:43 PM
I changed the comment rule in the scanner to completely omit comment lines, so it no longer returns anything.

## Day 2 Oct 23rd 10:40 AM
Couldn't work on this project for some time because of some close deadlines of other projects.

I introduced strings to the parser, and turns out bison cannot nest paranthesis in grammar rules as they also get recognized as literal token if not defined as such.

So I made a new grammar rule for values of variables and now the parser can understand strings. Yay.
