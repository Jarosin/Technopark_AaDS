#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertices_count) : vertices_count_(vertices_count)
{
    graph_.resize(vertices_count);
    for (int i = 0; i < vertices_count_; i++)
    {
        graph_[i].resize(vertices_count_, 0);
    }
}

MatrixGraph::MatrixGraph(const IGraph &igraph)
{
    int len = igraph.VerticesCount();
    graph_.resize(len);
    vertices_count_ = len;
    for (int i = 0; i < len; i++)
    {
        graph_[i].resize(len, 0);
        std::vector<int> edges = igraph.GetNextVertices(i);
        for (auto &elm : edges)
        {
            graph_[i][elm] += 1;
        }
    }
}
MatrixGraph::~MatrixGraph() {}

// Добавление ребра от from к to.
void MatrixGraph::AddEdge(int from, int to)
{
    graph_[from][to] += 1;
}

int MatrixGraph::VerticesCount() const
{
    return vertices_count_;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
    std::vector<int> res;
    for (int i = 0; i < vertices_count_; i++)
    {
        for (int j = 0; j < graph_[vertex][i]; j++) // добавляем по количеству
            res.push_back(i);                       // добавляем по номеру вершины
    }
    return res;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> res;
    for (int i = 0; i < graph_.size(); i++)
    {
        for (int j = 0; j < graph_[i][vertex]; j++)
            res.push_back(i);
    }
    return res;
}
