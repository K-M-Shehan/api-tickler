package com.testlang.demo;

import org.springframework.http.HttpHeaders;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping("/api")
public class TestApiController {

    @PostMapping("/login")
    public ResponseEntity<String> login(@RequestBody Map<String, String> credentials) {
        String username = credentials.get("username");
        String password = credentials.get("password");
        
        if ("admin".equals(username) && "1234".equals(password)) {
            String response = "{\"token\": \"abc123xyz\", \"username\": \"" + username + "\"}";
            
            HttpHeaders headers = new HttpHeaders();
            headers.add("Content-Type", "application/json");
            
            return ResponseEntity.ok()
                    .headers(headers)
                    .body(response);
        }
        
        return ResponseEntity.status(401).body("{\"error\": \"Invalid credentials\"}");
    }

    @GetMapping("/users/{id}")
    public ResponseEntity<String> getUser(@PathVariable int id) {
        String response = "{\"id\": " + id + ", \"name\": \"User " + id + "\", \"role\": \"USER\"}";
        
        HttpHeaders headers = new HttpHeaders();
        headers.add("Content-Type", "application/json");
        headers.add("X-App", "TestLangDemo");
        
        return ResponseEntity.ok()
                .headers(headers)
                .body(response);
    }

    @PutMapping("/users/{id}")
    public ResponseEntity<String> updateUser(@PathVariable int id, @RequestBody Map<String, String> data) {
        String role = data.getOrDefault("role", "USER");
        String response = "{\"updated\": true, \"id\": " + id + ", \"role\": \"" + role + "\"}";
        
        HttpHeaders headers = new HttpHeaders();
        headers.add("Content-Type", "application/json");
        headers.add("X-App", "TestLangDemo");
        
        return ResponseEntity.ok()
                .headers(headers)
                .body(response);
    }
}
