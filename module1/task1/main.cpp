#include <iostream>

int find_bit(int n, int k)
{
    return (n >> k) & 1;
}

int main()
{
    unsigned long int n;
    int k;
    std::cin >> n >> k;
    std::cout << find_bit(n, k);
    return 0;
}