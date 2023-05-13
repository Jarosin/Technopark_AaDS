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
#include "IGraph.h"
#include "ArcGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"


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

bool test_graphs()
{
    ListGraph list_graph(5);
    list_graph.AddEdge(0, 1);
    list_graph.AddEdge(1, 2);
    list_graph.AddEdge(2, 3);
    list_graph.AddEdge(3, 4);
    list_graph.AddEdge(4, 2);
    MatrixGraph matrix_graph(list_graph);
    SetGraph set_graph(list_graph);
    ArcGraph arc_graph(list_graph);
    std::vector<IGraph *> graphs;
    graphs.push_back(&list_graph);
    graphs.push_back(&matrix_graph);
    graphs.push_back(&set_graph);
    graphs.push_back(&arc_graph);
    for (int i = 0; i < graphs.size(); i++)
    {
        for (int j = i + 1; j < graphs.size(); j++)
        {
            if (!areEquelGraphs(*graphs[i], *graphs[j]))
                return false;
        }
    }
    return true;
}

int main()
{
    if (test_graphs())
        std::cout << "OK" << std::endl;
    else
        std::cout << "FAIL" << std::endl;
    return 0;
}
