/**
 * Graph.h
 * 
 * This file defines a generic Graph class using an adjacency list representation.
 * The graph supports both directed and undirected types, and allows for weighted edges.
 * 
 * Structure:
 * - The graph is stored as an unordered_map from each vertex to a list of Edge structs.
 * - Each Edge contains a destination vertex and an optional weight.
 * - Vertices and edges can be added dynamically.
 * - Supports traversal algorithms (BFS and DFS), as well as utility methods for querying vertices and edges.
 * 
 * Complexity:
 * - Adding a vertex: O(1)
 * - Adding an edge: O(1) (amortized, assuming unordered_map and list operations are O(1))
 * - Checking for a vertex: O(1)
 * - Checking for an edge: O(k), where k is the number of edges from the source vertex
 * - BFS/DFS traversal: O(V + E), where V is the number of vertices and E is the number of edges
 * - Space complexity: O(V + E)
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <queue>
#include <functional>

template <typename VertexType, typename WeightType = int>
class Graph {
public:
    // Edge structure (destination + weight)
    struct Edge {
        VertexType dest;
        WeightType weight;
        Edge(const VertexType& d, WeightType w = WeightType{}) 
            : dest(d), weight(w) {}
    };

    // Graph type (directed/undirected)
    enum class Type { DIRECTED, UNDIRECTED };

private:
    std::unordered_map<VertexType, std::list<Edge>> adjList;
    Type graphType;

public:
    explicit Graph(Type type = Type::UNDIRECTED) : graphType(type) {}

    // Add a vertex (if not already present)
    void addVertex(const VertexType& vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = std::list<Edge>();
        }
    }

    // Add an edge (and vertices if needed)
    void addEdge(const VertexType& src, const VertexType& dest, WeightType weight = WeightType{}) {
        addVertex(src);
        addVertex(dest);
        adjList[src].emplace_back(dest, weight);
        if (graphType == Type::UNDIRECTED) {
            adjList[dest].emplace_back(src, weight);
        }
    }

    // Check if a vertex exists
    bool hasVertex(const VertexType& vertex) const {
        return adjList.find(vertex) != adjList.end();
    }

    // Check if an edge exists
    bool hasEdge(const VertexType& src, const VertexType& dest) const {
        if (!hasVertex(src) || !hasVertex(dest)) return false;
        const auto& edges = adjList.at(src);
        return std::any_of(edges.begin(), edges.end(), 
            [&dest](const Edge& e) { return e.dest == dest; });
    }

    // Get all vertices
    std::vector<VertexType> vertices() const {
        std::vector<VertexType> result;
        for (const auto& pair : adjList) {
            result.push_back(pair.first);
        }
        return result;
    }

    // Get edges from a vertex
    const std::list<Edge>& edgesFrom(const VertexType& src) const {
        if (!hasVertex(src)) throw std::out_of_range("Vertex not found");
        return adjList.at(src);
    }

    // Print the graph (for debugging)
    void print() const {
        for (const auto& pair : adjList) {
            std::cout << pair.first << " -> ";
            for (const Edge& e : pair.second) {
                std::cout << "[" << e.dest << ", " << e.weight << "] ";
            }
            std::cout << "\n";
        }
    }

    // BFS (Breadth-First Search)
    void BFS(const VertexType& start, std::function<void(const VertexType&)> visit) const {
        if (!hasVertex(start)) return;
        std::unordered_map<VertexType, bool> visited;
        std::queue<VertexType> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            VertexType current = q.front();
            q.pop();
            visit(current);

            for (const Edge& e : adjList.at(current)) {
                if (!visited[e.dest]) {
                    visited[e.dest] = true;
                    q.push(e.dest);
                }
            }
        }
    }

    // DFS (Depth-First Search)
    void DFS(const VertexType& start, std::function<void(const VertexType&)> visit) const {
        if (!hasVertex(start)) return;
        std::unordered_map<VertexType, bool> visited;
        DFSHelper(start, visited, visit);
    }

private:
    void DFSHelper(const VertexType& current, std::unordered_map<VertexType, bool>& visited, 
                   std::function<void(const VertexType&)> visit) const {
        visit(current);
        visited[current] = true;

        for (const Edge& e : adjList.at(current)) {
            if (!visited[e.dest]) {
                DFSHelper(e.dest, visited, visit);
            }
        }
    }
};

#endif // GRAPH_H