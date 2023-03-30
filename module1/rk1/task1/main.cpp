/*
Дан отсортированный по возрастанию массив попарно различных целых чисел A[0..n-1]. На вход также подается некоторое целое число k. Необходимо вернуть индекс элемента k в массиве A, если он там присутствует, либо вернуть позицию, куда его следовало бы вставить, чтобы массив остался отсортированным.

Требование: сложность O(logN)

Формат ввода
В первой строчке записано число n – размерность массива A. Во второй строчке перечислены элементы массива A. В третьей строчке записано значение k.

Формат вывода
Целое число — позиция k в A.

Ввод
4
1 3 5 6
5
Вывод:
2
*/
#include <iostream>
int BinarySearch(int *arr, int len, int k)
{
    int *start = arr;
    int *end = arr + len - 1;
    while (start < end)
    {
        int *middle = (end - start) / 2 + start;
        if (k == *middle)
            return middle - arr;
        if (k < *middle)
        {
            end = middle - 1;
        }
        else
        {
            start = middle + 1;
        }
    }
    if (k > *start)
        return start - arr + 1;
    return start - arr;
}
int main()
{
    int n = 0;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
    int k = 0;
    std::cin >> k;
    int pos = BinarySearch(arr, n, k);
    std::cout << pos;    
    return 0;
}
