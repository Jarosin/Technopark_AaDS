/*4.1 Слияние массивов.
Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
Требования: время работы O(N * logK). Ограничение на размер кучи O(K)..
Формат входных данных: Сначала вводится количество массивов K. Затем по очереди размер каждого массива и элементы массива. Каждый массив упорядочен по возрастанию.
Формат выходных данных: Итоговый отсортированный массив.*/
#include <iostream>
//TODO: сделать код безопасным
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
                auto temp = buf[i];
                buf[i] = buf[largest];
                buf[largest] = buf[i];
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
                auto temp = buf[parent];
                buf[parent] = buf[i];
                buf[i] = temp;
                siftUp(parent, cmp);
            }
        }
        void Append(T new_el)
        {
            buf[len] = new_el;
            len++;
        }
};

template <typename T>
class Capsule
{
    public:
        T data;
        int arr_number;
        Capsule(T data, int arr_number)
        {
            this->data = data;
            this->arr_number = arr_number;
        }
        Capsule(){};
        ~Capsule(){};
};
template <typename T>
int CompareCapsules(Capsule<T> a, Capsule<T> b)
{
    return a.data - b.data;
}
//два варианта: либо запоминать номер массива с самим элементом(оберкта), либо создать массив, хранящий последний изъятый элемент
//Проблема массива отслеживания - при повторении одного элемента в нескольких массивах будут проблемы
template <typename T>
int MergeArrays(T **aa, int *lens, int k, int n, int *res, int (*cmp)(T, T))
{
    Heap<Capsule<T>> solver(k);
    for (int i = 0; i < k; i++)
    { 
        if (lens[i] > 0)
        {
            lens[i]--;
            Capsule<T> temp(aa[i][lens[i]], i);
            solver.Insert(temp, &CompareCapsules);
        }
    }
    int cur = n - 1;
    for (int i = 0; i < n; i++)
    {
        Capsule<T> temp = solver.ExtractMax(&CompareCapsules);
        res[cur] = temp.data;
        cur--;
        int arr_number = temp.arr_number;
        if (lens[arr_number] > 0)
        {
            lens[arr_number]--;
            Capsule<T> temp(aa[arr_number][lens[arr_number]], arr_number);
            solver.Insert(temp, &CompareCapsules);
        }
    }
    return 0;
}

int compare(int a, int b)
{
    return a - b;
}
int main()
{
    int **aa;
    int rows;
    int *lengths;
    int n = 0;
    std::cin >> rows;
    aa = new int*[rows];
    lengths = new int[rows];
    for (int i = 0; i < rows; i++)
    {
        int columns = 0;
        std::cin >> columns; 
        aa[i] = new int[columns];
        lengths[i] = columns;
        n += columns;
        for (int j = 0; j < columns; j++)
        {
            std::cin >> aa[i][j];
        }
    }
    int *res = new int[n];  
    MergeArrays<int>(aa, lengths, rows, n, res, &compare);
    for (int i = 0; i < n; i++)
        std::cout << res[i] << " ";
    delete[] res;
    for (int i = 0; i < rows; i++)
    {
        delete[] aa[i];
    }
    delete[] aa;
    delete[] lengths;
    return 0;
}
/*3
2
1 2
1
5
0*/