#pragma once

#include "igraph.h"

class ListGraph : public IGraph {
 public:
    explicit ListGraph(int _verticesCount);
    explicit ListGraph(const IGraph &);
    ~ListGraph() override=default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    std::vector< std::vector<int> > graph;
    int verticesCount;
};
