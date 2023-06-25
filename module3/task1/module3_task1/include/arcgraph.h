#pragma once

#include "igraph.h"

class ArcGraph : public IGraph {
 public:
    explicit ArcGraph(int vertices_count);
    explicit ArcGraph(const IGraph &);
    ~ArcGraph() override=default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

 private:
    std::vector< std::pair<int, int> > graph;
    int verticesCount;
};
