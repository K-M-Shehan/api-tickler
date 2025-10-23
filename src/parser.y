%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
int yyparse();

int yylex(void);
int yyerror(const char *s);
%}

%token LET IDENTIFIER NON_NEG_INT
%token CONFIG BASE_URL HEADER TEST
%token GET POST PUT DELETE
%token EXPECT STATUS BODY CONTAINS
%token EQUALS STRING LBRACE RBRACE

%%
commands: /*could be zero or more commands*/
        /*could be nothing*/
        | commands command
;

command: /*the command could be config or test*/
      CONFIG    { printf("Saw CONFIG\n"); }
      | TEST    { printf("Saw TEST\n"); }
      | variable
;

variable: 
        LET IDENTIFIER EQUALS value { printf("I see a variable declared and instantiated with a non negative number or string\n"); }        
;

value:
     NON_NEG_INT
     | STRING
;

%%

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

int yywrap(void) {
    return 1;
}

int main(int argc, char **argv) {
  if(argc > 1) {
    yyin = fopen(argv[1], "r"); // open the file and feed it to the yyin var
  
    if(!yyin) { // error handing for when there is no file
      perror(argv[1]);
      return 1;
    }
  }
  else {
    yyin = stdin; // if there is no file specified go with stdin
  }
  int ret = yyparse(); // parse input
  if(yyin != stdin) {
    fclose(yyin);
    printf("Task complete, exiting ...\n");
  }
  return ret;
}

