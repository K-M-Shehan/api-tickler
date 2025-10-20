%{
#include "parser.tab.h"
%}

%%
"let"                   { return LET; }
"//".*                  { /*skips the whole line*/ }
[0-9]+                  { return NON_NEG_INT; }

"config"                { return CONFIG; }
"base_url"              { return BASE_URL; }
"header"                { return HEADER; }
"test"                  { return TEST; }
"GET"                   { return GET; }
"POST"                  { return POST; }
"PUT"                   { return PUT; }
"DELETE"                { return DELETE; }
"expect"                { return EXPECT; }
"status"                { return STATUS; }
"body"                  { return BODY; }
"contains"              { return CONTAINS; }

[A-Za-z_][A-Za-z0-9_]*  { return IDENTIFIER; }

"="                     { return EQUALS; }
[ \t\n]+                { /* skip whitespace */ }
.                       { return yytext[0]; }
%%

// TODO implement strings, supports \* and \\
// TODO no vars outside strings/paths
