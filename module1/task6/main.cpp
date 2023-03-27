/*
Дано множество целых чисел из [0..10^9] размера n. 
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль

Требования: к дополнительной памяти: O(n). 
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition. 
Рекурсия запрещена. 
Решение должно поддерживать передачу функции сравнения снаружи.


Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
template<typename T>
struct DefaultComparator
{
    bool operator()(const T& l, const T& r)
    {
        return l < r;
    }
};
template<typename T, typename Comparator = DefaultComparator<T>>
int Partition(T *arr, int l, int r, Comparator cmp = Comparator())
{
    int pivot_idx = std::rand() % (r - l) + l;
    std::swap(arr[pivot_idx], arr[r]);
    int i = l;
    int j = r;
    while (i < j)
    {
        for (; cmp(arr[i], arr[r]); i++) continue;
        for (; !cmp(arr[j], arr[r]) && j > l; j--) continue;
        if (i < j)
        {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    std::swap(arr[i], arr[r]);
    return i;
}
template<typename T, typename Comparator = DefaultComparator<T>>
void k_stat(T *arr, int size, int k, Comparator cmp = Comparator())
{
    int l = 0;
    int r = size - 1;
    while (l < r) {
        int m = Partition(arr, l, r);
        if (m == k)
        {
            return;
        }
        else if (m < k)
        {
            l = m + 1;
        }
        else //m > k
        {
            r = m;
        }
    }
}
int main()
{
    int n = 0;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    int k = static_cast<int>(floor(0.1 * n));
    k_stat<int>(arr, n, k);
    std::cout << arr[k] << std::endl;

    k = static_cast<int>(floor(0.5 * n));
    k_stat<int>(arr, n, k);
    std::cout << arr[k] << std::endl;

    k = static_cast<int>(floor(0.9 * n));
    k_stat<int>(arr, n, k);
    std::cout << arr[k] << std::endl;
    
    delete[] arr;
    return 0;
}