#include "SetGraph.h"
SetGraph::SetGraph(int vertices_count) : vertices_count_(vertices_count)
{
    graph_.resize(vertices_count);
}

SetGraph::SetGraph(const IGraph &igraph)
{
    int len = igraph.VerticesCount();
    graph_.resize(len);
    vertices_count_ = len;
    for (int i = 0; i < len; i++)
    {
        std::vector<int> edges = igraph.GetNextVertices(i);
        for (auto &elm : edges)
        {
            graph_[i].insert(elm);
        }
    }
}
SetGraph::~SetGraph() {}

// Добавление ребра от from к to.
void SetGraph::AddEdge(int from, int to)
{
    graph_[from].insert(to);
}

int SetGraph::VerticesCount() const
{
    return vertices_count_;
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    std::vector<int> res;
    for (auto &it : graph_[vertex])
        res.push_back(it);
    return res;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> res;
    for (int i = 0; i < vertices_count_; i++)
    {
        for (auto &edge : graph_[i])
            if (edge == vertex)
                res.push_back(i);
    }
    return res;
}
