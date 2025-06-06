#include "HashTable.h"
#include <iostream>
#include <string>

int main() {
    // Create hash table with strings as keys and ints as values
    HashTable<std::string, int> scores;
    
    // Insert test data
    scores.insert("Alice", 92);
    scores.insert("Bob", 85);
    scores.insert("Charlie", 78);
    scores.insert("Diana", 95);
    
    // Test insert/update
    std::cout << "=== Insert/Update Test ===" << std::endl;
    std::cout << "Alice's score: " << scores.get("Alice") << std::endl;
    scores.insert("Alice", 98);  // Update existing key
    std::cout << "Alice's updated score: " << scores.get("Alice") << std::endl;
    
    // Test contains and get
    std::cout << "\n=== Contains/Get Test ===" << std::endl;
    std::cout << "Contains 'Bob'? " << (scores.contains("Bob") ? "Yes" : "No") << std::endl;
    std::cout << "Bob's score: " << scores.get("Bob") << std::endl;
    
    // Test removal
    std::cout << "\n=== Removal Test ===" << std::endl;
    std::cout << "Removing 'Charlie': " << (scores.remove("Charlie") ? "Success" : "Failed") << std::endl;
    std::cout << "Contains 'Charlie'? " << (scores.contains("Charlie") ? "Yes" : "No") << std::endl;
    
    // Test rehashing
    std::cout << "\n=== Rehashing Test ===" << std::endl;
    std::cout << "Initial buckets: " << scores.bucketCount() 
              << ", Items: " << scores.size() 
              << ", Load factor: " << scores.loadFactor() << std::endl;
    
    // Add more items to trigger rehash
    for (int i = 0; i < 20; ++i) {
        scores.insert("Student" + std::to_string(i), 70 + i);
    }
    
    std::cout << "After rehash - Buckets: " << scores.bucketCount() 
              << ", Items: " << scores.size() 
              << ", Load factor: " << scores.loadFactor() << std::endl;
    
    // Test edge cases
    std::cout << "\n=== Nonexistent key Test ===" << std::endl;
    try {
        std::cout << "Nonexistent key: " << scores.get("Eve") << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // Test clear
    scores.clear();
    std::cout << "\nAfter clear - Size: " << scores.size() 
              << ", Empty? " << (scores.empty() ? "Yes" : "No") << std::endl;
    
    return 0;
}