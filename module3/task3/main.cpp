#include <iostream>
#include <vector>
#include <limits>
#include <set>

struct IGraph {
    virtual ~IGraph()=default;

    virtual void AddEdge(int from, int to, int weight)=0;

    virtual int VerticesCount() const=0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const=0;

};

class ListGraph : public IGraph{
    public:
        explicit ListGraph(int size);
        ~ListGraph()=default;

        void AddEdge(int from, int to, int weight) override;
        int VerticesCount() const;
        std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override; 

    private:
        std::vector<std::vector<std::pair<int, int>>> graph;
        int verticesCount;
};

ListGraph::ListGraph(int size) : verticesCount(size), graph(size) {}

std::vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
    return graph[vertex];
}

int ListGraph::VerticesCount() const {
    return verticesCount;
}

void ListGraph::AddEdge(int from, int to, int weight) {
    graph[from].push_back(std::make_pair(to, weight));
    graph[to].push_back(std::make_pair(from, weight));
}

int countShortestPaths(const IGraph& graph, int from, int to) {
    std::vector<int> dist(graph.VerticesCount(), std::numeric_limits<int>::max());
    std::set<std::pair<int, int>> s;
    dist[from] = 0;    
    s.insert(std::make_pair(0, from));

    while (!s.empty()) {
        int current = s.begin()->second; 
        s.erase(s.begin());
        for ( auto next : graph.GetNextVertices(current) ) {
            if ( dist[next.first] == std::numeric_limits<int>::max() ) {
                dist[next.first] = dist[current] + next.second;
                s.insert(std::make_pair(dist[next.first], next.first));
            } else if ( dist[next.first] > dist[current] + next.second ) {
                s.erase(std::make_pair(dist[next.first], next.first));
                dist[next.first] = dist[current] + next.second;
                s.insert(std::make_pair(dist[next.first], next.first));
            }
        }
    }
    return dist[to];
}


int main() {
    int vertices = 0, edges = 0;

    std::cin >> vertices;
    std::cin >> edges;

    ListGraph graph(vertices);

    int from = 0, to = 0, weight = 0;
    
    for (int i = 0; i < edges; i++) {
        std::cin >> from;
        std::cin >> to;
        std::cin >> weight;
        graph.AddEdge(from, to, weight);
    }

    std::cin >> from;
    std::cin >> to;

    std::cout << countShortestPaths(graph, from, to) << std::endl;
    
    return 0;
}