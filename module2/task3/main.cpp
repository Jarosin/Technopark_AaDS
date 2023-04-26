/*
Задача 3. B-дерево (4 балла)

Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне 0..232 -1

Требования:
B-дерево должно быть реализовано в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.

Формат входных данных
Сначала вводится минимальный порядок дерева t.
Затем вводятся элементы дерева.

Формат выходных данных
Программа должна вывести B-дерево по слоям. Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.


stdin
stdout

2
0 1 2 3 4 5 6 7 8 9


3
1 5 7
0 2 4 6 8 9
4
0 1 2 3 4 5 6 7 8 9


3
0 1 2 4 5 6 7 8 9

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

template <typename T>
class BTree
{
public:
    struct Node
    {
        Node(bool leaf)
            : leaf(leaf)
        {
        }

        ~Node()
        {
            for (Node *child : children)
            {
                delete child;
            }
        }

        bool leaf;
        std::vector<T> keys;
        std::vector<Node *> children;
    };

    BTree(size_t min_degree)
        : t(min_degree), root(nullptr)
    {
    }

    ~BTree()
    {
        if (root)
            delete root;
    }

    void Insert(const T &key)
    {
        if (!root)
            root = new Node(true);

        // здесь и дальше: если при спуске по дереву находим
        // переполненный узел -- сначала разбиваем его, потом спускаемся
        if (isNodeFull(root))
        {
            Node *newRoot = new Node(false);
            newRoot->children.push_back(root);
            root = newRoot;
            splitChild(root, 0);
        }

        // теперь корень точно не переполнен, можем вызвать insertNonFull
        insertNonFull(root, key);
    }

    void debugPrint()
    {
        debugPrintInternal(root, 0);
    }

    void PrintPerLayer()
    {
        std::queue<Node *> print_queue, temp;
        print_queue.push(root);
        while (true)
        {
            while (!print_queue.empty())
            {
                Node *cur = print_queue.front();
                print_queue.pop();
                if (!cur->leaf)
                {
                    for (auto& child : cur->children)
                        temp.push(child);
                }
                for (const auto& key : cur->keys)
                {
                    std::cout << key << " ";
                }
            }
            std::cout << std::endl;
            while (!temp.empty())
            {
                print_queue.push(temp.front());
                temp.pop();
            }
            if (print_queue.empty())
                break;
        }
    }
private:
    void debugPrintInternal(Node *node, int indent)
    {
        std::cout << std::string(indent, ' ');
        std::cout << "keys: [";
        for (auto it = node->keys.begin(); it != node->keys.end(); it++)
        {
            std::cout << (*it);
            if (it + 1 != node->keys.end())
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;

        for (auto child : node->children)
        {
            debugPrintInternal(child, indent + 4);
        }
    }

    bool isNodeFull(Node *node)
    {
        return node->keys.size() == 2 * t - 1;
    }

    // разбить переполненного потомка index узла node
    void splitChild(Node *node, size_t index)
    {
        Node *child = node->children[index];
        Node *right = new Node(child->leaf);
        auto keys_amount = child->keys.size();
        for (int i = 0; i < keys_amount / 2; i++)
        {
            right->keys.push_back(child->keys.back());
            child->keys.pop_back();
            if (!child->children.empty())
            {
                if (child->children.back()->keys.front() >= right->keys.back())
                {
                    right->children.push_back(child->children.back());
                    child->children.pop_back();
                }
            }
        }
        //если можем перевесить дополнительную из серединки - перевешиваем
        if (!child->children.empty())
        {
            if (child->children.back()->keys.front() < right->keys.back() && child->children.back()->keys.front() > child->keys.back())
            {
                right->children.push_back(child->children.back());
                child->children.pop_back();
            }
        }
        std::reverse(right->keys.begin(), right->keys.end());
        std::reverse(right->children.begin(), right->children.end());
        node->children.insert(node->children.begin() + index + 1, right);
        node->keys.insert(node->keys.begin() + index, child->keys.back());
        child->keys.pop_back();
    }

    // вставить ключ key в гарантированно не переполненную ноду node
    void insertNonFull(Node *node, const T &key)
    {
        int pos = node->keys.size() - 1;

        // гарантированно не перепеполненный лист -- запишем новый ключ в него
        if (node->leaf)
        {
            // расширили вектор ключей для вставки нового
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && key < node->keys[pos])
            {
                // обходим ключи справа налево, сдвигая вправо на 1
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            // вставляем новый ключ на освобожденное в цикле место
            node->keys[pos + 1] = key;
        }
        // не лист, значит есть потомки, пишем в один из них
        else
        {
            // ищем позицию потомка, в которого добавим ключ
            while (pos >= 0 && key < node->keys[pos])
            {
                pos--;
            }

            // если потомок и так полон, надо его сначала разбить
            if (isNodeFull(node->children[pos + 1]))
            {
                splitChild(node, pos + 1);
                // после разбиения потомка в текущий узел из него поднялся ключ
                // надо сравниться и с ним
                if (key > node->keys[pos + 1])
                    pos++;
            }
            insertNonFull(node->children[pos + 1], key);
        }
    }

    size_t t;
    Node *root;
    friend void test1();
};

void test1()
{
    BTree<char> tree(3);

    tree.root = new BTree<char>::Node(false);
    tree.root->keys = {'G', 'M', 'P', 'X'};

    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'A', 'C', 'D', 'E'};
        tree.root->children.push_back(child);
    }

    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'J', 'K'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'N', 'O'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'R', 'S', 'T', 'U', 'V'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'Y', 'Z'};
        tree.root->children.push_back(child);
    }

    std::cout << "Initial tree:" << std::endl;
    tree.debugPrint();
    std::cout << std::endl;

    std::string insertKeys = "BQLF";
    // посимвольно добавляем в дерево ключи
    for (auto c : insertKeys)
    {
        tree.Insert(c);
        std::cout << "After inserting " << c << ":" << std::endl;
        tree.debugPrint();
        std::cout << std::endl;
    }
}

int main(int argc, const char *argv[])
{
    //test1();
    size_t degree = 0;
    std::cin >> degree;
    BTree<unsigned long> tree(degree);
    unsigned long new_key;
    while (std::cin >> new_key)
    {
        tree.Insert(new_key);
    }
    tree.PrintPerLayer();
    return 0;
}
