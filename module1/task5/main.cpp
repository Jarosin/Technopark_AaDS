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
        int start, end, ads;
        Visit(int start, int end)
        {
            this->start = start;
            this->end = end;
            ads = 0;
        }
        Visit(Visit &a)
        {
            start = a.start;
            end = a.end;
            ads = a.ads;
        }
        Visit()
        {
            start = 0;
            end = 0;
            ads = 0;
        }
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
    //сортируем по в первую очередь концам, иначе наоборот по началам
    if (a.end < b.end)
        return -1;
    if (a.end > b.end)
        return 1;
    if (a.start > b.start)
        return -1;
    if (a.start < b.start)
        return 1;
    return 0;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
int ShowAd(Visit *visits, int len, int cur, int end)
{
    for (int i = cur; i < len; i++)
    {
        if (visits[i].start <= end)
        {
            visits[i].ads++;
        }
    }
    return 0;
}
int CountAds(Visit *visits, int len, int (*cmp)(Visit, Visit))
{
    int cur = 0;
    MergeSort(visits, len, cmp);
    int ans = 0;
    for (int i = 0; i < len; i++)
    {     
        int cur_ads = visits[i].ads;
        if (cur_ads < 2)
        {
            for (int j = 0; j < 2 - cur_ads; j++)
            {
                //показываем рекламу всем в промежутке текущего, делаем -j т.к. нельзя дважды показывать рекламу в одно время
                ShowAd(visits, len, i, visits[i].end - j);
                ans++;
            }
        }
    }
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
    /*for (int i = 0; i < n; i++)
        std::cout << arr[i].start << " " << arr[i].end << std::endl;*/
    std::cout << res;
    delete[] arr;
    return 0;
}