#!/bin/bash
# Build and start the Spring Boot backend

echo "Building Spring Boot backend..."
cd backend

if [ ! -f "pom.xml" ]; then
    echo "Error: pom.xml not found in backend directory"
    exit 1
fi

mvn clean package

if [ $? -eq 0 ]; then
    echo ""
    echo "Backend built successfully!"
    echo "Starting backend on http://localhost:8080..."
    echo ""
    java -jar target/testlang-demo-0.0.1-SNAPSHOT.jar
else
    echo "Error: Backend build failed"
    exit 1
fi
