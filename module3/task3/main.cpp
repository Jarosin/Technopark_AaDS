// Задача 3. «Города» (4 балла)
// Обязательная задача
// Требуется отыскать самый выгодный маршрут между городами.
// Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
// Формат входных данных.
// Первая строка содержит число N – количество городов.
// Вторая строка содержит число M - количество дорог.
// Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
// Последняя строка содержит маршрут (откуда и куда нужно доехать).
// Формат выходных данных.
// Вывести длину самого выгодного маршрута.

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <queue>

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
        graph_[to].emplace_back(from, weight);
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
    int FindShortestPathLength(int from, int to)
    {
        std::set<std::pair<int, int>> path_set;
        std::vector<int> total_path_lengths(vertices_count_, INT32_MAX);
        total_path_lengths[from] = 0;
        std::pair<int, int> temp(0, from);
        path_set.insert(temp);
        while (!path_set.empty())
        {
            auto path = *path_set.begin();
            path_set.erase(path);
            auto paths_to = GetNextVertices(path.second);
            for (auto path_to : paths_to)
            {
                path_to.second += total_path_lengths[path.second];
                if (path_to.second < total_path_lengths[path_to.first])
                {
                    temp.second = path_to.first;
                    temp.first = path_to.second;
                    path_set.insert(temp);
                    total_path_lengths[path_to.first] = path_to.second;
                }
            }
        }
        return total_path_lengths[to];
    }

private:
    std::vector<std::vector<std::pair<int, int>>> graph_;
    int vertices_count_;
};

int main()
{
    int total_vertices_count;
    int road_amount;
    std::cin >> total_vertices_count >> road_amount;
    ListGraph graph(total_vertices_count);
    for (int i = 0; i < road_amount; i++)
    {
        int to, from, weight;
        std::cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }
    int from, to;
    std::cin >> from >> to;
    std::cout << graph.FindShortestPathLength(from, to);
    return 0;
}
