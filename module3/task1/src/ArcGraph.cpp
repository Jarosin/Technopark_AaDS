#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertices_count) : vertices_count_(vertices_count)
{
    graph_.resize(vertices_count);
}

ArcGraph::ArcGraph(const IGraph &igraph)
{
    int len = igraph.VerticesCount();
    vertices_count_ = len;
    for (int i = 0; i < len; i++)
    {
        std::vector<int> edges = igraph.GetNextVertices(i);
        for (auto &elm : edges)
        {
            std::pair<int, int> edge(i, elm);
            graph_.push_back(edge);
        }
    }
}
ArcGraph::~ArcGraph() {

}

// Добавление ребра от from к to.
void ArcGraph::AddEdge(int from, int to)
{
    std::pair<int, int> edge(from, to);
    graph_.push_back(edge);
}

int ArcGraph::VerticesCount() const
{
    return vertices_count_;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const
{
    std::vector<int> res;
    for (auto &it : graph_)
    {
        if (it.first == vertex)
            res.push_back(it.second);
    }
    return res;
}
std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> res;
    for (auto &it : graph_)
    {
        if (it.second == vertex)
            res.push_back(it.first);
    }
    return res;
}
