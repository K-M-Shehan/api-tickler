# Architecture

### Overview

TestLang++ is composed of three core parts:

- Lexer (`src/scanner.l`) — tokenizes the input language using Flex.
- Parser (`src/parser.y`) — Bison grammar that builds an AST and drives code generation.
- Code generator — embedded in the Bison actions; emits JUnit 5 test Java source.

### Runtime test backend

The `backend/` folder contains a small Spring Boot application used for local integration tests. It exposes a few endpoints (see `API.md`) that the generated tests target.

### Build flow

1. `make parser` → produces `build/testlang-parser` (lexer+parser binary).
2. `./build/testlang-parser example.test GeneratedTests.java` → generates Java test source.
3. `javac` (via `make compile-tests`) → compiles generated tests.
4. `java -jar junit-platform-console-standalone.jar --scan-class-path` → runs tests.

### Design notes

- Error messages are produced with line numbers and hints for easier debugging (see `ERROR_MESSAGES.md`).
- Variable substitution is handled in the code generation phase: `$name` occurrences are replaced with the declared values at generation time.
