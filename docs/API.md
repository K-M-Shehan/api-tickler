# Backend API (Test Backend)

The local Spring Boot backend used for integration tests exposes these endpoints under `/api`:

1) POST /api/login
   - Request JSON body: `{ "username": "<user>", "password": "<pass>" }`
   - Success response: `200 OK`, `Content-Type: application/json`
     - Body example: `{"token": "abc123xyz", "username": "admin"}`
   - Failure response: `401` with `{"error": "Invalid credentials"}`

Example curl:

```bash
curl -X POST http://localhost:8080/api/login \
  -H 'Content-Type: application/json' \
  -d '{"username":"admin","password":"1234"}'
```

2) GET /api/users/{id}
   - Response: `200 OK`, `Content-Type: application/json`, `X-App: TestLangDemo`
   - Body example: `{"id": 1, "name": "User 1", "role": "USER"}`

Example curl:

```bash
curl http://localhost:8080/api/users/1
```

3) PUT /api/users/{id}
   - Request JSON body: accepts `role` (optional)
   - Response: `200 OK`, body: `{"updated": true, "id": <id>, "role": "<role>"}`

Example curl:

```bash
curl -X PUT http://localhost:8080/api/users/2 \
  -H 'Content-Type: application/json' \
  -d '{"role":"ADMIN"}'
```
