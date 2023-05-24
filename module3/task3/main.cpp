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
        std::pair<int, int> way_to(to, weight);
        std::pair<int, int> way_from(from, weight);

        graph_[from].push_back(way_to);
        graph_[to].push_back(way_from);
    }

    virtual int VerticesCount() const override
    {
        return vertices_count_;
    }

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override
    {
        std::vector<std::pair<int, int>> res;
        res.reserve(graph_[vertex].size());
        for (auto &it : graph_[vertex])
        {
            res.push_back(it);
        }
        return res;
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
    int FindShortestPathLength(int from, int to) {
        std::priority_queue<std::pair<int, int>> path_queue;
        std::vector<int> total_path_lengths(vertices_count_, -1);
        std::pair<int, int> temp(from, 0);
        path_queue.push(temp);
        while (!path_queue.empty())
        {
            auto path = path_queue.top();
            path_queue.pop();

            while (!path_queue.empty() && path_queue.top().first == path.first)
            {
                path.second = path_queue.top().second;
                path_queue.pop();
            }

            if (total_path_lengths[path.first] == -1 || path.second < total_path_lengths[path.first])
            {
                total_path_lengths[path.first] = path.second;

                auto paths_to = GetNextVertices(path.first);
                for (auto path_to : paths_to)
                {
                    path_to.second += total_path_lengths[path.first];
                    path_queue.push(path_to);
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
