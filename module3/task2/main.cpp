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
        std::vector<int> path_lengths(VerticesCount(), -1);
        std::vector<int> path_count(VerticesCount(), 0);
        std::queue<int> vertices_queue;
        vertices_queue.push(from);
        path_lengths[from] = 0;
        path_count[from] = 1;
        while (!vertices_queue.empty())
        {
            int current_node = vertices_queue.front();
            vertices_queue.pop();
            std::vector<int> adj_list = GetNextVertices(current_node);
            for (auto &adjacent_node : adj_list)
            {
                if (path_lengths[adjacent_node] == path_lengths[current_node] + 1)
                {
                    path_count[adjacent_node] += path_count[current_node];
                }
                if (path_lengths[adjacent_node] == -1)
                {
                    vertices_queue.push(adjacent_node);
                    path_lengths[adjacent_node] = path_lengths[current_node] + 1;
                    path_count[adjacent_node] = path_count[current_node];
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
