/**
 * GraphMatrix.h
 * 
 * This file defines a generic GraphMatrix class using an adjacency matrix representation.
 * The graph supports both directed and undirected types, and allows for weighted edges.
 * 
 * Structure:
 * - The graph is stored as a 2D vector (matrix) of weights.
 * - Each vertex is mapped to an index using an unordered_map.
 * - Vertices are stored in a vector to maintain insertion order and index mapping.
 * - Supports adding vertices and edges, checking for edges/vertices, and printing the matrix.
 * 
 * Complexity:
 * - Adding a vertex: O(V), where V is the number of vertices (due to resizing the matrix)
 * - Adding an edge: O(1)
 * - Checking for a vertex: O(1)
 * - Checking for an edge: O(1)
 * - Printing the matrix: O(V^2)
 * - Space complexity: O(V^2), where V is the number of vertices
 */

#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

template <typename VertexType, typename WeightType = int>
class GraphMatrix {
private:
    std::vector<std::vector<WeightType>> matrix;
    std::unordered_map<VertexType, size_t> vertexIndices;
    std::vector<VertexType> vertices;
    bool isDirected;

public:
    explicit GraphMatrix(bool directed = false) : isDirected(directed) {}

    void addVertex(const VertexType& vertex) {
        if (vertexIndices.find(vertex) != vertexIndices.end()) return;
        
        vertexIndices[vertex] = vertices.size();
        vertices.push_back(vertex);
        
        // Resize matrix
        for (auto& row : matrix) row.push_back(WeightType{});
        matrix.emplace_back(vertices.size(), WeightType{});
    }

    void addEdge(const VertexType& src, const VertexType& dest, WeightType weight = WeightType{}) {
        addVertex(src);
        addVertex(dest);
        
        size_t i = vertexIndices[src];
        size_t j = vertexIndices[dest];
        matrix[i][j] = weight;
        
        if (!isDirected) matrix[j][i] = weight;
    }

    bool hasEdge(const VertexType& src, const VertexType& dest) const {
        if (!hasVertex(src) || !hasVertex(dest)) return false;
        return matrix[vertexIndices.at(src)][vertexIndices.at(dest)] != WeightType{};
    }

    bool hasVertex(const VertexType& vertex) const {
        return vertexIndices.find(vertex) != vertexIndices.end();
    }

    void print() const {
        std::cout << "  ";
        for (const auto& v : vertices) std::cout << v << " ";
        std::cout << "\n";

        for (size_t i = 0; i < matrix.size(); ++i) {
            std::cout << vertices[i] << " ";
            for (const auto& val : matrix[i]) {
                std::cout << val << " ";
            }
            std::cout << "\n";
        }
    }
};

#endif // GRAPH_MATRIX_H