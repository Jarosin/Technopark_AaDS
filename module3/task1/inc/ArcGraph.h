#pragma once
#include "IGraph.h"
#include <utility>

class ArcGraph : public IGraph
{
public:
    ArcGraph(int vertices_count);

    ArcGraph(const IGraph &igraph);
    ~ArcGraph();

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int> > graph_;
    int vertices_count_;
};
