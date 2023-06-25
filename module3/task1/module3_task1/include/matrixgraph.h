#pragma once

#include "igraph.h"

class MatrixGraph : public IGraph {
 public:
    explicit MatrixGraph(int _verticesCount);
    explicit MatrixGraph(const IGraph &);
    ~MatrixGraph() override=default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    std::vector< std::vector<int> > graph;
    int verticesCount;
};
