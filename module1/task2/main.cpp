#include <iostream>
#include <vector>
int find_borders(int &start, int &end, int *A, int n)
{
    start = 0;
    end = 1;
    while (A[end] > A[end - 1])
    {
        start = end;
        end *= 2;
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
    while (A[start] < A[start + 1])
    {
        int middle = (start + end) / 2;
        if (A[middle] > A[middle + 1])
        {
            end = middle;
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
