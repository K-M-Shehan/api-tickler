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

## Prerequisites

```bash
sudo apt-get update
sudo apt-get install build-essential flex bison openjdk-11-jdk maven wget
```

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

## Language Syntax

### Complete Example

```testlang
config {
  base_url = "http://localhost:8080";
  header "Content-Type" = "application/json";
}

let user = "admin";
let id = 42;

test Login {
  POST "/api/login" {
    body = "{ \"username\": \"$user\", \"password\": \"1234\" }";
  };
  expect status = 200;
  expect header "Content-Type" contains "json";
  expect body contains "\"token\":";
}

test GetUser {
  GET "/api/users/$id";
  expect status = 200;
  expect body contains "\"id\": 42";
}
```

### Key Features

- **Variables**: `let name = "value";` with `$name` substitution
- **HTTP Methods**: GET, POST, PUT, DELETE
- **Assertions**: status, header (equals/contains), body contains
- **Config Block**: base_url and default headers
- **Comments**: `// line comments`

**Important:** Block requests (POST/PUT with `{}`) need a semicolon after `}`.

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

### Enhanced Error Messages ✨

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

See `ERROR_MESSAGES.md` for complete documentation and examples.

### Demo Error Messages
```bash
./demo-errors.sh  # Shows all error types with examples
```

## Common Issues

1. **Syntax Error**: Missing `;` after block request `}`
2. **Backend Not Running**: Start with `./run-backend.sh` first
3. **String Escaping**: Use `\"` for quotes in JSON bodies

## Project Status

✅ Complete Flex scanner with all tokens  
✅ Complete Bison parser with AST  
✅ Java code generation with HttpClient  
✅ Variable substitution working  
✅ Spring Boot backend with 3 endpoints  
✅ Build automation via Makefile  
✅ End-to-end workflow tested  

## License

MIT License

---

**Quick Demo:**
```bash
make parser && ./run-backend.sh &
sleep 15 && make run-tests
```
