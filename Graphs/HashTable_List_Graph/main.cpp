#include "GraphHybrid.h"
#include <iostream>

int main() {
    GraphHybrid<std::string, int> socialNetwork(true); // Directed

    socialNetwork.addEdge("Alice", "Bob", 1); // Alice follows Bob
    socialNetwork.addEdge("Bob", "Charlie", 1);
    socialNetwork.addEdge("Alice", "Charlie", 2); // Alice strongly follows Charlie

    std::cout << "Social Network (Directed):\n";
    socialNetwork.print();

    std::cout << "\nEdge Checks:\n";
    std::cout << "Alice -> Bob? " << (socialNetwork.hasEdge("Alice", "Bob") ? "Yes" : "No") << "\n";
    std::cout << "Bob -> Alice? " << (socialNetwork.hasEdge("Bob", "Alice") ? "Yes" : "No") << "\n";

    return 0;
}