#include "arcgraph.h"

ArcGraph::ArcGraph(int verticesCount) : verticesCount(verticesCount) {}

ArcGraph::ArcGraph(const IGraph &igraph) : ArcGraph(igraph.VerticesCount()) {
    for (int vertice = 0; vertice < verticesCount; ++vertice) {
        std::vector<int> related_nodes = igraph.GetNextVertices(vertice);
        for (int other_node : related_nodes) {
            graph.emplace_back(vertice, other_node);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    std::pair<int, int> new_edge(from, to);
    graph.emplace_back(new_edge);
}

int ArcGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (const auto &pair : graph) {
        if (pair.first == vertex) {
            result.push_back(pair.second);
        }
    }
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (const auto &linkage : graph) {
        if (linkage.second == vertex) {
            result.push_back(linkage.first);
        }
    }
    return result;
}