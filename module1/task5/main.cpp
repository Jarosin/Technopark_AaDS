/*Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции. 
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
5_1. Реклама.
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
*/
#include <iostream>
template<typename T>
int MergeSort(T* arr, int len, int (*cmp)(T, T))
{
    if (len == 1)
        return 0;
    T* middle = arr + len / 2;
    T* start = arr;

    //сортируем половинки
    MergeSort(start, len / 2, cmp);
    MergeSort(middle, len - len / 2, cmp);

    T *res = new T[len];
    //обьединяем половинки
    for (int i = 0; i < len; i++)
    {
        if (cmp(*start, *middle) < 1)
        {
            res[i] = *start;
            start++;
            if (start >= arr + len / 2)
            {
                for (int j = i + 1; j < len; j++, middle++)
                    res[j] = *middle;    
                break;
            }

        }
        else
        {
            res[i] = *middle;
            middle++;
            if (middle >= arr + len)
            {
                for (int j = i + 1; j < len; j++, start++)
                    res[j] = *start;  
                break;
            }

        }
    }
    for (int i = 0; i < len; i++)
        arr[i] = res[i];
    delete[] res;
    return 0;
}
int compare(int a, int b)
{
    return a - b;
}
int main()
{
    int n = 0;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
    MergeSort(arr, n, &compare);
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    } 
    return 0;
}