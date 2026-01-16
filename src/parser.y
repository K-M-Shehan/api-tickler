%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern FILE *yyin;
extern int yylineno;
extern char *yytext;

int yylex(void);
void yyerror(const char *s);

/* Enhanced error reporting */
typedef enum {
    ERR_GENERIC,
    ERR_MISSING_IDENTIFIER,
    ERR_MISSING_SEMICOLON,
    ERR_EXPECTED_STRING,
    ERR_EXPECTED_NUMBER,
    ERR_EXPECTED_VALUE,
    ERR_MISSING_BLOCK_START,
    ERR_MISSING_BLOCK_END
} ErrorType;

void report_error(ErrorType type, const char* context);

/* Data structures */
typedef struct Variable {
    char* name;
    char* value;
    int is_number;
    struct Variable* next;
} Variable;

typedef struct Header {
    char* key;
    char* value;
    struct Header* next;
} Header;

typedef struct Assertion {
    enum { ASSERT_STATUS, ASSERT_STATUS_RANGE, ASSERT_HEADER_EQ, ASSERT_HEADER_CONTAINS, ASSERT_BODY_CONTAINS } type;
    char* header_name;
    char* expected_value;
    int status_code;
    int status_min;
    int status_max;
    struct Assertion* next;
} Assertion;

typedef struct Request {
    enum { REQ_GET, REQ_POST, REQ_PUT, REQ_DELETE } method;
    char* path;
    Header* headers;
    char* body;
    Assertion* assertions;
    struct Request* next;
} Request;

typedef struct Test {
    char* name;
    Request* requests;
    struct Test* next;
} Test;

typedef struct Program {
    char* base_url;
    Header* default_headers;
    Variable* variables;
    Test* tests;
} Program;

Program* program;
Header* current_headers = NULL;
char* current_body = NULL;
Request* current_requests = NULL;

/* Forward declarations */
Variable* create_variable(char* name, char* value, int is_number);
Header* create_header(char* key, char* value);
Assertion* create_assertion_status(int status);
Assertion* create_assertion_status_range(int minv, int maxv);
Assertion* create_assertion_header_eq(char* name, char* value);
Assertion* create_assertion_header_contains(char* name, char* value);
Assertion* create_assertion_body_contains(char* value);
Request* create_request(int method, char* path, Header* headers, char* body, Assertion* assertions);
Test* create_test(char* name, Request* requests);
void add_variable(Variable* var);
void add_default_header(Header* header);
void add_test(Test* test);
char* substitute_variables(char* str);
void generate_java_code(Program* prog, const char* filename);

%}

%union {
    int num;
    char* str;
    void* ptr;
}

%token <str> IDENTIFIER STRING
%token <num> NUMBER
%token LET CONFIG BASE_URL HEADER TEST
%token GET POST PUT DELETE
%token EXPECT STATUS BODY CONTAINS IN
%token EQUALS LBRACE RBRACE SEMICOLON DOTDOT

%type <ptr> config_block config_items config_item
%type <ptr> variable_decl value
%type <ptr> test test_body
%type <ptr> statement request_stmt simple_request block_request
%type <ptr> request_block request_item
%type <ptr> assertion_stmt assertion

%%

program:
    /* empty */ { 
        program = malloc(sizeof(Program));
        program->base_url = NULL;
        program->default_headers = NULL;
        program->variables = NULL;
        program->tests = NULL;
    }
    | program config_block
    | program variable_decl
    | program test
;

config_block:
    CONFIG LBRACE config_items RBRACE
;

config_items:
    /* empty */
    | config_items config_item
;

config_item:
    BASE_URL EQUALS STRING SEMICOLON {
        program->base_url = strdup($3);
    }
    | HEADER STRING EQUALS STRING SEMICOLON {
        add_default_header(create_header($2, $4));
    }
;

variable_decl:
    LET IDENTIFIER EQUALS value SEMICOLON {
        add_variable((Variable*)$4);
        ((Variable*)$4)->name = $2;
    }
    | LET EQUALS value SEMICOLON {
        report_error(ERR_MISSING_IDENTIFIER, "let");
        YYABORT;
    }
    | LET IDENTIFIER EQUALS error SEMICOLON {
        report_error(ERR_EXPECTED_VALUE, "");
        YYABORT;
    }
;

value:
    STRING {
        Variable* var = malloc(sizeof(Variable));
        var->value = $1;
        var->is_number = 0;
        var->next = NULL;
        $$ = var;
    }
    | NUMBER {
        Variable* var = malloc(sizeof(Variable));
        var->value = malloc(32);
        sprintf(var->value, "%d", $1);
        var->is_number = 1;
        var->next = NULL;
        $$ = var;
    }
;

test:
    TEST IDENTIFIER LBRACE test_body RBRACE {
        Test* t = create_test($2, current_requests);
        add_test(t);
        current_requests = NULL;
    }
;

test_body:
    /* empty */
    | test_body statement
;

statement:
    request_stmt
    | assertion_stmt
;

request_stmt:
    simple_request
    | block_request
;

simple_request:
    GET STRING SEMICOLON {
        Request* req = create_request(REQ_GET, $2, NULL, NULL, NULL);
        req->next = current_requests;
        current_requests = req;
    }
    | DELETE STRING SEMICOLON {
        Request* req = create_request(REQ_DELETE, $2, NULL, NULL, NULL);
        req->next = current_requests;
        current_requests = req;
    }
;

block_request:
    POST STRING LBRACE request_block RBRACE SEMICOLON {
        Request* req = create_request(REQ_POST, $2, current_headers, current_body, NULL);
        req->next = current_requests;
        current_requests = req;
        current_headers = NULL;
        current_body = NULL;
    }
    | PUT STRING LBRACE request_block RBRACE SEMICOLON {
        Request* req = create_request(REQ_PUT, $2, current_headers, current_body, NULL);
        req->next = current_requests;
        current_requests = req;
        current_headers = NULL;
        current_body = NULL;
    }
    | POST STRING LBRACE RBRACE SEMICOLON {
        Request* req = create_request(REQ_POST, $2, NULL, NULL, NULL);
        req->next = current_requests;
        current_requests = req;
    }
    | PUT STRING LBRACE RBRACE SEMICOLON {
        Request* req = create_request(REQ_PUT, $2, NULL, NULL, NULL);
        req->next = current_requests;
        current_requests = req;
    }
;

request_block:
    /* empty */
    | request_block request_item
;

request_item:
    HEADER STRING EQUALS STRING SEMICOLON {
        Header* h = create_header($2, $4);
        h->next = current_headers;
        current_headers = h;
    }
    | BODY EQUALS STRING SEMICOLON {
        current_body = strdup($3);
    }
;

assertion_stmt:
    EXPECT assertion {
        if (current_requests != NULL) {
            Assertion* a = (Assertion*)$2;
            a->next = current_requests->assertions;
            current_requests->assertions = a;
        }
    }
;

assertion:
    STATUS EQUALS NUMBER SEMICOLON {
        $$ = create_assertion_status($3);
    }
    | STATUS EQUALS NUMBER DOTDOT NUMBER SEMICOLON {
        $$ = create_assertion_status_range($3, $5);
    }
    | STATUS EQUALS STRING SEMICOLON {
        report_error(ERR_EXPECTED_NUMBER, "status");
        fprintf(stderr, "  You wrote: expect status = \"%s\";\n", $3);
        fprintf(stderr, "  Should be: expect status = %s;\n", $3);
        YYABORT;
    }
    | HEADER STRING EQUALS STRING SEMICOLON {
        $$ = create_assertion_header_eq($2, $4);
    }
    | HEADER STRING CONTAINS STRING SEMICOLON {
        $$ = create_assertion_header_contains($2, $4);
    }
    | BODY CONTAINS STRING SEMICOLON {
        $$ = create_assertion_body_contains($3);
    }
;

%%

void report_error(ErrorType type, const char* context) {
    fprintf(stderr, "Error on line %d: ", yylineno);
    
    switch(type) {
        case ERR_MISSING_IDENTIFIER:
            fprintf(stderr, "Expected identifier after '%s', but found '%s'\n", context, yytext);
            fprintf(stderr, "  Hint: Variable and test names must start with a letter or underscore\n");
            fprintf(stderr, "  Example: let userName = \"admin\";\n");
            break;
        case ERR_MISSING_SEMICOLON:
            fprintf(stderr, "Expected ';' after %s, but found '%s'\n", context, yytext);
            fprintf(stderr, "  Hint: All statements must end with a semicolon\n");
            fprintf(stderr, "  Example: GET \"/api/users/42\";\n");
            break;
        case ERR_EXPECTED_STRING:
            fprintf(stderr, "Expected string after '%s', but found '%s'\n", context, yytext);
            fprintf(stderr, "  Hint: String values must be in double quotes\n");
            fprintf(stderr, "  Example: body = \"{ \\\"key\\\": \\\"value\\\" }\";\n");
            break;
        case ERR_EXPECTED_NUMBER:
            fprintf(stderr, "Expected number after '%s', but found '%s'\n", context, yytext);
            fprintf(stderr, "  Hint: Status codes must be numeric (not strings)\n");
            fprintf(stderr, "  Example: expect status = 200;\n");
            break;
        case ERR_EXPECTED_VALUE:
            fprintf(stderr, "Expected value (string or number) after '=', but found '%s'\n", yytext);
            fprintf(stderr, "  Hint: Variables must be assigned a value\n");
            fprintf(stderr, "  Example: let id = 42; or let name = \"test\";\n");
            break;
        case ERR_MISSING_BLOCK_START:
            fprintf(stderr, "Expected '{' to start block, but found '%s'\n", yytext);
            fprintf(stderr, "  Hint: test and config blocks must start with '{'\n");
            break;
        case ERR_MISSING_BLOCK_END:
            fprintf(stderr, "Expected '}' to end block, but found '%s'\n", yytext);
            fprintf(stderr, "  Hint: Make sure all '{' have matching '}'\n");
            break;
        default:
            fprintf(stderr, "%s at '%s'\n", context, yytext);
            break;
    }
}

void yyerror(const char *s) {
    // Try to provide more context based on what we were parsing
    if (strstr(s, "IDENTIFIER")) {
        report_error(ERR_MISSING_IDENTIFIER, "keyword");
    } else if (strstr(s, "SEMICOLON")) {
        report_error(ERR_MISSING_SEMICOLON, "statement");
    } else if (strstr(s, "STRING")) {
        report_error(ERR_EXPECTED_STRING, "keyword");
    } else if (strstr(s, "NUMBER")) {
        report_error(ERR_EXPECTED_NUMBER, "status");
    } else if (strstr(s, "LBRACE")) {
        report_error(ERR_MISSING_BLOCK_START, "");
    } else if (strstr(s, "RBRACE")) {
        report_error(ERR_MISSING_BLOCK_END, "");
    } else {
        // Generic error with helpful context
        fprintf(stderr, "Error on line %d: %s\n", yylineno, s);
        fprintf(stderr, "  Found: '%s'\n", yytext);
        fprintf(stderr, "  Hint: Check syntax near this location\n");
        fprintf(stderr, "  Common issues:\n");
        fprintf(stderr, "    - Missing semicolon after statement\n");
        fprintf(stderr, "    - Missing quotes around string values\n");
        fprintf(stderr, "    - Incorrect token (e.g., string instead of number)\n");
        fprintf(stderr, "    - Missing identifier after 'let' or 'test'\n");
    }
}

int yywrap(void) {
    return 1;
}

Header* create_header(char* key, char* value) {
    Header* h = malloc(sizeof(Header));
    h->key = key;
    h->value = value;
    h->next = NULL;
    return h;
}

Assertion* create_assertion_status(int status) {
    Assertion* a = malloc(sizeof(Assertion));
    a->type = ASSERT_STATUS;
    a->status_code = status;
    a->next = NULL;
    return a;
}

Assertion* create_assertion_status_range(int minv, int maxv) {
    Assertion* a = malloc(sizeof(Assertion));
    a->type = ASSERT_STATUS_RANGE;
    a->status_min = minv;
    a->status_max = maxv;
    a->next = NULL;
    return a;
}

Assertion* create_assertion_header_eq(char* name, char* value) {
    Assertion* a = malloc(sizeof(Assertion));
    a->type = ASSERT_HEADER_EQ;
    a->header_name = name;
    a->expected_value = value;
    a->next = NULL;
    return a;
}

Assertion* create_assertion_header_contains(char* name, char* value) {
    Assertion* a = malloc(sizeof(Assertion));
    a->type = ASSERT_HEADER_CONTAINS;
    a->header_name = name;
    a->expected_value = value;
    a->next = NULL;
    return a;
}

Assertion* create_assertion_body_contains(char* value) {
    Assertion* a = malloc(sizeof(Assertion));
    a->type = ASSERT_BODY_CONTAINS;
    a->expected_value = value;
    a->next = NULL;
    return a;
}

Request* create_request(int method, char* path, Header* headers, char* body, Assertion* assertions) {
    Request* req = malloc(sizeof(Request));
    req->method = method;
    req->path = path;
    req->headers = headers;
    req->body = body;
    req->assertions = assertions;
    req->next = NULL;
    return req;
}

Test* create_test(char* name, Request* requests) {
    Test* t = malloc(sizeof(Test));
    t->name = name;
    Request* prev = NULL;
    Request* curr = requests;
    while (curr != NULL) {
        Request* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    t->requests = prev;
    t->next = NULL;
    return t;
}

void add_variable(Variable* var) {
    var->next = program->variables;
    program->variables = var;
}

void add_default_header(Header* header) {
    header->next = program->default_headers;
    program->default_headers = header;
}

void add_test(Test* test) {
    test->next = program->tests;
    program->tests = test;
}

char* substitute_variables(char* str) {
    if (str == NULL) return NULL;
    
    char* result = malloc(4096);
    result[0] = '\0';
    char* p = str;
    char* out = result;
    
    while (*p) {
        if (*p == '$') {
            p++;
            char varname[256];
            int i = 0;
            while (*p && (isalnum(*p) || *p == '_')) {
                varname[i++] = *p++;
            }
            varname[i] = '\0';
            
            Variable* v = program->variables;
            while (v != NULL) {
                if (strcmp(v->name, varname) == 0) {
                    strcpy(out, v->value);
                    out += strlen(v->value);
                    break;
                }
                v = v->next;
            }
        } else {
            *out++ = *p++;
        }
    }
    *out = '\0';
    
    return result;
}

char* escape_java_string(char* str) {
    if (str == NULL) return "\"\"";
    
    char* result = malloc(strlen(str) * 2 + 3);
    char* out = result;
    *out++ = '"';
    
    while (*str) {
        if (*str == '"') {
            *out++ = '\\';
            *out++ = '"';
        } else if (*str == '\\') {
            *out++ = '\\';
            *out++ = '\\';
        } else if (*str == '\n') {
            *out++ = '\\';
            *out++ = 'n';
        } else if (*str == '\t') {
            *out++ = '\\';
            *out++ = 't';
        } else {
            *out++ = *str;
        }
        str++;
    }
    *out++ = '"';
    *out = '\0';
    
    return result;
}

void generate_java_code(Program* prog, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Error: cannot open output file %s\n", filename);
        return;
    }
    
    // Extract class name from filename (remove path and .java extension)
    const char* basename = strrchr(filename, '/');
    basename = basename ? basename + 1 : filename;
    char classname[256];
    strncpy(classname, basename, sizeof(classname) - 1);
    classname[sizeof(classname) - 1] = '\0';
    char* dot = strrchr(classname, '.');
    if (dot) *dot = '\0';
    
    fprintf(f, "import org.junit.jupiter.api.*;\n");
    fprintf(f, "import static org.junit.jupiter.api.Assertions.*;\n");
    fprintf(f, "import java.net.http.*;\n");
    fprintf(f, "import java.net.*;\n");
    fprintf(f, "import java.time.Duration;\n");
    fprintf(f, "import java.nio.charset.StandardCharsets;\n");
    fprintf(f, "import java.util.*;\n\n");
    
    fprintf(f, "public class %s {\n", classname);
    fprintf(f, "    static String BASE = %s;\n", 
            prog->base_url ? escape_java_string(prog->base_url) : "\"\"");
    fprintf(f, "    static Map<String,String> DEFAULT_HEADERS = new HashMap<>();\n");
    fprintf(f, "    static HttpClient client;\n\n");
    
    fprintf(f, "    @BeforeAll\n");
    fprintf(f, "    static void setup() {\n");
    fprintf(f, "        client = HttpClient.newBuilder().connectTimeout(Duration.ofSeconds(5)).build();\n");
    
    Header* h = prog->default_headers;
    while (h != NULL) {
        fprintf(f, "        DEFAULT_HEADERS.put(%s, %s);\n",
                escape_java_string(h->key), escape_java_string(h->value));
        h = h->next;
    }
    
    fprintf(f, "    }\n\n");
    
    Test* t = prog->tests;
    while (t != NULL) {
        fprintf(f, "    @Test\n");
        fprintf(f, "    void test_%s() throws Exception {\n", t->name);
        
        Request* req = t->requests;
        int req_num = 0;
        while (req != NULL) {
            req_num++;
            
            char* path = substitute_variables(req->path);
            if (path[0] == '/' && prog->base_url) {
                fprintf(f, "        String url%d = BASE + %s;\n", req_num, escape_java_string(path));
            } else {
                fprintf(f, "        String url%d = %s;\n", req_num, escape_java_string(path));
            }
            
            fprintf(f, "        HttpRequest.Builder b%d = HttpRequest.newBuilder(URI.create(url%d))\n",
                    req_num, req_num);
            fprintf(f, "            .timeout(Duration.ofSeconds(10));\n");
            
            if (req->method == REQ_GET) {
                fprintf(f, "        b%d.GET();\n", req_num);
            } else if (req->method == REQ_DELETE) {
                fprintf(f, "        b%d.DELETE();\n", req_num);
            } else if (req->method == REQ_POST) {
                if (req->body) {
                    char* body = substitute_variables(req->body);
                    fprintf(f, "        b%d.POST(HttpRequest.BodyPublishers.ofString(%s));\n",
                            req_num, escape_java_string(body));
                } else {
                    fprintf(f, "        b%d.POST(HttpRequest.BodyPublishers.noBody());\n", req_num);
                }
            } else if (req->method == REQ_PUT) {
                if (req->body) {
                    char* body = substitute_variables(req->body);
                    fprintf(f, "        b%d.PUT(HttpRequest.BodyPublishers.ofString(%s));\n",
                            req_num, escape_java_string(body));
                } else {
                    fprintf(f, "        b%d.PUT(HttpRequest.BodyPublishers.noBody());\n", req_num);
                }
            }
            
            fprintf(f, "        for (var e : DEFAULT_HEADERS.entrySet()) {\n");
            fprintf(f, "            b%d.header(e.getKey(), e.getValue());\n", req_num);
            fprintf(f, "        }\n");
            
            Header* rh = req->headers;
            while (rh != NULL) {
                char* value = substitute_variables(rh->value);
                fprintf(f, "        b%d.header(%s, %s);\n",
                        req_num, escape_java_string(rh->key), escape_java_string(value));
                rh = rh->next;
            }
            
            fprintf(f, "        HttpResponse<String> resp%d = client.send(b%d.build(), ",
                    req_num, req_num);
            fprintf(f, "HttpResponse.BodyHandlers.ofString(StandardCharsets.UTF_8));\n\n");
            
            Assertion* a = req->assertions;
            while (a != NULL) {
                switch (a->type) {
                    case ASSERT_STATUS:
                        fprintf(f, "        assertEquals(%d, resp%d.statusCode());\n",
                                a->status_code, req_num);
                        break;
            case ASSERT_STATUS_RANGE:
            fprintf(f, "        assertTrue(resp%d.statusCode() >= %d && resp%d.statusCode() <= %d, \"status expected in range %d..%d but was: \" + resp%d.statusCode());\n",
                req_num, a->status_min, req_num, a->status_max, a->status_min, a->status_max, req_num);
            break;
                    case ASSERT_HEADER_EQ:
                        fprintf(f, "        assertEquals(%s, resp%d.headers().firstValue(%s).orElse(\"\"));\n",
                                escape_java_string(substitute_variables(a->expected_value)),
                                req_num, escape_java_string(a->header_name));
                        break;
                    case ASSERT_HEADER_CONTAINS:
                        fprintf(f, "        assertTrue(resp%d.headers().firstValue(%s).orElse(\"\").contains(%s));\n",
                                req_num, escape_java_string(a->header_name),
                                escape_java_string(substitute_variables(a->expected_value)));
                        break;
                    case ASSERT_BODY_CONTAINS:
                        fprintf(f, "        assertTrue(resp%d.body().contains(%s));\n",
                                req_num, escape_java_string(substitute_variables(a->expected_value)));
                        break;
                }
                a = a->next;
            }
            
            if (req->next) fprintf(f, "\n");
            req = req->next;
        }
        
        fprintf(f, "    }\n\n");
        t = t->next;
    }
    
    fprintf(f, "}\n");
    fclose(f);
    
    printf("Generated Java code: %s\n", filename);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input.test> [output.java]\n", argv[0]);
        return 1;
    }
    
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror(argv[1]);
        return 1;
    }
    
    int ret = yyparse();
    fclose(yyin);
    
    if (ret == 0) {
        const char* output = argc > 2 ? argv[2] : "GeneratedTests.java";
        generate_java_code(program, output);
        printf("Parsing complete!\n");
    }
    
    return ret;
}
