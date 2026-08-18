# Lexer (Flex) Reference

Location: `src/scanner.l`

### Purpose
- Tokenizes TestLang++ source into tokens the Bison parser consumes.

### How to regenerate

```bash
# From project root (Makefile target):
make parser
# Or manually (match Makefile variables):
bison -d -o build/parser.tab.c src/parser.y
flex -o build/lex.yy.c src/scanner.l
gcc -o build/testlang-parser build/lex.yy.c build/parser.tab.c -Ibuild
```

### Key runtime symbols
- `yyin` — input FILE* used by the lexer (set by the driver to read files)
- `yytext` — the current token text buffer
- `yylval` — semantic value passed back to the parser (set in lexer actions)

### Important tokens (high-level)
- Keywords: `config`, `let`, `test`, `expect`, `GET`, `POST`, `PUT`, `DELETE`
- Literals: `IDENTIFIER`, `NON_NEG_INT`, `STRING` (quoted text)
- Punctuation: `{`, `}`, `;`, `=`, `"`, `$`, `/`

### Notes
- Strings: double-quoted strings must handle escape sequences `\"` and variable refs like `$name`.
- Order matters: put longer token patterns before shorter ones to avoid accidental matches (e.g. keywords before `IDENTIFIER`).
- Comments: single-line comments are skipped by the lexer.

### Extending the lexer
- Add the token regex and return the token name used by the parser (see `src/parser.y` for expected tokens).
- When adding a new token that carries a semantic value (e.g. `STRING`), set `yylval` appropriately in the action code.

### Debugging tips
- Run the generated lexer against a sample file and print `yytext` in actions to observe tokenization.
- Enable Bison verbose output when debugging parser/lexer interactions:

```bash
bison -v -d -o build/parser.tab.c src/parser.y
```
