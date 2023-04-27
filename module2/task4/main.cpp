#include <iostream>
/*
Требование для всех вариантов Задачи 4
Решение должно поддерживать передачу функции сравнения снаружи.

4_2. Порядковые статистики. Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики задается числом k.
Требования: скорость выполнения запроса - O(log n).
in
out
5
40 0
10 1
4 1
-10 0
50 2
40
40
10
4
50


*/

template <typename T>
class DefaultComparator
{
    public:
        bool operator()(const T& left, const T& right)
        {
            return left < right;
        }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class AvlTree
{
    struct Node
    {
        Node(const T &data)
            : data(data), left(nullptr), right(nullptr), height(1), count(1)
        {
        }

        size_t count;
        T data;
        Node *left;
        Node *right;
        size_t height;
    };

public:
    AvlTree(Comparator comparator = Comparator())
        : root(nullptr), comparator_(comparator)
    {
    }

    ~AvlTree()
    {
        destroyTree(root);
    }

    void Add(const T &data)
    {
        root = addInternal(root, data);
    }

    bool Has(const T &data)
    {
        Node *tmp = root;
        while (tmp)
        {
            if (comparator(data, tmp->data))
                tmp = tmp->left;
            else if (comparator(tmp->data, data))
                tmp = tmp->right;
            else
                return true;
        }
        return false;
    }
    void Delete(const T &data)
    {
        root = deleteInternal(root, data);
    }

    T FindStat(size_t index)
    {
        return InternalFindStat(root, index);
    }

private:

    T InternalFindStat(Node* node, size_t index)
    {
        if (getCount(node->left) == index)
            return node->data;
        if (getCount(node->left) > index)
            return InternalFindStat(node->left, index);
        index = index - getCount(node->left) - 1;
        return InternalFindStat(node->right, index);
    }
    void destroyTree(Node *node)
    {
        if (node)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node *deleteInternal(Node *node, const T &data)
    {
        if (!node)
            return nullptr;
        if (comparator_(node->data, data))
            node->right = deleteInternal(node->right, data);
        else if (comparator_(data, node->data))
            node->left = deleteInternal(node->left, data);
        else
        {
            Node *left = node->left;
            Node *right = node->right;

            delete node;

            if (!right)
                return left;

            Node *min = findAndRemoveMin(right);
            min->left = left;
            return doBalance(min);
        }

        return doBalance(node);
    }

    Node *findMin(Node *node)
    {
        while (node->left)
            node = node->left;
        return node;
    }

    Node *removeMin(Node *node)
    {
        if (!node->left)
            return node->right;
        node->left = removeMin(node->left);
        return doBalance(node);
    }

    Node *findAndRemoveMin(Node *node)
    {
        Node *min = findMin(node);    // возвращает минимальный элемент в дереве
        min->right = removeMin(node); // возвращает дерево, из которого удалили минимальный элемент
        return min;
    }

    Node *addInternal(Node *node, const T &data)
    {
        if (!node)
            return new Node(data);
        if (!comparator_(data, node->data))
            node->right = addInternal(node->right, data);
        else
            node->left = addInternal(node->left, data);

        return doBalance(node);
    }

    size_t getCount(Node *node)
    {
        return node ? node->count : 0;
    }

    size_t getHeight(Node *node)
    {
        return node ? node->height : 0;
    }

    void fixHeight(Node *node)
    {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    void fixCount(Node *node)
    {
        node->count = getCount(node->left) + getCount(node->right) + 1;
    }

    int getBalance(Node *node)
    {
        return getHeight(node->right) - getHeight(node->left);
    }

    Node *rotateLeft(Node *node)
    {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixHeight(node);
        fixCount(node);
        fixHeight(tmp);
        fixCount(tmp);
        return tmp;
    }

    Node *rotateRight(Node *node)
    {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixCount(node);
        fixHeight(tmp);
        fixCount(tmp);
        return tmp;
    }

    Node *doBalance(Node *node)
    {
        fixHeight(node);
        fixCount(node);
        switch (getBalance(node))
        {
        case 2:
        {
            if (getBalance(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        case -2:
        {
            if (getBalance(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        default:
            return node;
        }
    }

    Node *root;
    Comparator comparator_;
};

int main(int argc, const char *argv[])
{
    AvlTree<u_int> tree;
    int num;
    int k;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> num >> k;
        if (num < 0)
        {
            tree.Delete(-num);
            std::cout << tree.FindStat(k) << std::endl;
        }
        else
        {
            tree.Add(num);
            std::cout << tree.FindStat(k) << std::endl;
        }
    }
    return 0;
}
