/*Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции. 
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
5_1. Реклама.
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
*/
#include <iostream>

class Visit
{
    public:
        int start, end;
        Visit(int start, int end)
        {
            this->start = start;
            this->end = end;
        }
        Visit(Visit &a)
        {
            start = a.start;
            end = a.end;
        }
        Visit(){}
};
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
int CompareVisits(Visit a, Visit b)
{
    //сравниваем время(приход >> уход)
    if (a.start > b.start)
        return 1;
    if (a.start < b.start)
        return -1;
    if (a.end < b.end)
        return -1;
    if (a.end > b.end)
        return 1;
    return 0;
}
int CountAds(Visit *visits, int len, int (*cmp)(Visit, Visit))
{
    int cur = 0;
    MergeSort(visits, len, cmp);
    //массив максимально наложенных визитов(всегда меньше либо равен начальному)
    Visit *res = new Visit[len];
    int ans = 0;
    res[0].start = visits[0].start;
    res[0].end = visits[0].end;
    for (int i = 0; i < len; i++)
    {
        //начало только растет(ибо упорядочено)
        //так что если начало следующего меньше текущего конца, то сужаем текущий
        if (visits[i].start < res[cur].end)
        {
            res[cur].start = visits[i].start;
            //берем меньший конец
            res[cur].end = std::max(res[cur].end, visits[i].end, compare);
        }
        else
        {
            //если совпали начало текущего и конец предыдущего нужно на 1 меньше рекламу 
            if (cur > 0 && res[cur].start == res[cur - 1].end)
                ans--;
            //если в текущий отрезок нельзя добавить новый визит, делаем новый
            cur++;
            res[cur].start = visits[i].start;
            res[cur].end = visits[i].end;
        }
    }
    //дополнительный прогон для последнего
    if (cur > 0 && res[cur].start == res[cur - 1].end)
        ans--;
    delete[] res;
    // + 1 т.к. cur был индексом
    ans += (cur + 1) * 2;
    return ans;
}
int main()
{
    int n = 0;
    int res = 0;
    std::cin >> n;
    Visit *arr = new Visit[n];
    for (int i = 0; i < n; i++)
        std::cin >> arr[i].start >> arr[i].end;
    res = CountAds(arr, n, &CompareVisits);
    for (int i = 0; i < n; i++)
        std::cout << arr[i].start << " " << arr[i].end << std::endl;
    std::cout << res;
    delete[] arr;
    return 0;
}
/*
5
1 2
2 4
3 20
6 15
7 19
*/