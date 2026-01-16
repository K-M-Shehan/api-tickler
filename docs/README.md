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

## Day 2 Oct 23rd 12:49 PM
This change took some time as I had to do some trial and error before I got an idea which actually worked (this felt soo good). 

The feature I added was the ability to parse variables references inside of a string. To do this the string token must be extended, and I decided that I would do it in the yacc file instead of regex in the scanner (this would be a critical hit to readability if done). 

I made a separate grammar rule for strings, their structure being QUOTE followed by a section (this section is also another grammer rule {yes its getting a bit complicated but bear with me this is going to be mindblowing, at least for me}), and finally ending with another QUOTE, as a string normally should.

I then implemented the the section between the quotes, it could be nothing, a text section or the variable references (and yes recursion was also sprinkled in for the love of the game).

Current code:

```yacc
variable: 
        LET IDENTIFIER EQUALS value { printf("I see a variable declared and instantiated with a non negative number or string\n"); }        
;

value:
     NON_NEG_INT
     | string
;

string:
      QUOTE parts QUOTE
;

parts:
     /*nothing*/
     | parts TEXT_SECTION
     | parts var_ref
;

var_ref:
       DOLLAR IDENTIFIER
;
```

```lex
"\""    { return QUOTE; } 
"\$"    { return DOLLAR; } 
"="     { return EQUALS; } 

[A-Za-z_][A-Za-z0-9_]* { return IDENTIFIER; } 
[^"\\$\\\n]+           { return TEXT_SECTION; }
```

Now this is the interesting part, I compiled everything and ran the parser, and to my suprise instead of getting the expected output I got:

```bash
❯ ./parser 
let name = "sam" 
Error: syntax error
```

I tried a bunch of things, changing a lot of stuff, but nothing worked. So I tried to understand what it was actually parsing and realized that the text "sam" could be parsed as an INDENTIFIER and not a TEXT_SECTION, so I changed my code as follows:
```yacc
string:
      QUOTE parts QUOTE
;

parts:
     /*nothing*/
     | parts IDENTIFIER /*identifier here is just the text part that comes after the quote*/
     | parts var_ref
;
```

I also removed the TEXT_SECTION token from the parser and scanner, and it worked.

But that also came at a cost:
```bash
❯ ./parser
let name = "sam"
I see a variable declared and instantiated with a non negative number or string
let url = "/admin"
Error: syntax error
```

But this time I was ready, I just added another part to the RHS of the parts rule and it worked.

```yacc
parts:
     /*nothing*/
     | parts IDENTIFIER /*identifier here is just the text part that comes after the quote*/
     | parts SLASH IDENTIFIER
     | parts var_ref
;
```

```lex
"/"                     { return SLASH; }
```

As I was writing this I realized that this was getting too complex and I am ready to compromize some readability to make this simpler (I'm going to do it all the scanner with regex), I hope comments will make it more readable.
