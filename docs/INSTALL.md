# Installation

Prerequisites (tested on Debian):

```bash
sudo apt-get update
sudo apt-get install -y build-essential flex bison openjdk-11-jdk maven wget curl
```

Build steps

1. Build the parser and lexer:

```bash
make parser
```

2. Build the Spring Boot backend (single-shot):

```bash
cd backend && mvn clean package
```

3. (Optional) Start the backend locally:

```bash
./run-backend.sh
```

Notes
- `make parser` writes artifacts into `build/` and produces `build/testlang-parser`.
- The top-level `Makefile` provides targets for the full workflow: `make run-tests`.
