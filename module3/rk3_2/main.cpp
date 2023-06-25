#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <stack>

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

int isEulerian(const IGraph& graph) {
    int verticesCount = graph.VerticesCount();
    std::vector<int> degrees(verticesCount, 0);

    for (int i = 0; i < verticesCount; ++i) {
        degrees[i] = graph.GetNextVertices(i).size();
    }

    int oddDegreesCount = 0;
    for (int i = 0; i < verticesCount; ++i) {
        if (degrees[i] % 2 == 1) {
            ++oddDegreesCount;
        }
    }

    if (oddDegreesCount == 0) {
        return 1; 
    } else if (oddDegreesCount == 2) {
        int firstOddDegreeVertex = -1;
        int secondOddDegreeVertex = -1;

        for (int i = 0; i < verticesCount; ++i) {
            if (degrees[i] % 2 == 1) {
                if (firstOddDegreeVertex == -1) {
                    firstOddDegreeVertex = i;
                } else {
                    secondOddDegreeVertex = i;
                    break;
                }
            }
        }
        degrees[firstOddDegreeVertex]--;
        degrees[secondOddDegreeVertex]--;
        std::vector<bool> visited(verticesCount, false);
        std::stack<int> stack;
        stack.push(firstOddDegreeVertex);

        while (!stack.empty()) {
            int cur = stack.top();
            stack.pop();
            visited[cur] = true;
            for (auto next : graph.GetNextVertices(cur)) {
                if (!visited[next] && degrees[next] > 0) {
                    stack.push(next);
                    --degrees[next];
                }
            }
        }

        for (int i = 0; i < verticesCount; ++i) {
            if (degrees[i] % 2 == 1) {
                return 0; 
            }
        }

        return 1; 
    } else {
        return 0; 
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    ListGraph graph(n);

    for (int i = 0; i < m; ++i) {
        int from = 0; 
        int to = 0;
        std::cin >> from;
        std::cin >> to;
        graph.AddEdge(from, to);
    }

    int result = isEulerian(graph);
    
    std::cout << result;

    return 0;
}