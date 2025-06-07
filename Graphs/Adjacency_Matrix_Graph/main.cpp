#include "GraphMatrix.h"
#include <iostream>

int main() {
    GraphMatrix<std::string, int> roadNetwork(false); // Undirected

    roadNetwork.addEdge("A", "B", 5);
    roadNetwork.addEdge("A", "C", 3);
    roadNetwork.addEdge("B", "D", 2);

    std::cout << "Adjacency Matrix:\n";
    roadNetwork.print();

    std::cout << "\nEdge Checks:\n";
    std::cout << "A -> B? " << (roadNetwork.hasEdge("A", "B") ? "Yes" : "No") << "\n";
    std::cout << "B -> A? " << (roadNetwork.hasEdge("B", "A") ? "Yes" : "No") << "\n";
    std::cout << "A -> D? " << (roadNetwork.hasEdge("A", "D") ? "Yes" : "No") << "\n";

    return 0;
}