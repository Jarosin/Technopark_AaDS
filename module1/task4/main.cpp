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
        Heap() 
        {
            capacity = 10;
            len = 0;
            buf = new T[10];
        };
        ~Heap() 
        {
            free(buf);
        };
        void Insert(T element, bool (*cmp)(T, T))
        {
            Append(element);
            siftUp(len - 1);
        }
        T ExtractMax(bool (*cmp)(T, T))
        {
            len--;
            T max = buf[0];
            buf[0] = buf[len];
            siftDown(0);
            return max;
        }
        T PeekMax()
        {
            if (len == 0)
                return
            return buf[0];
        }
    private:
        T *buf;
        int len;
        int capacity;
        void siftDown(int i, int (*cmp)(T, T))
        {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < size && cmp(buf[left], buf[largest]))
                largest = left;
            if (right < size && cmp(buf[right], buf[largest]))
                largest = right;
            if (largest != i)
            {
                auto temp = buf[i];
                buf[i] = buf[largest];
                buf[largest] = buf[i];
                siftDown(largest);
            }
        }
        void siftUp(int i, int (*cmp)(T, T))
        {
            if (i == 0)
                return;
            int parent = (i - 1) / 2;
            if (cmp(buf[parent], buf[i]))
            {
                auto temp = buf[parent];
                buf[parent] = buf[i];
                buf[i] = temp;
                siftUp(parent);
            }
        }
        void grow()
        {
            T new_buf = new T[capacity * 2];
            for (int i = 0; i < len; i++)
            {
                new_buf[i] = buf[i];
            }
            capacity *= 2;
            free(buf);
            buf = new_buf;
        };
        void Append(T new_el)
        {
            if (len >= capacity)
                grow();
            buf[len] = new_el;
            len++;
        }
};

/*template <typename T>
class Capsule
{
    public:
        T data;
        int arr_number;
        Capsule(T &data, int arr_number)
        {
            this->data = data;
            this->arr_number = arr_number;
        }
        ~Capsule(){};
};*/

//два варианта: либо запоминать номер массива с самим элементом(оберкта), либо создать массив, хранящий последний изъятый элемент
//Проблема массива отслеживания - при повторении одного элемента в нескольких массивах будут проблемы
template <typename T>
T* MergeArrays(T **aa, int *lens, int k, int n, int (*cmp)(T, T))
{
    Heap<T> solver;
    T *last_el = new T[k];
    for (int i = 0; i < k; i++)
    { 
        lens[i]--;
        last_el[i] = aa[i][lens[i]];
        solver.Insert(last_el[i]);
    }
    T *res = new T[n];
    for (int i = 0; i < n; i++)
    {
        T max = solver.ExtractMax();
        for (int i = 0; i < k; i++)
        {
            if (last_el[i])
        }
    }
}
int main()
{
    int **aa;
    int rows;
    int *lengths;
    std::cin >> rows;
    aa = new int*[rows];
    lengths = new int[rows];
    for (int i = 0; i < rows; i++)
    {
        int columns = 0;
        std::cin >> columns; 
        aa[i] = new int[columns];
        lengths[i] = columns;
        for (int j = 0; j < columns; j++)
        {
            std::cin >> aa[i][j];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < lengths[i]; j++)
            std::cout << aa[i][j] << " ";
    }

    for (int i = 0; i < rows; i++)
    {
        free(aa[i]);
    }
    free(aa);
    return 0;
}