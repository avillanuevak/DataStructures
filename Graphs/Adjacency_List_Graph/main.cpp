#include "Graph.h"
#include <iostream>

int main() {
    // Create an undirected graph (cities with distances)
    Graph<std::string, int> roadNetwork(Graph<std::string, int>::Type::UNDIRECTED);
    roadNetwork.addEdge("New York", "Boston", 215);
    roadNetwork.addEdge("New York", "Philadelphia", 95);
    roadNetwork.addEdge("Boston", "Philadelphia", 310);

    // Print the graph
    std::cout << "Road Network:\n";
    roadNetwork.print();

    // Check connections
    std::cout << "\nDoes New York connect to Boston? " 
              << (roadNetwork.hasEdge("New York", "Boston") ? "Yes" : "No") << "\n";
    std::cout << "Does Boston connect to Philadelphia? " 
              << (roadNetwork.hasEdge("Boston", "Philadelphia") ? "Yes" : "No") << "\n";

    // BFS Traversal
    std::cout << "\nBFS Traversal (starting from New York):\n";
    roadNetwork.BFS("New York", [](const std::string& city) { 
        std::cout << city << " "; 
    });

    // DFS Traversal
    std::cout << "\n\nDFS Traversal (starting from Boston):\n";
    roadNetwork.DFS("Boston", [](const std::string& city) { 
        std::cout << city << " "; 
    });

    // Directed graph example (task dependencies)
    Graph<std::string> taskGraph(Graph<std::string>::Type::DIRECTED);
    taskGraph.addEdge("Wake Up", "Brush Teeth");
    taskGraph.addEdge("Brush Teeth", "Eat Breakfast");
    taskGraph.addEdge("Eat Breakfast", "Go to Work");

    std::cout << "\n\nTask Dependency Graph (Directed):\n";
    taskGraph.print();

    return 0;
}