# Parser (Bison) Reference

Location: `src/parser.y`

### Overview
- The Bison grammar defines the language's syntax and contains semantic actions that build an internal representation and emit Java test code.

### How to regenerate

```bash
# From project root (Makefile target):
make parser
# Manual steps (matches Makefile):
bison -d -o build/parser.tab.c src/parser.y
flex -o build/lex.yy.c src/scanner.l
gcc -o build/testlang-parser build/lex.yy.c build/parser.tab.c -Ibuild
```

### Key nonterminals (high-level)
- `config` — global config block (`base_url`, default headers)
- `let` / `variable` — variable declarations and values
- `test` — test case block containing requests and expectations
- `request` — HTTP request construct (method, path, optional body)
- `expect` — assertions on response (`status`, `header`, `body`)

### AST & Code Generation
- The parser actions build a simple AST and then the code generator emits JUnit 5 + HttpClient Java source. Inspect action blocks in `parser.y` to see the exact emitted Java snippets.

### Debugging and verbose output
- Produce a parser state file to inspect conflicts and states:

```bash
bison -v -d -o build/parser.tab.c src/parser.y
# This creates build/parser.output with state tables and reduce/reduce or shift/reduce info.
```

- Use test inputs (e.g. `example.test`) and run the generated `build/testlang-parser` with a file and output target to reproduce generation problems.

### Common grammar issues
- Missing semicolons after blocks (`}`) often produce cascading syntax errors — check preceding request blocks.
- Ambiguous tokenization between `IDENTIFIER` and string parts inside quoted strings can lead to unexpected parses; if adding complex string features, prefer handling in the lexer or add dedicated grammar rules.

### Where to change behavior
- To change token names or token values: edit `src/scanner.l` and adjust `yylval` assignments.
- To change syntax or generated code: edit `src/parser.y` — action code emits the Java output.
