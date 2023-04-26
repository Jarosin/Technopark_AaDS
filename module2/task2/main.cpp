/*
Задача 2. Порядок обхода (4 балла)
Обязательная задача
Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
2_1. Выведите элементы в порядке in-order (слева направо).

in
out

3
2 1 3
1 2 3

3
1 2 3
1 2 3

3
3 1 2
1 2 3

*/

#include <iostream>
#include <stack>
#include <memory>
template <typename T>
struct TreeNode
{
    T data_;
    std::shared_ptr<TreeNode<T>> left_;
    std::shared_ptr<TreeNode<T>> right_;
    TreeNode(T data) : left_(nullptr), right_(nullptr), data_(data) {}
    bool operator<(const T &data)
    {
        return data_ < data;
    }
};
template <typename T>
class DefaultComparator
{
public:
    bool operator()(const T &left, const T &right) const
    {
        return left < right;
    }
};
template <typename T, typename Comparator = DefaultComparator<T>>
class BinaryTree
{
public:
    using TreeNodePtr = std::shared_ptr<TreeNode<T>>;
    BinaryTree(Comparator cmp = Comparator()) : comparator_(cmp), root_(nullptr){};
    void Insert(T data)
    {
        if (!root_)
        {
            root_ = std::make_shared<TreeNode<T>>(data);
            return;
        }
        TreeNodePtr cur = root_;
        while (true)
        {
            if (!comparator_(data, cur->data_))
            {
                if (!cur->right_)
                {
                    cur->right_ = std::make_shared<TreeNode<T>>(data);
                    break;
                }
                else
                    cur = cur->right_;
            }
            else
            {
                if (!cur->left_)
                {
                    cur->left_ = std::make_shared<TreeNode<T>>(data);
                    break;
                }
                else
                    cur = cur->left_;
            }
        }
    }
    void PrintInOrder()
    {
        if (!root_)
            return;
        TreeNodePtr cur = root_;
        std::stack<TreeNodePtr> stack;
        while (true)
        {
            while (cur)
            {
                stack.push(cur);
                cur = cur->left_;
            }
            while (!cur)
            {
                if (stack.empty())
                    return;
                cur = stack.top();
                stack.pop();
                std::cout << cur->data_ << " ";
                cur = cur->right_;
            }
        }
    }

private:
    TreeNodePtr root_;
    Comparator comparator_;
};

#include <iostream>

int main()
{
    BinaryTree<long> tree;
    size_t len = 0;
    std::cin >> len;
    long cur;
    for (size_t i = 0; i < len; i++)
    {
        std::cin >> cur;
        tree.Insert(cur);
    }
    tree.PrintInOrder();
    return 0;
}
