# Devlog

## Day 1 Oct 20th 2:18 PM
I have chosen Flex and Bison instead of Jflex and cup because I'm more comfortable working with C than Java. Also Jflex and cup don't have much learning resources (examples, documentation and community help) when comparing with something like Flex and Bison.

Flex and Bison also have a more predictable syntax and also less verbose (i dig this) than Jflex and cup.

## Day 1 Oct 20th 2:40 PM
I have implemented a small parser and scanner with bison and flex, it was awesome.

## Day 1 Oct 20th 3:56 PM 
I have made it so that the parser can now read from a file called "input.test", the next step would be to make it so that we can specify the name of the test file.

I learnt that flex normally reads input from a variable called yyin which takes stdin as input (the command line input stream), what I did was that I made yyin point to a specific file (that is input.test), so the lexer read from there instead of from the command line.
