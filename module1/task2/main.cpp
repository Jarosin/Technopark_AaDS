#include <iostream>
#include <vector>
int find_borders(int &start, int &end, std::vector<int> A)
{
    start = 0;
    end = 1;
    while (A[start] < A[end])
    {
        start = end;
        end *= 2;
        if (end > A.size() - 1)
            end = A.size() - 1;
    }
    return 0;
}

int binary_search(int &start, int &end, std::vector<int> A)
{
    int middle = (start + end) / 2;
    while (start != end)
    {
        if (A[middle] > A[start] && A[middle] > A[end])
            return middle;
        if (A[start] > A[end])
        {
            end = middle - 1;
        }
        else
            start = middle + 1;
    }
    return start;
}

int main()
{
    std::vector<int> A;
    int n;
    std::cin >> n;
    A.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> A[i];
    }

    int start, end;
    find_borders(start, end, A);
    int res = binary_search(start, end, A);
    std::cout << res;
    return 0;
}
