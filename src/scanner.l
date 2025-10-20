%{
#include "parser.tab.h"
%}

%%
"config"    { return CONFIG; }
"test"      { return TEST; }
[ \t\n]+    { /* skip whitespace */ }
.           { return yytext[0]; }
%%
