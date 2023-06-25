
#include <iostream>
#include <queue>
#include <vector>
#include <limits>

struct IGraph {
    virtual ~IGraph()=default;

    virtual void AddEdge(int from, int to)=0;

    virtual int VerticesCount() const=0;

    virtual std::vector<int> GetNextVertices(int vertex) const=0;
    virtual std::vector<int> GetPrevVertices(int vertex) const=0;
};


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


ListGraph::ListGraph(int _verticesCount) : graph(_verticesCount), verticesCount(_verticesCount) {}

ListGraph::ListGraph(const IGraph &igraph) : ListGraph(igraph.VerticesCount()) {
    for (int vert = 0; vert < verticesCount; ++vert) {
        graph[vert] = igraph.GetNextVertices(vert);
    }
}


void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
    graph[to].push_back(from);
    
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


int countShortestPaths(const IGraph &graph, const int from, const int to) {
    int n = graph.VerticesCount();
    std::vector<int> dist(n, std::numeric_limits<int>::max());
    dist[from] = 0;
    std::vector<int> pathes(n, 0);
    pathes[from] = 1;

    std::queue<int> q;
    q.push(from);
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (const auto &next: graph.GetNextVertices(current)) {
            if (dist[next] > dist[current] + 1) {
                dist[next] = dist[current] + 1;
                pathes[next] = pathes[current];
                q.push(next);
            } else if (dist[next] == dist[current] + 1) {
                pathes[next] += pathes[current];
            }
        }
    }
    return pathes[to];
}

int main() {
    int v = 0; 
    int n = 0;
    
    std::cin >> v;
    std::cin >> n;
    
    ListGraph graph(v);

    for (int i = 0; i < n; ++i) {
        int from = 0; 
        int to = 0;
        std::cin >> from;
        std::cin >> to;
        graph.AddEdge(from, to);
    }

    int from = 0, to = 0;
    
    std::cin >> from;
    std::cin >> to;

    std::cout << countShortestPaths(graph, from, to) << std::endl;

    return 0;
}