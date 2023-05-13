#include "ListGraph.h"

ListGraph::ListGraph(int vertices_count) : vertices_count_(vertices_count)
{
    graph_.resize(vertices_count);
}

ListGraph::ListGraph(const IGraph &igraph)
{
    int len = igraph.VerticesCount();
    vertices_count_ = len;
    graph_.reserve(len);
    for (int i = 0; i < len; i++)
    {
        std::vector<int> edges = igraph.GetNextVertices(i);
        graph_[i].reserve(edges.size());
        graph_[i].insert(std::begin(graph_[i]), std::begin(edges), std::end(edges));
    }
}
ListGraph::~ListGraph() {}

// Добавление ребра от from к to.
void ListGraph::AddEdge(int from, int to)
{
    graph_[from].push_back(to);
}

int ListGraph::VerticesCount() const
{
    return vertices_count_;
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
    std::vector<int> res;
    res.reserve(graph_[vertex].size());
    for (auto &it : graph_[vertex])
    {
        res.push_back(it);
    }
    return res;
}
std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> res;
    for (int i = 0; i < graph_.size(); i++)
    {
        for (int j = 0; j < graph_[i].size(); j++)
        {
            if (graph_[i][j] == vertex)
            {
                res.push_back(i);
            }
        }
    }
    return res;
}
