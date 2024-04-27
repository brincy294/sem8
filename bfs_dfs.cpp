#include <iostream>
#include <omp.h>
#include <vector>
#include <queue>
using namespace std;
const int MAX_VERTICES = 100;

void dfs_recursive(vector<vector<int>>& graph, int vertex, vector<bool>& visited){
    visited[vertex] = true;
    cout<<vertex<<" ";
    #pragma omp parallel for
    for (int neighbor : graph[vertex]){
        if (!visited[neighbor]){
            dfs_recursive(graph, neighbor, visited);
        }
    }
}

void dfs(vector<vector<int>>& graph, int start_vertex){
    vector<bool> visited(graph.size(), false);
    dfs_recursive(graph, start_vertex, visited);
}

void bfs(vector<vector<int>>& graph, int start_vertex){
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(start_vertex);
    visited[start_vertex] = true;
    while(!q.empty()){
        int vertex = q.front();
        q.pop();
        cout<<vertex<<" ";
        #pragma omp parallel for
        for (int neighbor : graph[vertex]){
            if (!visited[neighbor]){
                #pragma omp critical
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
}

int main(){
    vector<vector<int>> graph(MAX_VERTICES);
    int num_edges, num_vertices;
    cout<<"Enter number of vertices: ";
    cin>>num_vertices;
    cout<<"Enter number of edges: ";
    cin>>num_edges;

    cout<<"Enter v1 and v2:"<<endl;
    for(int i=0; i<num_edges; ++i){
        int v1, v2;
        cin>>v1>>v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    int start_vertex;
    cout<<"Enter starting vertex: ";
    cin>>start_vertex;

    cout<<"\nBFS Traversal: ";
    bfs(graph, start_vertex);
    cout<<"\nDFS Traversal: ";
    dfs(graph, start_vertex);
}