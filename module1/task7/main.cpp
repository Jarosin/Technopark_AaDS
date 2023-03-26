/*7_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6. Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/
#include <iostream>
int find_bit(int n, int k)
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
        for (; i < end && !find_bit(*i, bit); i++) {}
        for (; j > start && find_bit(*j, bit); j--) {}
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

int main()
{
    int n = 0;
    std::cin >> n;
    unsigned long long *arr = new unsigned long long[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];    
    }
    int bit_number = 63;
    BinaryQuickSort(arr, arr + n - 1, bit_number);
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    return 0;
}