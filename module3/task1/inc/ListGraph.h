#pragma once
#include <IGraph.h>

class ListGraph : public IGraph
{
public:
    ListGraph(int vertices_count);

    ListGraph(const IGraph &igraph);
    ~ListGraph();

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> graph_;
    int vertices_count_;
};
