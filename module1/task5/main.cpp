/*Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции. 
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
5_1. Реклама.
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
*/
#include <iostream>
template <typename T>
class Heap
{
    public:
        Heap(int k) 
        {
            len = 0;
            buf = new T[k];
        };
        ~Heap() 
        {
            delete[] buf;
        };
        void Insert(T element, int (*cmp)(T, T))
        {
            Append(element);
            siftUp(len - 1, cmp);
        }
        T ExtractMax(int (*cmp)(T, T))
        {
            len--;
            T max = buf[0];
            buf[0] = buf[len];
            siftDown(0, cmp);
            return max;
        }
        T PeekMax()
        {
            return buf[0];
        }
    private:
        T *buf;
        int len;
        void siftDown(int i, int (*cmp)(T, T))
        {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < len && cmp(buf[left], buf[largest]) > 0)
                largest = left;
            if (right < len && cmp(buf[right], buf[largest]) > 0)
                largest = right;
            if (largest != i)
            {
                std::swap(buf[largest], buf[i]);
                siftDown(largest, cmp);
            }
        }
        void siftUp(int i, int (*cmp)(T, T))
        {
            if (i == 0)
                return;
            int parent = (i - 1) / 2;
            if (cmp(buf[parent], buf[i]) < 0)
            {
                std::swap(buf[i], buf[parent]);
                siftUp(parent, cmp);
            }
        }
        void Append(T new_el)
        {
            buf[len] = new_el;
            len++;
        }
};
int main()
{
    return 0;
}