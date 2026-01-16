#!/bin/bash
# Full workflow: build parser, generate tests, compile, and run

set -e  # Exit on error

echo "=========================================="
echo "TestLang++ - Full Test Workflow"
echo "=========================================="
echo ""

# Check if backend is running
echo "Checking if backend is running..."
if ! curl -s http://localhost:8080/api/users/1 > /dev/null 2>&1; then
    echo "Warning: Backend doesn't seem to be running on http://localhost:8080"
    echo "Please start the backend first with: ./run-backend.sh"
    echo ""
    read -p "Continue anyway? (y/n) " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

echo ""
echo "Step 1: Building parser..."
make parser

echo ""
echo "Step 2: Generating Java tests from example.test..."
make example

echo ""
echo "Step 3: Compiling generated tests..."
make compile-tests

echo ""
echo "Step 4: Running tests..."
echo "=========================================="
make test

echo ""
echo "=========================================="
echo "Test workflow completed!"
echo "=========================================="
