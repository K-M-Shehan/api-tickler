%{
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
int yyparse();

int yylex(void);
int yyerror(const char *s);
%}

%token CONFIG TEST

%%
commands: /*could be zero or more commands*/
        /*could be nothing*/
        | commands command
;

command: /*the command could be config or test*/
      CONFIG    { printf("Saw CONFIG\n"); }
      | TEST    { printf("Saw TEST\n"); }
;
%%

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

int yywrap(void) {
    return 1;
}

int main(void) {
  yyin = fopen("input.test", "r"); // open the input.test file
  if(!yyin) { // error handing for when there is no file
    perror("input.test");
    return 1;
  }
  yyparse(); // start parsing from the file opened
  fclose(yyin);
  return 0;
}

