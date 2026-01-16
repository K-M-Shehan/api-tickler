# Makefile for TestLang++ DSL Compiler

CC = gcc
LEX = flex
YACC = bison
CFLAGS = -Wall -g

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests

# Targets
PARSER = $(BUILD_DIR)/testlang-parser
GENERATED_JAVA = GeneratedTests.java
EXAMPLE_TEST = example.test

# JUnit 5 dependencies
JUNIT_VERSION = 5.9.3
JUNIT_PLATFORM_VERSION = 1.9.3
JUNIT_JAR = junit-jupiter-$(JUNIT_VERSION).jar
JUNIT_API_JAR = junit-jupiter-api-$(JUNIT_VERSION).jar
JUNIT_ENGINE_JAR = junit-jupiter-engine-$(JUNIT_VERSION).jar
JUNIT_PLATFORM_JAR = junit-platform-console-standalone-$(JUNIT_PLATFORM_VERSION).jar

.PHONY: all clean parser example test backend run-tests help

all: parser example

# Build the parser
parser: $(BUILD_DIR) $(PARSER)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/parser.tab.c $(BUILD_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	$(YACC) -d -o $(BUILD_DIR)/parser.tab.c $(SRC_DIR)/parser.y

$(BUILD_DIR)/lex.yy.c: $(SRC_DIR)/scanner.l $(BUILD_DIR)/parser.tab.h
	$(LEX) -o $(BUILD_DIR)/lex.yy.c $(SRC_DIR)/scanner.l

$(PARSER): $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/parser.tab.c
	$(CC) $(CFLAGS) -o $(PARSER) $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/parser.tab.c -I$(BUILD_DIR)

# Parse example.test and generate Java code
example: parser
	./$(PARSER) $(EXAMPLE_TEST) $(GENERATED_JAVA)

# Compile generated tests
compile-tests: example
	@echo "Compiling generated tests..."
	@if [ ! -f $(JUNIT_PLATFORM_JAR) ]; then \
		echo "Downloading JUnit 5..."; \
		wget -q https://repo1.maven.org/maven2/org/junit/platform/junit-platform-console-standalone/$(JUNIT_PLATFORM_VERSION)/$(JUNIT_PLATFORM_JAR); \
	fi
	javac -cp $(JUNIT_PLATFORM_JAR) $(GENERATED_JAVA)

# Run the generated JUnit tests
test: compile-tests
	@echo "Running JUnit tests..."
	java -jar $(JUNIT_PLATFORM_JAR) --class-path . --scan-class-path

# Build and run Spring Boot backend
backend:
	@echo "Building Spring Boot backend..."
	cd backend && mvn clean package
	@echo "Backend built successfully. Run 'make run-backend' to start it."

run-backend:
	@echo "Starting Spring Boot backend on http://localhost:8080..."
	cd backend && java -jar target/testlang-demo-0.0.1-SNAPSHOT.jar

# Full workflow: build parser, generate tests, compile, and run
run-tests: example compile-tests test

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(GENERATED_JAVA) *.class
	rm -f $(JUNIT_PLATFORM_JAR)
	cd backend && mvn clean 2>/dev/null || true

# Help target
help:
	@echo "TestLang++ DSL Compiler - Makefile Targets"
	@echo "==========================================="
	@echo "  make parser         - Build the TestLang++ parser"
	@echo "  make example        - Parse example.test and generate GeneratedTests.java"
	@echo "  make compile-tests  - Compile the generated JUnit 5 tests"
	@echo "  make test           - Run the generated JUnit 5 tests"
	@echo "  make run-tests      - Full workflow: generate, compile, and run tests"
	@echo "  make backend        - Build the Spring Boot backend"
	@echo "  make run-backend    - Start the Spring Boot backend (port 8080)"
	@echo "  make clean          - Remove all build artifacts"
	@echo "  make help           - Show this help message"
	@echo ""
	@echo "Typical workflow:"
	@echo "  1. make backend        # Build the backend once"
	@echo "  2. make run-backend    # Start backend in one terminal"
	@echo "  3. make run-tests      # In another terminal, run tests"
