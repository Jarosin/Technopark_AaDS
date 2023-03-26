/*7_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6. Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/
#include <iostream>
#include <cassert>
int find_bit(unsigned long long n, int k)
{
    return (n >> k) & 1;
}
int BinaryQuickSort(unsigned long long *start, unsigned long long *end, int bit)
{
    if (bit < 0)
        return 0;
    unsigned long long *i = start;
    unsigned long long *j = end;
    while (i < j)
    {
        for (; i < end && !find_bit(*i, bit); i++) continue;
        for (; j > start && find_bit(*j, bit); j--) continue;
        if (i < j) {
            std::swap(*i, *j);
        }
    }
    if (j > start) 
        BinaryQuickSort(start, j, bit - 1);
    if (i < end)
        BinaryQuickSort(i, end, bit - 1);
    return 0;
}
template <typename T>
int check_sorted(T *arr, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            std::cout << "Didnt sort properly" << std::endl;
            return 1;
        }
    }
    std::cout << "It's ok" << std::endl;
    return 0;
}

int test()
{
    int bit_count = 63;
    int rc = 0;

    unsigned long long arr1[] = {1, 2, 3, 4};
    int len = 4;
    BinaryQuickSort(arr1, arr1 + len - 1, bit_count);
    if (!rc)
        rc = check_sorted(arr1, len);

    len = 100000;
    unsigned long long *arr2 = new unsigned long long[len];
    for (int i = 0; i < len; i++)
    {
        arr2[len - i - 1] = i;
    }
    BinaryQuickSort(arr2, arr2 + len - 1, bit_count);
    if (!rc)
        rc = check_sorted(arr2, len);
    delete[] arr2;
    
    len = 64;
    arr2 = new unsigned long long[len];
    unsigned long long a = 1;
    for (int i = 0; i < len; i++)
    {
        arr2[len - i - 1] = a;
        std::cout << a << " ";
        a *= 2;
    }
    BinaryQuickSort(arr2, arr2 + len - 1, bit_count);
    if (!rc)
        rc = check_sorted(arr2, len);
    delete[] arr2;

    return rc;
}

int main()
{   
    //assert(!test());
    int n = 0;
    std::cin >> n;
    unsigned long long max = 0;
    unsigned long long *arr = new unsigned long long[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
        if (arr[i] > max)
            max = arr[i];
    }  
    int bit_number = 0;
    for (int i = 0; i < 63; i++)
    {
        if ((max >> i) & 1)
            bit_number = i;   
    }
    BinaryQuickSort(arr, arr + n - 1, bit_number);
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    delete[] arr;
    return 0;
}