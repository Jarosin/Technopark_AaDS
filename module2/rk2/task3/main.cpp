#include <iostream>
#include <string>
#include <unordered_set>

constexpr auto FAIL = "FAIL";
constexpr auto OK = "OK";

struct Node
{
    std::string product_name;
    int color;
    int size;
    size_t Hash() const
    {
        auto name_hash = std::hash<std::string>{}(product_name);
        auto color_hash = std::hash<int>{}(color);
        auto size_hash = std::hash<int>{}(size);
        while(color_hash > 0)
        {
            name_hash *= 10;
            name_hash += color_hash % 10;
            color_hash /= 10;
        }
        while(size_hash > 0)
        {
            name_hash *= 10;
            name_hash += size_hash % 10;
            size_hash /= 10;
        }
        return name_hash;
    }
    bool operator==(const Node& other) const
    {
        return Hash() == other.Hash();
    }
    Node(std::string other_product_name, int other_color, int other_size) : product_name(other_product_name), color(other_color), size(other_size) {}
};

namespace std
{
    template <>
    struct hash<Node>
    {
        size_t operator()(const Node &node) const
        {
            return node.Hash();
        }
    };
}




int main()
{
    std::unordered_set<Node> product_set;
    char command;
    std::string product_name;
    int color, size;
    while (std::cin >> command >> product_name >> color >> size)
    {
        Node temp(product_name, color, size);
        switch(command)
        {
            case '+':
                if (!product_set.count(temp))
                {
                    std::cout << OK << std::endl;
                    product_set.insert(temp);
                }
                else
                {
                    std::cout << FAIL << std::endl;
                }
                break;
            case '?':
                if (!product_set.count(temp))
                {
                    std::cout << FAIL << std::endl;
                }
                else
                    std::cout << OK << std::endl;
                break;

            case '-':
                if (!product_set.count(temp))
                {
                    std::cout << FAIL << std::endl;
                }
                else
                {
                    std::cout << OK << std::endl;
                    product_set.erase(temp);
                }
                break;
            default:
                break;
        }
    }
    return 0;
}
