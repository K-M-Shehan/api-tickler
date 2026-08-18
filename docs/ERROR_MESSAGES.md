# Parser Error Messages

This document summarizes common parser and lexer error messages produced by the TestLang++ toolchain and gives examples and suggested fixes.

### General format
- "Error on line <n>: <message>" — includes the line number and a short message.
- Context: a snippet or description of what was expected.
- Hint: actionable suggestion.

### Common errors

- Missing semicolon after block request
  - Symptom: "Expected ';' after '}'" or a generic syntax error on the following line.
  - Fix: add a semicolon after a request body block, e.g. `POST "/x" { body = "{}" };`

- Invalid status value
  - Symptom: "Expected number after 'status', but found '"200"'"
  - Fix: use a numeric literal: `expect status = 200;`

- Unterminated string
  - Symptom: "Unterminated string at end of file" or unexpected token when parsing a quote.
  - Fix: ensure strings are closed and escape embedded quotes with `\"`.

- Unknown token / unrecognized input
  - Symptom: "Unexpected token '<token>'" or "syntax error" with context.
  - Fix: check for typos in keywords (e.g. `let` / `test` / `expect`) and ensure punctuation (`;`, `{`, `}`) is correct.

If you see an error not documented here, please open an issue with the failing `.test` input and the exact tool output.