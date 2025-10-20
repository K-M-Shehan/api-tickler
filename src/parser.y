%{
#include <stdio.h>
#include <stdlib.h>

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
      | TEST      { printf("Saw TEST\n"); }
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
    return yyparse();
}

