#include <iostream>
#include <vector>
int find_borders(int &start, int &end, int *A, int n)
{
    start = 0;
    end = 1;
    while (A[start] < A[end])
    {
        start = end;
        end *= 2;
        if (A[end] < A[end - 1] || A[start] > A[start + 1])
            break;
        if (end > n - 1)
        {
            end = n - 1;
            break;
        }
    }
    return 0;
}

int binary_search(int &start, int &end, int *A)
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
    int n;
    std::cin >> n;
    int *A = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> A[i];
    }

    int start, end;
    find_borders(start, end, A, n);
    int res = binary_search(start, end, A);
    std::cout << res;
    delete[] A;
    return 0;
}
