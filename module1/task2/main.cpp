#include <iostream>
#include <vector>
int find_borders(int &start, int &end, std::vector<int> &A)
{
    start = 0;
    end = 1;
    while (A[start] < A[end])
    {
        start = end;
        end *= 2;
        if (A[end] < A[end - 1] || A[start] > A[start + 1])
            break;
        if (end > A.size() - 1)
        {
            end = A.size() - 1;
            break;
        }
    }
    return 0;
}

int binary_search(int &start, int &end, std::vector<int> &A)
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
    int n, temp;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> temp;
        A.push_back(temp);
    }

    int start, end;
    find_borders(start, end, A);
    int res = binary_search(start, end, A);
    std::cout << res;
    return 0;
}
