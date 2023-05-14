// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами.
// Требования: сложность O(V+E).
// Формат ввода.
// v: кол-во вершин (макс. 50000),
// n: кол-во ребер (макс. 200000),
// n пар реберных вершин,
// пара вершин u, w для запроса.
// Формат вывода.
// Количество кратчайших путей от u к w.

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <queue>

struct IGraph
{
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph
{
public:
    ListGraph(int vertices_count) : vertices_count_(vertices_count)
    {
        graph_.resize(vertices_count);
    }

    ListGraph(const IGraph &igraph)
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
    ~ListGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override
    {
        graph_[from].push_back(to);
        graph_[to].push_back(from);
    }

    virtual int VerticesCount() const override
    {
        return vertices_count_;
    }

    virtual std::vector<int> GetNextVertices(int vertex) const override
    {
        std::vector<int> res;
        res.reserve(graph_[vertex].size());
        for (auto &it : graph_[vertex])
        {
            res.push_back(it);
        }
        return res;
    }
    virtual std::vector<int> GetPrevVertices(int vertex) const override
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

    int findShortestPathsAmount(int from, int to)
    {
        if (from == to)
            return 0;
        std::vector<int> path_lengths(VerticesCount(), -1);
        std::vector<int> path_count(VerticesCount(), -1);
        std::queue<int> path_top;
        path_top.push(from);
        path_lengths[from] = 0;
        path_count[from] = 1;
        while (!path_top.empty())
        {
            int top = path_top.front();
            path_top.pop();
            std::vector<int> top_linked = GetNextVertices(top);
            for (auto &elem : top_linked)
            {
                if (path_lengths[elem] > path_lengths[top] + 1)
                {
                    path_count[elem] = path_count[top];
                    path_lengths[elem] = path_lengths[top] + 1;
                    path_top.push(elem);
                }
                else if (path_lengths[elem] == path_lengths[top] + 1)
                {
                    path_count[elem] += path_count[top];
                }
                else if (path_lengths[elem] == -1)
                {
                    path_top.push(elem);
                    path_lengths[elem] = path_lengths[top] + 1;
                    path_count[elem] = path_count[top];
                }
            }
        }
        return path_count[to];
    }

private:
    std::vector<std::vector<int>> graph_;
    int vertices_count_;
};


int main()
{
    int len = 0;
    int n = 0;
    std::cin >> len;
    ListGraph graph(len);
    std::cin >> n;
    int start, end;
    for (int i = 0; i < n; i++)
    {
        std::cin >> start >> end;
        graph.AddEdge(start, end);
    }
    std::cin >> start >> end;
    std::cout << graph.findShortestPathsAmount(start, end);
    return 0;
}
