# Language Reference & Key Features

This document describes the TestLang++ language syntax and its main features.

### Overview
- TestLang++ is a simple declarative DSL for HTTP API testing. Source files use the `.test` extension.

### Top-level constructs
- `config { ... }` — global configuration (e.g. `base_url`, default headers)
- `let <name> = <value>;` — declare a variable (string or non-negative integer)
- `test <Name> { ... }` — defines a test case containing requests and assertions

### HTTP requests
- Inline: `GET "/path";`
- With body: `POST "/path" { body = "{...}" };` (note the required semicolon after `}`)
- Path parameters can use variables: `GET "/users/$id";`

### Assertions
- `expect status = <number>;` — assert numeric HTTP status
- `expect header "Name" equals "value";` — header equality
- `expect header "Name" contains "substring";` — header contains
- `expect body contains "text";` — substring check in response body

### Variables and substitution
- Declare: `let user = "admin";`
- Use in strings and paths via `$name` (substituted at generation time)
- Strings support escaped quotes `\"` and variable references inside JSON bodies

### Config block
- Example:

```testlang
config {
  base_url = "http://localhost:8080";
  header "Content-Type" = "application/json";
}
```

### Comments
- Line comments start with `//` and continue to end-of-line.

### Important rules
- Semicolon required after request blocks: `} ;` — omitting it causes cascading parser errors.
- Status values must be numeric literals (no quotes).
- When extending strings with embedded grammar, take care that tokenization does not treat string parts as `IDENTIFIER` unexpectedly — prefer handling in the lexer or add grammar rules in `src/parser.y`.

### Examples

```testlang
let user = "admin";
test Login {
  POST "/api/login" {
    body = "{ \"username\": \"$user\", \"password\": \"1234\" }";
  };
  expect status = 200;
  expect body contains "\"token\":";
}
```

### See also
- Parser internals: [docs/PARSER.md](docs/PARSER.md)
- Lexer/token rules: [docs/LEXER.md](docs/LEXER.md)
- Usage and examples: [docs/USAGE.md](docs/USAGE.md)
