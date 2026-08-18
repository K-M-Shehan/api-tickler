# api-tickler

> A Domain-Specific Language for HTTP API testing that compiles to JUnit 5 tests using Java 11+ HttpClient.

## Project Overview

TestLang++ is a complete DSL implementation using Flex and Bison that allows you to write API tests in a clean, declarative syntax and automatically generates executable JUnit 5 tests.

## Project Structure

```
api-tickler/
├── src/
│   ├── scanner.l           # Flex lexer specification  
│   └── parser.y            # Bison parser with code generation
├── backend/                # Spring Boot test backend (3 endpoints)
├── example.test            # Example TestLang++ test file
├── Makefile               # Complete build automation
├── run-backend.sh         # Backend startup script
├── run-tests.sh           # Full test workflow script
└── README.md              # This file
```

## Documentation

Further documentation and guides live in the `docs/` folder:

- [INSTALL.md](docs/INSTALL.md) — Installation and prerequisites
- [USAGE.md](docs/USAGE.md) — How to build and run the toolset
- [ARCHITECTURE.md](docs/ARCHITECTURE.md) — High-level architecture and build flow
- [API.md](docs/API.md) — Backend API reference (endpoints used by generated tests)
- [ERROR_MESSAGES.md](docs/ERROR_MESSAGES.md) — Parser/lexer error message guide
- [LEXER.md](docs/LEXER.md) — Lexer (Flex) reference
- [PARSER.md](docs/PARSER.md) — Parser (Bison) reference
- [LANGUAGE.md](docs/LANGUAGE.md) — Language syntax & key features
- [CONTRIBUTING.md](docs/CONTRIBUTING.md) — Contributing guidelines
- [README.md](docs/README.md) — Devlog and day-to-day notes


## Quick Start

### 1. Build the Parser
```bash
make parser
```

### 2. Start the Backend  
```bash
./run-backend.sh  # In terminal 1
```

### 3. Run Tests
```bash
./run-tests.sh     # In terminal 2
```

## Makefile Targets

```bash
make parser         # Build TestLang++ compiler
make example        # Parse example.test → GeneratedTests.java
make compile-tests  # Compile Java tests with JUnit 5
make test           # Run JUnit tests  
make run-tests      # Full workflow (parse + compile + run)
make backend        # Build Spring Boot backend
make clean          # Remove all artifacts
```

## Implementation

**Scanner (Flex)**: Tokenizes keywords, identifiers, strings, numbers  
**Parser (Bison)**: Builds AST with symbol tables for variables  
**Code Generator**: Emits idiomatic JUnit 5 + HttpClient code  

## Generated Java Example

```java
@Test
void test_Login() throws Exception {
    String url1 = BASE + "/api/login";
    HttpRequest.Builder b1 = HttpRequest.newBuilder(URI.create(url1));
    b1.POST(HttpRequest.BodyPublishers.ofString("{\"username\":\"admin\"}"));
    HttpResponse<String> resp1 = client.send(b1.build(), ...);
    
    assertEquals(200, resp1.statusCode());
    assertTrue(resp1.body().contains("\"token\":"));
}
```

## Error Handling

### Enhanced Error Messages

The parser provides **detailed, actionable error messages** with:
- **Line numbers** - Exact location of the error
- **Context** - What was expected vs what was found
- **Hints** - Suggestions for fixing the error
- **Examples** - Correct syntax demonstration

**Example Error Output:**
```
Error on line 3: Expected number after 'status', but found ';'
  Hint: Status codes must be numeric (not strings)
  Example: expect status = 200;
  You wrote: expect status = "200";
  Should be: expect status = 200;
```

See [docs/ERROR_MESSAGES.md](docs/ERROR_MESSAGES.md) for complete documentation and examples.

## Common Issues

1. **Syntax Error**: Missing `;` after block request `}`
2. **Backend Not Running**: Start with `./run-backend.sh` first
3. **String Escaping**: Use `\"` for quotes in JSON bodies


## License
[MIT License](./LICENSE)

**Quick Demo:**
```bash
make parser && ./run-backend.sh &
sleep 15 && make run-tests
```
