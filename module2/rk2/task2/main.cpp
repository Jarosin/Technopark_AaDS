#include <iostream>
#include <stack>
#include <algorithm>
template <typename T>
struct TreeNode
{
    T data_;
    TreeNode<T> *left_;
    TreeNode<T> *right_;
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
    using TreeNodePtr = TreeNode<T> *;
    BinaryTree(Comparator cmp = Comparator()) : comparator_(cmp), root_(nullptr){};
    ~BinaryTree()
    {
        TreeNodePtr cur = root_, tmp = nullptr;
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
                if (cur->right_)
                {
                    tmp = cur;
                    cur = cur->right_;
                    tmp->right_ = nullptr;
                    stack.push(tmp);
                }
                else
                {
                    delete cur;
                    cur = nullptr;
                }
            }
        }
    }
    void Insert(T data)
    {
        if (!root_)
        {
            root_ = new TreeNode<T>(data);
            return;
        }
        TreeNodePtr cur = root_;
        while (true)
        {
            if (!comparator_(data, cur->data_))
            {
                if (!cur->right_)
                {
                    cur->right_ = new TreeNode<T>(data);
                    break;
                }
                else
                    cur = cur->right_;
            }
            else
            {
                if (!cur->left_)
                {
                    cur->left_ = new TreeNode<T>(data);
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
    bool isEquel()
    {
        if (!root_)
            return true;
        TreeNodePtr cur = root_;
        T data = root_->data_;
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
                    return true;
                cur = stack.top();
                stack.pop();
                if (data != cur->data_)
                    return false;
                cur = cur->right_;
            }
        }
    }
    int findNodeHeight(TreeNodePtr node)
    {
        if (!node)
            return 0;
        int left_height = findNodeHeight(node->left_);
        int right_height = findNodeHeight(node->right_);
        if (left_height == 0)
        {
            return right_height + 1;
        }
        else if (right_height == 0)
        {
            return left_height + 1;
        }
        return std::min(left_height, right_height) + 1;
    }

    int findHeight()
    {
        return findNodeHeight(root_);
    }

private:
    TreeNodePtr root_;
    Comparator comparator_;
};

#include <iostream>

int main()
{
    BinaryTree<int> tree;
    int cur;
    while (std::cin >> cur)
    {
        tree.Insert(cur);
    }
    std::cout << tree.findHeight();
    return 0;
}
