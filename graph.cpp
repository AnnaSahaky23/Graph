
#include <iostream>
#include <vector>
#include <algorithm>

void DFSRecursive(std::vector<std::vector<int>>& graph, std::vector<bool>& visited, int vertex)
{
    visited[vertex] = true;

    for (int i = 0; i < graph[vertex].size(); ++i)
    {
        int neighbour = graph[vertex][i];
        if (!visited[neighbour])
        {
            DFSRecursive(graph, visited, neighbour);
        }
    }
}


bool IsConnected(std::vector<std::vector<int>>& graph, std::vector<bool>& visited)
{
    int v = graph.size();
    if (v == 0) return true;
    for(auto it : visited){
        if(it == 0){
            return false;
        }
    }
    return true;

}

int getCountOfConnectedComponent(std::vector<std::vector<int>>& graph){
    std::vector<bool> visited(graph.size(),false);
    int CountOfConnectedComponent = 0;
    for(int i = 0; i < graph.size(); i++){
        if(!visited[i]){
            DFSRecursive(graph,visited,i);
            CountOfConnectedComponent++;
        }
    }
    return CountOfConnectedComponent;
}

std::vector<std::vector<int>> MakeGraphWithoutComponent(std::vector<std::vector<int>>& graph, int vertex){
    std::vector<std::vector<int>> ret;
    ret = graph;
    for(int i = 0; i < ret[vertex].size(); i++){
        auto it = find(ret[ret[vertex][i]].begin(),ret[ret[vertex][i]].end(),vertex);
        ret[ret[vertex][i]].erase(it);
    }
    auto it = ret.begin()+vertex;
    ret.erase(it);
    for(int i = 0; i < ret.size(); i++){
        for(int j = 0; j < ret[i].size(); j++){
            if(ret[i][j] > vertex){
                ret[i][j]--;
            }
        }
    }
    return ret;
}

std::vector<int> FindArticulationPoints(std::vector<std::vector<int>>& graph){
    std::vector<int> ret;
    for(int i = 0; i < graph.size(); i++){
        std::vector<std::vector<int>> tmp = MakeGraphWithoutComponent(graph, i);
        int CompCountGraph = getCountOfConnectedComponent(graph);
        int CompCountTmp = getCountOfConnectedComponent(tmp);
        if(CompCountGraph < CompCountTmp){
            ret.push_back(i);
        }
    }
    return ret;
}

int main()
{

    std::vector<std::vector<int>> graph = {
        { 1, 4, 6},
        { 0, 6},
        { },
        { 6 },
        { 0, 6 },
        { 7 },
        { 0,1, 3, 4},
        {5}
    };

    std::vector<int> ret = FindArticulationPoints(graph);
    for(auto it : ret){
        std::cout<<it<<' ';
    }
    return 0;
}