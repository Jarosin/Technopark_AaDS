// Дан базовый интерфейс для представления ориентированного графа:
// struct IGraph {
// virtual ~IGraph() {}

// Добавление ребра от from к to.
// virtual void AddEdge(int from, int to) = 0;

// virtual int VerticesCount() const  = 0;

// virtual std::vector<int> GetNextVertices(int vertex) const = 0;
// virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
// };

// Необходимо написать несколько реализаций интерфейса:
// ListGraph, хранящий граф в виде массива списков смежности,
// MatrixGraph, хранящий граф в виде матрицы смежности,
// SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
// ArcGraph, хранящий граф в виде одного массива пар {from, to}.
// Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
// Для каждого класса создавайте отдельные h и cpp файлы.
// Число вершин графа задается в конструкторе каждой реализации.
#include <iostream>
#include <vector>
#include <set>
#include <utility>

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

private:
    std::vector<std::vector<int>> graph_;
    int vertices_count_;
};

class MatrixGraph : public IGraph
{
public:
    MatrixGraph(int vertices_count) : vertices_count_(vertices_count)
    {
        graph_.resize(vertices_count);
        for (int i = 0; i < vertices_count_; i++)
        {
            graph_[i].resize(vertices_count_, 0);
        }
    }

    MatrixGraph(const IGraph &igraph)
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
    ~MatrixGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override
    {
        graph_[from][to] += 1;
    }

    virtual int VerticesCount() const override
    {
        return vertices_count_;
    }

    virtual std::vector<int> GetNextVertices(int vertex) const override
    {
        std::vector<int> res;
        for (int i = 0; i < vertices_count_; i++)
        {
            if (graph_[vertex][i])
                for (int j = 0; j < graph_[vertex][i]; j++) // добавляем по количеству
                    res.push_back(i);                       // добавляем по номеру вершины
        }
        return res;
    }

    virtual std::vector<int> GetPrevVertices(int vertex) const override
    {
        std::vector<int> res;
        for (int i = 0; i < graph_.size(); i++)
        {
            if (graph_[i][vertex])
                for (int j = 0; j < graph_[vertex][i]; j++)
                    res.push_back(i);
        }
        return res;
    }

private:
    std::vector<std::vector<int>> graph_;
    int vertices_count_;
};

class SetGraph : public IGraph
{
public:
    SetGraph(int vertices_count) : vertices_count_(vertices_count)
    {
        graph_.resize(vertices_count);
    }

    SetGraph(const IGraph &igraph)
    {
        int len = igraph.VerticesCount();
        graph_.resize(len);
        vertices_count_ = len;
        for (int i = 0; i < len; i++)
        {
            std::vector<int> edges = igraph.GetNextVertices(i);
            for (auto &elm : edges)
            {
                graph_[i].insert(elm);
            }
        }
    }
    ~SetGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override
    {
        graph_[from].insert(to);
    }

    virtual int VerticesCount() const override
    {
        return vertices_count_;
    }

    virtual std::vector<int> GetNextVertices(int vertex) const override
    {
        std::vector<int> res;
        for (auto &it : graph_[vertex])
            res.push_back(it);
        return res;
    }

    virtual std::vector<int> GetPrevVertices(int vertex) const override
    {
        std::vector<int> res;
        for (int i = 0; i < vertices_count_; i++)
        {
            for (auto &edge : graph_[i])
                if (edge == vertex)
                    res.push_back(i);
        }
        return res;
    }

private:
    std::vector<std::set<int>> graph_;
    int vertices_count_;
};

class ArcGraph : public IGraph
{
public:
    ArcGraph(int vertices_count) : vertices_count_(vertices_count)
    {
        graph_.resize(vertices_count);
    }

    ArcGraph(const IGraph &igraph)
    {
        int len = igraph.VerticesCount();
        vertices_count_ = len;
        for (int i = 0; i < len; i++)
        {
            std::vector<int> edges = igraph.GetNextVertices(i);
            for (auto &elm : edges)
            {
                std::pair<int, int> edge(i, elm);
                graph_.push_back(edge);
            }
        }
    }
    ~ArcGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override
    {
        std::pair<int, int> edge(from, to);
        graph_.push_back(edge);
    }

    virtual int VerticesCount() const override
    {
        return vertices_count_;
    }

    virtual std::vector<int> GetNextVertices(int vertex) const override
    {
        std::vector<int> res;
        for (auto &it : graph_)
        {
            if (it.first == vertex)
                res.push_back(it.second);
        }
        return res;
    }
    virtual std::vector<int> GetPrevVertices(int vertex) const override
    {
        std::vector<int> res;
        for (auto &it : graph_)
        {
            if (it.second == vertex)
                res.push_back(it.first);
        }
        return res;
    }

private:
    std::vector<std::pair<int, int> > graph_;
    int vertices_count_;
};


bool areEquelGraphs(const IGraph& l, const IGraph& r)
{
    if (l.VerticesCount() != r.VerticesCount())
        return false;

    // проверка ребер из вершины
    for (int i = 0; i < l.VerticesCount(); i++)
    {
        std::vector<int> left_edges = l.GetNextVertices(i);
        std::vector<int> right_edges = r.GetNextVertices(i);
        bool flag = false;
        for (auto &left_edge : left_edges) // может быть нарушен порядок, нужно это учесть
        {
            flag = false;
            for (auto &right_edge : right_edges)
            {
                if (right_edge == left_edge)
                {
                    flag = true;
                    right_edge = -1; // позволяет проверить количество ребер с одинаковым началом и концом
                    break;
                }
            }
            if (!flag)
                return false;
        }
    }

    // проверка ребер в вершину
    for (int i = 0; i < l.VerticesCount(); i++)
    {
        std::vector<int> left_edges = l.GetPrevVertices(i);
        std::vector<int> right_edges = r.GetPrevVertices(i);
        bool flag = false;
        for (auto &left_edge : left_edges) // может быть нарушен порядок, нужно это учесть
        {
            flag = false;
            for (auto &right_edge : right_edges)
            {
                if (right_edge == left_edge)
                {
                    flag = true;
                    right_edge = -1; // позволяет проверить количество ребер с одинаковым началом и концом
                    break;
                }
            }
            if (!flag)
                return false;
        }
    }
    return true;
}

int main()
{
    return 0;
}
