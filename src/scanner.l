%{
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>

extern int yylineno;

/* Process escape sequences in strings */
char* process_escapes(const char* str, int len) {
    char* result = malloc(len + 1);
    char* out = result;
    const char* in = str;
    const char* end = str + len;
    
    while (in < end) {
        if (*in == '\\' && (in + 1) < end) {
            in++;  // Skip backslash
            switch (*in) {
                case 'n':  *out++ = '\n'; break;
                case 't':  *out++ = '\t'; break;
                case 'r':  *out++ = '\r'; break;
                case '\\': *out++ = '\\'; break;
                case '"':  *out++ = '"'; break;
                default:   *out++ = *in; break;
            }
            in++;
        } else {
            *out++ = *in++;
        }
    }
    *out = '\0';
    return result;
}

/* Multiline triple-quoted string support */
char* multi_buf = NULL;
int multi_len = 0;

void append_multi(const char* s, int len) {
    if (!s || len <= 0) return;
    if (!multi_buf) {
        multi_buf = malloc(len + 1);
        memcpy(multi_buf, s, len);
        multi_len = len;
        multi_buf[multi_len] = '\0';
    } else {
        multi_buf = realloc(multi_buf, multi_len + len + 1);
        memcpy(multi_buf + multi_len, s, len);
        multi_len += len;
        multi_buf[multi_len] = '\0';
    }
}

/* Trim leading and trailing whitespace from buffer */
void trim_multi() {
    if (!multi_buf || multi_len == 0) return;
    
    char* start = multi_buf;
    char* end = multi_buf + multi_len - 1;
    
    /* Trim leading whitespace */
    while (start <= end && (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r')) {
        start++;
    }
    
    /* Trim trailing whitespace */
    while (end >= start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        end--;
    }
    
    /* Calculate new length */
    int new_len = end - start + 1;
    if (new_len <= 0) {
        multi_len = 0;
        multi_buf[0] = '\0';
        return;
    }
    
    /* Shift content if needed */
    if (start != multi_buf) {
        memmove(multi_buf, start, new_len);
    }
    multi_buf[new_len] = '\0';
    multi_len = new_len;
}
%}

%x MULTI

%%
"let"                   { return LET; }
"//".*                  { /* skips the whole line */ }
[0-9]+                  { yylval.num = atoi(yytext); return NUMBER; }

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
"in"                    { return IN; }

";"                     { return SEMICOLON; }
"="                     { return EQUALS; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
".."                    { return DOTDOT; }

[A-Za-z_][A-Za-z0-9_]*  { yylval.str = strdup(yytext); return IDENTIFIER; }

\"\"\"    { if(multi_buf) { free(multi_buf); multi_buf = NULL; multi_len = 0; } BEGIN(MULTI); }

<MULTI>\"\"\"  { 
    trim_multi();
    yylval.str = process_escapes(multi_buf ? multi_buf : "", multi_len);
    if (multi_buf) { free(multi_buf); multi_buf = NULL; multi_len = 0; }
    BEGIN(INITIAL);
    return STRING;
}
<MULTI>\n    { append_multi("\n", 1); }
<MULTI>.     { append_multi(yytext, yyleng); }

\"([^\"\\]|\\[\"\\ntr])*\" { 
    yylval.str = process_escapes(yytext + 1, yyleng - 2);
    return STRING; 
}

[ \t]+                  { /* skip whitespace */ }
\n                      { yylineno++; }
.                       { fprintf(stderr, "Line %d: unexpected character '%s'\n", yylineno, yytext); }
%%
