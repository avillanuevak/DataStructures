#ifndef GRAPH_HYBRID_H
#define GRAPH_HYBRID_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

// GraphHybrid uses an adjacency list representation with a hash table (unordered_map)
// for fast vertex lookup and a vector of edges for each vertex.
// - Vertex lookup: O(1) average (unordered_map)
// - Edge insertion: O(1) average (vector push_back)
// - Edge existence check: O(k) where k = out-degree of src vertex

template <typename VertexType, typename WeightType = int>
class GraphHybrid {
private:
    struct Edge {
        VertexType dest;
        WeightType weight;
        Edge(const VertexType& d, WeightType w) : dest(d), weight(w) {}
    };

    // Adjacency map: maps each vertex to a list of outgoing edges
    std::unordered_map<VertexType, std::vector<Edge>> adjMap;
    bool isDirected;

public:
    // Constructor: O(1)
    explicit GraphHybrid(bool directed = false) : isDirected(directed) {}

    // Add a vertex: O(1) average
    void addVertex(const VertexType& vertex) {
        if (adjMap.find(vertex) == adjMap.end()) {
            adjMap[vertex] = std::vector<Edge>();
        }
    }

    // Add an edge: O(1) average (adds both directions if undirected)
    void addEdge(const VertexType& src, const VertexType& dest, WeightType weight = WeightType{}) {
        addVertex(src);   // O(1)
        addVertex(dest);  // O(1)
        adjMap[src].emplace_back(dest, weight); // O(1)
        if (!isDirected) adjMap[dest].emplace_back(src, weight); // O(1)
    }

    // Check if an edge exists: O(k), k = out-degree of src
    bool hasEdge(const VertexType& src, const VertexType& dest) const {
        if (!hasVertex(src) || !hasVertex(dest)) return false;
        for (const auto& edge : adjMap.at(src)) {
            if (edge.dest == dest) return true;
        }
        return false;
    }

    // Check if a vertex exists: O(1) average
    bool hasVertex(const VertexType& vertex) const {
        return adjMap.find(vertex) != adjMap.end();
    }

    // Print the graph: O(V + E)
    void print() const {
        for (const auto& [src, edges] : adjMap) {
            std::cout << src << " -> ";
            for (const auto& edge : edges) {
                std::cout << "[" << edge.dest << ", " << edge.weight << "] ";
            }
            std::cout << "\n";
        }
    }
};

#endif // GRAPH_HYBRID_H