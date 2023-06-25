#include <vector>
#include <iostream>
#include <climits>
#include <queue>
#include <sstream>
#include <stack>
#include <assert.h>

#include "arcgraph.h"
#include "listgraph.h"
#include "matrixgraph.h"
#include "setgraph.h"

// не используется, но удалять жалко
void recursive_dfs_aux( const IGraph& graph, int vertex, std::vector<bool>& visited, void (*callback)(int vertex)){
    visited[vertex] = true;
    callback(vertex);

    std::vector<int> children = graph.GetNextVertices(vertex);
    for( int child : children ) {
        if(!visited[child]) {
            recursive_dfs_aux(graph, child, visited, callback);
        }
    }
}

void recursive_dfs( const IGraph& graph, void (*callback)(int vertex)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int vertex = 0; vertex < graph.VerticesCount(); vertex++){
        if( !visited[vertex] ){
            recursive_dfs_aux(graph, vertex, visited, callback);
        }
    }
}


void dfs(const IGraph& graph, void (*callback)(int vertex)) {
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
                    callback(vertex);
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
}

void bfs(const IGraph& graph, void (*callback)(int vertex)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> q;
    for (int vertex = 0; vertex < graph.VerticesCount(); vertex++){
        if( !visited[vertex] ){
            q.push(vertex);
            visited[vertex] = true;
            while ( !q.empty() ) {
                int cur_vertex = q.front();
                q.pop();
                
                callback(cur_vertex);
                
                std::vector<int> children = graph.GetNextVertices(vertex);
                for( int child : children ) {
                    if(!visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }
        }
    }
} 

void run() {
    // listgraph
    ListGraph lgraph(4);
    lgraph.AddEdge(0, 1); // ромб
    lgraph.AddEdge(0, 2);
    lgraph.AddEdge(1, 3);
    lgraph.AddEdge(2, 3);

    std::cout << "List dfs: ";
    dfs(lgraph, [](int v){
        std::cout << v << " ";
    });
    std::cout << std::endl;
    std::cout << "List bfs: ";
    bfs(lgraph, [](int v){
        std::cout << v << " ";
    });
    std::cout << std::endl;


    MatrixGraph mgraph(4);
    mgraph.AddEdge(0, 1); // ромб
    mgraph.AddEdge(0, 2);
    mgraph.AddEdge(1, 3);
    mgraph.AddEdge(2, 3);

    std::cout << "Matr dfs: ";
    dfs(mgraph, [](int v){
        std::cout << v << " ";
    });
    std::cout << std::endl;
    std::cout << "Matr bfs: ";
    bfs(mgraph, [](int v){
        std::cout << v << " ";
    });
    std::cout << std::endl;


    SetGraph sgraph(4);
    sgraph.AddEdge(0, 1); // ромб
    sgraph.AddEdge(0, 2);
    sgraph.AddEdge(1, 3);
    sgraph.AddEdge(2, 3);

    std::cout << "Set dfs: ";
    dfs(sgraph, [](int v){
        std::cout << v << " ";
    });
    std::cout << std::endl;
    std::cout << "Set bfs: ";
    bfs(sgraph, [](int v){
        std::cout << v << " ";
    });
    std::cout << std::endl;


    ArcGraph agraph(4);
    agraph.AddEdge(0, 1); // ромб
    agraph.AddEdge(0, 2);
    agraph.AddEdge(1, 3);
    agraph.AddEdge(2, 3);

    std::cout << "Arc dfs: ";
    dfs(agraph, [](int v){
        std::cout << v << " ";
    });
    std::cout << std::endl;
    std::cout << "Arc bfs: ";
    bfs(agraph, [](int v){
        std::cout << v << " ";
    });
    std::cout << std::endl;
}

int main() {
    run();
    return 0;
}
