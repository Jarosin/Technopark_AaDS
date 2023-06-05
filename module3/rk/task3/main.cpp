#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <queue>
#include <stack>

struct IGraph
{
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
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
            std::vector<std::pair<int, int>> edges = igraph.GetNextVertices(i);
            graph_[i].reserve(edges.size());
            graph_[i].insert(std::begin(graph_[i]), std::begin(edges), std::end(edges));
        }
    }
    ~ListGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, int weight) override
    {
        graph_[from].emplace_back(to, weight);
    }

    virtual int VerticesCount() const override
    {
        return vertices_count_;
    }

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override
    {
        return graph_[vertex];
    }
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override
    {
        std::vector<std::pair<int, int>> res;
        for (int i = 0; i < graph_.size(); i++)
        {
            for (int j = 0; j < graph_[i].size(); j++)
            {
                if (graph_[i][j].first == vertex)
                {
                    res.push_back(graph_[i][j]);
                }
            }
        }
        return res;
    }

    // куда, за сколько
    int findShortestPathShorterThanK(int k, int from, int to)
    {
        int min = -1;
        std::queue<std::pair<int, int>> paths;
        std::pair<int, int> temp(from, 0);
        std::vector<int>shortest_paths(vertices_count_, -1);
        paths.push(temp);
        for (int i = 0; i <= k; i++)
        {
            int len = paths.size();
            for (int j = 0; j < len; j++)
            {
                temp = paths.front();
                paths.pop();
                if (temp.first == to)
                {
                    if (min == -1 || min > temp.second)
                    {
                        min = temp.second;
                    }
                }
                auto edges_to = GetNextVertices(temp.first);
                for (auto edge : edges_to)
                {
                    edge.second += temp.second;
                    if (shortest_paths[edge.first] == - 1 || shortest_paths[edge.first] > edge.second)
                    {
                        shortest_paths[edge.first] = edge.second;
                    }
                    //paths.push(edge);
                }
            }
            for (int i = 0; i < vertices_count_; i++)
            {
                if (shortest_paths[i] != -1)
                {
                    paths.emplace(i, shortest_paths[i]);
                    shortest_paths[i] = -1;
                }
            }
        }
        return min;
    }
private:
    std::vector<std::vector<std::pair<int, int>>> graph_;
    int vertices_count_;
};

int main()
{
    int total_vertices_count;
    int road_amount, k, start, finish;
    std::cin >> total_vertices_count >> road_amount >> k >> start >> finish;
    ListGraph graph(total_vertices_count);
    for (int i = 0; i < road_amount; i++)
    {
        int to, from, weight;
        std::cin >> from >> to >> weight;
        graph.AddEdge(from - 1, to - 1, weight);
    }
    std::cout << graph.findShortestPathShorterThanK(k, start - 1, finish - 1);
    return 0;
}
