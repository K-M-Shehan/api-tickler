# Contributing

Thank you for considering contributing! Small guide to get started.

### Development workflow

1. Fork and clone the repo.
2. Create a topic branch: `git checkout -b my-feature`.
3. Run tests and linters where applicable. For parser work:

```bash
make parser
./build/testlang-parser example.test GeneratedTests.java
```

4. Open a pull request with a clear description and test cases.

### Code style

- C for parser/lexer: follow existing style in `src/` and `build/` artifacts.
- Java backend: standard Maven layout in `backend/`.

### Reporting issues

- Provide a minimal reproducible `.test` file, the command you ran, and the full tool output.