#include "matrixgraph.h"

MatrixGraph::MatrixGraph(int _verticesCount) : graph(_verticesCount, std::vector<int>(_verticesCount, 0)), verticesCount(_verticesCount) {}

MatrixGraph::MatrixGraph(const IGraph &igraph) : MatrixGraph(igraph.VerticesCount()) {
    for (int vertice = 0; vertice < verticesCount; ++vertice) {
        std::vector<int> row = igraph.GetNextVertices(vertice);
        for (int other_vertice : row) {
            graph[vertice][other_vertice] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    graph[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> next_vertices;
    
    for (int child = 0; child < verticesCount; ++child) {
        if (graph[vertex][child] == 1) {
            next_vertices.push_back(child);
        }
    }
    
    return next_vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev_vertices;
    
    for (int parent = 0; parent < verticesCount; ++parent) {
        if (graph[parent][vertex] == 1) {
            prev_vertices.push_back(parent);
        }
    }

    return prev_vertices;
}
