#pragma once
#include "IGraph.h"


class MatrixGraph : public IGraph
{
public:
    MatrixGraph(int vertices_count);

    MatrixGraph(const IGraph &igraph);
    ~MatrixGraph();

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<int>> graph_;
    int vertices_count_;
};
