#include "setgraph.h"

SetGraph::SetGraph(int _verticesCount) : graph(_verticesCount), verticesCount(_verticesCount){}

SetGraph::SetGraph(const IGraph &igraph) : SetGraph(igraph.VerticesCount()) {
    for (int vertice = 0; vertice < verticesCount; ++vertice) {
        std::vector<int> row = igraph.GetNextVertices(vertice);
        for (int other_vertice : row) {
            graph[vertice].insert(other_vertice);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    graph[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (int child = 0; child < verticesCount; ++child) {
        if (graph[vertex].find(child) != graph[vertex].end()) {
            result.push_back(child);
        }
    }
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int parent = 0; parent < verticesCount; ++parent) {
        if (graph[parent].find(vertex) != graph[parent].end()) {
            result.push_back(parent);
        }
    }
    return result;
}
