/**
 * HashTable.h
 * 
 * This file defines a generic HashTable class using separate chaining (buckets of linked lists)
 * for collision resolution. The table automatically resizes (rehashes) when the load factor
 * exceeds a configurable threshold.
 * 
 * Structure:
 * - Uses a vector of buckets, where each bucket is a std::list of Entry structs (key-value pairs).
 * - Each Entry stores a key and its associated value.
 * - The hash function is based on std::hash for the key type.
 * - Supports insertion, removal, lookup, and dynamic resizing.
 * 
 * Complexity:
 * - Average-case time complexity for insert, remove, and get: O(1)
 * - Worst-case time complexity for insert, remove, and get: O(n) (if all keys hash to the same bucket)
 * - Rehashing (resizing) is O(n).
 * - Space complexity: O(n), where n is the number of elements stored.
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <algorithm>

template <typename Key, typename Value>
class HashTable {
private:
    struct Entry {
        Key key;
        Value value;
        Entry(const Key& k, const Value& v) : key(k), value(v) {}
    };

    using Bucket = std::list<Entry>;
    std::vector<Bucket> buckets;
    size_t itemCount = 0;
    float maxLoadFactor = 0.75f;

    size_t hashFunction(const Key& key) const {
        return std::hash<Key>{}(key) % buckets.size();
    }

    void rehash(size_t newSize) {
        std::vector<Bucket> newBuckets(newSize);
        for (auto& bucket : buckets) {
            for (auto& entry : bucket) {
                size_t newIndex = std::hash<Key>{}(entry.key) % newSize;
                newBuckets[newIndex].push_back(entry);
            }
        }
        buckets = std::move(newBuckets);
    }

public:
    HashTable(size_t initialSize = 10, float maxLF = 0.75f) 
        : buckets(initialSize), maxLoadFactor(maxLF) {
        if (initialSize < 1) buckets.resize(1);
    }

    void insert(const Key& key, const Value& value) {
        if (loadFactor() > maxLoadFactor) {
            rehash(buckets.size() * 2 + 1);
        }
        
        size_t index = hashFunction(key);
        Bucket& bucket = buckets[index];
        
        // Update existing key
        for (auto& entry : bucket) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        
        // Insert new key
        bucket.emplace_back(key, value);
        itemCount++;
    }

    bool remove(const Key& key) {
        size_t index = hashFunction(key);
        Bucket& bucket = buckets[index];
        
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                itemCount--;
                return true;
            }
        }
        return false;
    }

    Value& get(const Key& key) {
        size_t index = hashFunction(key);
        Bucket& bucket = buckets[index];
        
        for (auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::out_of_range("Key not found");
    }

    const Value& get(const Key& key) const {
        size_t index = hashFunction(key);
        const Bucket& bucket = buckets[index];
        
        for (const auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::out_of_range("Key not found");
    }

    bool contains(const Key& key) const {
        size_t index = hashFunction(key);
        const Bucket& bucket = buckets[index];
        
        for (const auto& entry : bucket) {
            if (entry.key == key) {
                return true;
            }
        }
        return false;
    }

    size_t size() const { return itemCount; }
    bool empty() const { return itemCount == 0; }
    float loadFactor() const { 
        return static_cast<float>(itemCount) / buckets.size(); 
    }
    size_t bucketCount() const { return buckets.size(); }

    void clear() {
        for (auto& bucket : buckets) {
            bucket.clear();
        }
        itemCount = 0;
    }
};

#endif // HASHTABLE_H