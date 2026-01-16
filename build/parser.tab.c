/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

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


#line 167 "build/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_LET = 6,                        /* LET  */
  YYSYMBOL_CONFIG = 7,                     /* CONFIG  */
  YYSYMBOL_BASE_URL = 8,                   /* BASE_URL  */
  YYSYMBOL_HEADER = 9,                     /* HEADER  */
  YYSYMBOL_TEST = 10,                      /* TEST  */
  YYSYMBOL_GET = 11,                       /* GET  */
  YYSYMBOL_POST = 12,                      /* POST  */
  YYSYMBOL_PUT = 13,                       /* PUT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_EXPECT = 15,                    /* EXPECT  */
  YYSYMBOL_STATUS = 16,                    /* STATUS  */
  YYSYMBOL_BODY = 17,                      /* BODY  */
  YYSYMBOL_CONTAINS = 18,                  /* CONTAINS  */
  YYSYMBOL_IN = 19,                        /* IN  */
  YYSYMBOL_EQUALS = 20,                    /* EQUALS  */
  YYSYMBOL_LBRACE = 21,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 22,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 23,                 /* SEMICOLON  */
  YYSYMBOL_DOTDOT = 24,                    /* DOTDOT  */
  YYSYMBOL_YYACCEPT = 25,                  /* $accept  */
  YYSYMBOL_program = 26,                   /* program  */
  YYSYMBOL_config_block = 27,              /* config_block  */
  YYSYMBOL_config_items = 28,              /* config_items  */
  YYSYMBOL_config_item = 29,               /* config_item  */
  YYSYMBOL_variable_decl = 30,             /* variable_decl  */
  YYSYMBOL_value = 31,                     /* value  */
  YYSYMBOL_test = 32,                      /* test  */
  YYSYMBOL_test_body = 33,                 /* test_body  */
  YYSYMBOL_statement = 34,                 /* statement  */
  YYSYMBOL_request_stmt = 35,              /* request_stmt  */
  YYSYMBOL_simple_request = 36,            /* simple_request  */
  YYSYMBOL_block_request = 37,             /* block_request  */
  YYSYMBOL_request_block = 38,             /* request_block  */
  YYSYMBOL_request_item = 39,              /* request_item  */
  YYSYMBOL_assertion_stmt = 40,            /* assertion_stmt  */
  YYSYMBOL_assertion = 41                  /* assertion  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   91

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  39
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  97

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   279


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   120,   120,   127,   128,   129,   133,   136,   138,   142,
     145,   151,   155,   159,   166,   173,   184,   191,   193,   197,
     198,   202,   203,   207,   212,   220,   227,   234,   239,   246,
     248,   252,   257,   263,   273,   276,   279,   285,   288,   291
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "STRING",
  "NUMBER", "LET", "CONFIG", "BASE_URL", "HEADER", "TEST", "GET", "POST",
  "PUT", "DELETE", "EXPECT", "STATUS", "BODY", "CONTAINS", "IN", "EQUALS",
  "LBRACE", "RBRACE", "SEMICOLON", "DOTDOT", "$accept", "program",
  "config_block", "config_items", "config_item", "variable_decl", "value",
  "test", "test_body", "statement", "request_stmt", "simple_request",
  "block_request", "request_block", "request_item", "assertion_stmt",
  "assertion", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-16)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -16,    25,   -16,    -3,   -15,     6,   -16,   -16,   -16,     4,
      23,   -16,    19,     3,   -16,   -16,    -9,    -7,   -16,    18,
      20,   -16,     9,    38,   -16,   -16,     8,   -16,   -16,    40,
      26,    41,    43,    44,    45,    17,   -16,   -16,   -16,   -16,
     -16,   -16,    27,    47,    29,    33,    34,    30,    52,    37,
      42,   -16,   -16,    35,   -16,    39,    46,   -16,    -8,    32,
      55,   -16,    48,    -6,    49,    -4,    58,    59,    50,    15,
      51,   -16,    60,    56,    54,   -16,   -16,    57,    61,    62,
     -16,   -16,    64,   -16,    63,    66,   -16,   -16,   -16,   -16,
      65,    71,    67,   -16,    68,   -16,   -16
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     3,     4,     5,     0,
       0,     7,     0,     0,    14,    15,     0,     0,    17,     0,
       0,    12,     0,     0,     6,     8,     0,    13,    11,     0,
       0,     0,     0,     0,     0,     0,    16,    18,    19,    21,
      22,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,     9,     0,    23,    29,    29,    24,     0,     0,
       0,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,     0,     0,     0,    30,    28,     0,     0,     0,
      36,    34,     0,    39,     0,     0,    25,    26,    38,    37,
       0,     0,     0,    35,     0,    32,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -16,   -16,   -16,   -16,   -16,   -16,    53,   -16,   -16,   -16,
     -16,   -16,   -16,    11,   -16,   -16,   -16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     6,    17,    25,     7,    16,     8,    26,    37,
      38,    39,    40,    63,    75,    41,    51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       9,    22,    23,    72,    19,    72,    11,    14,    15,    12,
      66,    73,    67,    73,    21,    24,    74,    10,    77,    31,
      32,    33,    34,    35,    13,     2,    48,    14,    15,    29,
      36,     3,     4,    49,    50,     5,    68,    69,    81,    82,
      18,    27,    30,    28,    42,    44,    43,    45,    46,    47,
      52,    53,    54,    57,    55,    56,    58,    59,    61,    70,
      60,    62,    78,    79,    84,     0,    20,    65,    64,    90,
      92,    71,    76,    80,    83,    94,    85,    86,     0,     0,
      87,     0,     0,    91,    88,    89,     0,     0,    93,     0,
      95,    96
};

static const yytype_int8 yycheck[] =
{
       3,     8,     9,     9,     1,     9,    21,     4,     5,     3,
      18,    17,    20,    17,    23,    22,    22,    20,    22,    11,
      12,    13,    14,    15,    20,     0,     9,     4,     5,    20,
      22,     6,     7,    16,    17,    10,     4,     5,    23,    24,
      21,    23,     4,    23,     4,     4,    20,     4,     4,     4,
      23,     4,    23,    23,    21,    21,     4,    20,    23,     4,
      18,    22,     4,     4,     4,    -1,    13,    56,    22,     5,
       4,    23,    23,    23,    23,     4,    20,    23,    -1,    -1,
      23,    -1,    -1,    20,    23,    23,    -1,    -1,    23,    -1,
      23,    23
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,     0,     6,     7,    10,    27,    30,    32,     3,
      20,    21,     3,    20,     4,     5,    31,    28,    21,     1,
      31,    23,     8,     9,    22,    29,    33,    23,    23,    20,
       4,    11,    12,    13,    14,    15,    22,    34,    35,    36,
      37,    40,     4,    20,     4,     4,     4,     4,     9,    16,
      17,    41,    23,     4,    23,    21,    21,    23,     4,    20,
      18,    23,    22,    38,    22,    38,    18,    20,     4,     5,
       4,    23,     9,    17,    22,    39,    23,    22,     4,     4,
      23,    23,    24,    23,     4,    20,    23,    23,    23,    23,
       5,    20,     4,    23,     4,    23,    23
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    25,    26,    26,    26,    26,    27,    28,    28,    29,
      29,    30,    30,    30,    31,    31,    32,    33,    33,    34,
      34,    35,    35,    36,    36,    37,    37,    37,    37,    38,
      38,    39,    39,    40,    41,    41,    41,    41,    41,    41
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     4,     0,     2,     4,
       5,     5,     4,     5,     1,     1,     5,     0,     2,     1,
       1,     1,     1,     3,     3,     6,     6,     5,     5,     0,
       2,     5,     4,     2,     4,     6,     4,     5,     5,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 120 "src/parser.y"
                { 
        program = malloc(sizeof(Program));
        program->base_url = NULL;
        program->default_headers = NULL;
        program->variables = NULL;
        program->tests = NULL;
    }
#line 1251 "build/parser.tab.c"
    break;

  case 9: /* config_item: BASE_URL EQUALS STRING SEMICOLON  */
#line 142 "src/parser.y"
                                     {
        program->base_url = strdup((yyvsp[-1].str));
    }
#line 1259 "build/parser.tab.c"
    break;

  case 10: /* config_item: HEADER STRING EQUALS STRING SEMICOLON  */
#line 145 "src/parser.y"
                                            {
        add_default_header(create_header((yyvsp[-3].str), (yyvsp[-1].str)));
    }
#line 1267 "build/parser.tab.c"
    break;

  case 11: /* variable_decl: LET IDENTIFIER EQUALS value SEMICOLON  */
#line 151 "src/parser.y"
                                          {
        add_variable((Variable*)(yyvsp[-1].ptr));
        ((Variable*)(yyvsp[-1].ptr))->name = (yyvsp[-3].str);
    }
#line 1276 "build/parser.tab.c"
    break;

  case 12: /* variable_decl: LET EQUALS value SEMICOLON  */
#line 155 "src/parser.y"
                                 {
        report_error(ERR_MISSING_IDENTIFIER, "let");
        YYABORT;
    }
#line 1285 "build/parser.tab.c"
    break;

  case 13: /* variable_decl: LET IDENTIFIER EQUALS error SEMICOLON  */
#line 159 "src/parser.y"
                                            {
        report_error(ERR_EXPECTED_VALUE, "");
        YYABORT;
    }
#line 1294 "build/parser.tab.c"
    break;

  case 14: /* value: STRING  */
#line 166 "src/parser.y"
           {
        Variable* var = malloc(sizeof(Variable));
        var->value = (yyvsp[0].str);
        var->is_number = 0;
        var->next = NULL;
        (yyval.ptr) = var;
    }
#line 1306 "build/parser.tab.c"
    break;

  case 15: /* value: NUMBER  */
#line 173 "src/parser.y"
             {
        Variable* var = malloc(sizeof(Variable));
        var->value = malloc(32);
        sprintf(var->value, "%d", (yyvsp[0].num));
        var->is_number = 1;
        var->next = NULL;
        (yyval.ptr) = var;
    }
#line 1319 "build/parser.tab.c"
    break;

  case 16: /* test: TEST IDENTIFIER LBRACE test_body RBRACE  */
#line 184 "src/parser.y"
                                            {
        Test* t = create_test((yyvsp[-3].str), current_requests);
        add_test(t);
        current_requests = NULL;
    }
#line 1329 "build/parser.tab.c"
    break;

  case 23: /* simple_request: GET STRING SEMICOLON  */
#line 207 "src/parser.y"
                         {
        Request* req = create_request(REQ_GET, (yyvsp[-1].str), NULL, NULL, NULL);
        req->next = current_requests;
        current_requests = req;
    }
#line 1339 "build/parser.tab.c"
    break;

  case 24: /* simple_request: DELETE STRING SEMICOLON  */
#line 212 "src/parser.y"
                              {
        Request* req = create_request(REQ_DELETE, (yyvsp[-1].str), NULL, NULL, NULL);
        req->next = current_requests;
        current_requests = req;
    }
#line 1349 "build/parser.tab.c"
    break;

  case 25: /* block_request: POST STRING LBRACE request_block RBRACE SEMICOLON  */
#line 220 "src/parser.y"
                                                      {
        Request* req = create_request(REQ_POST, (yyvsp[-4].str), current_headers, current_body, NULL);
        req->next = current_requests;
        current_requests = req;
        current_headers = NULL;
        current_body = NULL;
    }
#line 1361 "build/parser.tab.c"
    break;

  case 26: /* block_request: PUT STRING LBRACE request_block RBRACE SEMICOLON  */
#line 227 "src/parser.y"
                                                       {
        Request* req = create_request(REQ_PUT, (yyvsp[-4].str), current_headers, current_body, NULL);
        req->next = current_requests;
        current_requests = req;
        current_headers = NULL;
        current_body = NULL;
    }
#line 1373 "build/parser.tab.c"
    break;

  case 27: /* block_request: POST STRING LBRACE RBRACE SEMICOLON  */
#line 234 "src/parser.y"
                                          {
        Request* req = create_request(REQ_POST, (yyvsp[-3].str), NULL, NULL, NULL);
        req->next = current_requests;
        current_requests = req;
    }
#line 1383 "build/parser.tab.c"
    break;

  case 28: /* block_request: PUT STRING LBRACE RBRACE SEMICOLON  */
#line 239 "src/parser.y"
                                         {
        Request* req = create_request(REQ_PUT, (yyvsp[-3].str), NULL, NULL, NULL);
        req->next = current_requests;
        current_requests = req;
    }
#line 1393 "build/parser.tab.c"
    break;

  case 31: /* request_item: HEADER STRING EQUALS STRING SEMICOLON  */
#line 252 "src/parser.y"
                                          {
        Header* h = create_header((yyvsp[-3].str), (yyvsp[-1].str));
        h->next = current_headers;
        current_headers = h;
    }
#line 1403 "build/parser.tab.c"
    break;

  case 32: /* request_item: BODY EQUALS STRING SEMICOLON  */
#line 257 "src/parser.y"
                                   {
        current_body = strdup((yyvsp[-1].str));
    }
#line 1411 "build/parser.tab.c"
    break;

  case 33: /* assertion_stmt: EXPECT assertion  */
#line 263 "src/parser.y"
                     {
        if (current_requests != NULL) {
            Assertion* a = (Assertion*)(yyvsp[0].ptr);
            a->next = current_requests->assertions;
            current_requests->assertions = a;
        }
    }
#line 1423 "build/parser.tab.c"
    break;

  case 34: /* assertion: STATUS EQUALS NUMBER SEMICOLON  */
#line 273 "src/parser.y"
                                   {
        (yyval.ptr) = create_assertion_status((yyvsp[-1].num));
    }
#line 1431 "build/parser.tab.c"
    break;

  case 35: /* assertion: STATUS EQUALS NUMBER DOTDOT NUMBER SEMICOLON  */
#line 276 "src/parser.y"
                                                   {
        (yyval.ptr) = create_assertion_status_range((yyvsp[-3].num), (yyvsp[-1].num));
    }
#line 1439 "build/parser.tab.c"
    break;

  case 36: /* assertion: STATUS EQUALS STRING SEMICOLON  */
#line 279 "src/parser.y"
                                     {
        report_error(ERR_EXPECTED_NUMBER, "status");
        fprintf(stderr, "  You wrote: expect status = \"%s\";\n", (yyvsp[-1].str));
        fprintf(stderr, "  Should be: expect status = %s;\n", (yyvsp[-1].str));
        YYABORT;
    }
#line 1450 "build/parser.tab.c"
    break;

  case 37: /* assertion: HEADER STRING EQUALS STRING SEMICOLON  */
#line 285 "src/parser.y"
                                            {
        (yyval.ptr) = create_assertion_header_eq((yyvsp[-3].str), (yyvsp[-1].str));
    }
#line 1458 "build/parser.tab.c"
    break;

  case 38: /* assertion: HEADER STRING CONTAINS STRING SEMICOLON  */
#line 288 "src/parser.y"
                                              {
        (yyval.ptr) = create_assertion_header_contains((yyvsp[-3].str), (yyvsp[-1].str));
    }
#line 1466 "build/parser.tab.c"
    break;

  case 39: /* assertion: BODY CONTAINS STRING SEMICOLON  */
#line 291 "src/parser.y"
                                     {
        (yyval.ptr) = create_assertion_body_contains((yyvsp[-1].str));
    }
#line 1474 "build/parser.tab.c"
    break;


#line 1478 "build/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 296 "src/parser.y"


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
