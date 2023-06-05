#include <stack>
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

    int findEdgeAmount()
    {
        int amount = 0;
        for (auto &paths : graph_)
        {
            for (auto &elem : paths)
            {
                amount++;
            }
        }
        return amount;
    }

    bool isTree()
    {
        std::vector<bool> visited_vertices(vertices_count_, false);
        std::stack<int> vertices_stack;
        vertices_stack.push(0);
        if (!((findEdgeAmount() / 2) == vertices_count_ - 1))
            return false;
        while (!vertices_stack.empty())
        {
            if (!dfs(vertices_stack, visited_vertices))
                return false;
        }
        for (int i = 0; i < vertices_count_; i++)
        {
            if (!visited_vertices[i])
                return false;
        }
        return true;
    }

    bool dfs(std::stack<int> &vertices_stack, std::vector<bool> &visited_vertices)
    {
        bool flag = false;
        int vertice = vertices_stack.top();
        vertices_stack.pop();
        // возможно здесь стоило бы проверку сделать
        visited_vertices[vertice] = true;
        for (auto &path : graph_[vertice])
        {
            if (visited_vertices[path])
            {
                if (!flag)
                {
                    flag = true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                vertices_stack.push(path);
            }
        }
        return true;
    }

private:
    std::vector<std::vector<int>> graph_;
    int vertices_count_;
};

int main()
{
    int n, m;
    std::cin >> n >> m;
    ListGraph graph(n);
    for (int i = 0; i < m; i++)
    {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }
    std::cout << (graph.isTree() ? 1 : 0);
    return 0;
}
