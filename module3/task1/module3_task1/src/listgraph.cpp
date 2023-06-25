#include "listgraph.h"

ListGraph::ListGraph(int _verticesCount) : graph(_verticesCount), verticesCount(_verticesCount) {}

ListGraph::ListGraph(const IGraph &igraph) : ListGraph(igraph.VerticesCount()) {
    for (int vert = 0; vert < verticesCount; ++vert) {
        graph[vert] = igraph.GetNextVertices(vert);
    }
}


void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    result.reserve(graph[vertex].size());
    for ( int v : graph[vertex] ) {
        result.push_back(v);
    }
    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int parent = 0; parent < verticesCount; ++parent) {
        for (int child : graph[parent]) {
            if ( child == vertex ) {
                result.push_back(parent);
                break;
            }
        }
    }
    return result;
}