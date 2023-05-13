#pragma once
#include "IGraph.h"
#include <set>

class SetGraph : public IGraph
{
public:
    SetGraph(int vertices_count);

    SetGraph(const IGraph &igraph);
    ~SetGraph();

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::set<int>> graph_;
    int vertices_count_;
};
