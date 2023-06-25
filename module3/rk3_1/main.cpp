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

int dfs( const IGraph& graph ) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::stack<int> st;

    for (int vertex = 0; vertex < graph.VerticesCount(); vertex++){
        if( !visited[vertex] ){
            st.push(vertex);

            while (!st.empty()) {
                vertex = st.top();
                st.pop();

                if (!visited[vertex]){
                    visited[vertex] = true;
                    if ( graph.GetNextVertices(vertex).size() > 2){
                        return 0;
                    }
                }

                std::vector<int> children = graph.GetNextVertices(vertex);
                for (int child: children) {
                    if (!visited[child]) {
                        st.push(child);
                    }
                }
            }
        }
    }

    return 1;
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

    int result = dfs(graph);
    
    if ( m != n - 1) {
        result = 0;
    }

    std::cout << result;

    return 0;
}