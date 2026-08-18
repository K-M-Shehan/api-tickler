# Usage

### Quick Start

1. Build the parser and generate Java tests from `example.test`:

```bash
make parser
make example
```

2. Compile and run tests (JUnit platform will be downloaded automatically by `Makefile` when needed):

```bash
make compile-tests
make test
```

Full workflow (build parser → generate → compile → run):

```bash
./run-tests.sh
```

### Running the backend

Start the Spring Boot backend before running tests that rely on `http://localhost:8080`:

```bash
./run-backend.sh
```

### Makefile targets of interest

- `make parser` — build the flex/bison parser
- `make example` — parse `example.test` → `GeneratedTests.java`
- `make compile-tests` — compile generated Java tests (downloads junit-platform if needed)
- `make test` — run generated JUnit tests
- `make backend` — build the Spring Boot backend
- `make run-backend` — start the backend (same as `./run-backend.sh`)

### Tips
- If `run-tests.sh` warns the backend is not running, start the backend first or continue anyway for offline checks.
- Example test files: `example.test`, `example2.test`, `demo.test`.
