/*4.1 Слияние массивов.
Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
Требования: время работы O(N * logK). Ограничение на размер кучи O(K)..
Формат входных данных: Сначала вводится количество массивов K. Затем по очереди размер каждого массива и элементы массива. Каждый массив упорядочен по возрастанию.
Формат выходных данных: Итоговый отсортированный массив.*/
#include <iostream>

template <typename T>
struct DefaultComparator {
    bool operator()(const T& l, const T& r) const {
        return l < r;
    }
};
template <typename T, typename Comparator = DefaultComparator<T>>
class Heap
{
    public:
        Heap(int k, Comparator cmp = Comparator())
        {
            this->cmp = cmp;
            len = 0;
            buf = new T[k];
            capacity = k;
        };
        ~Heap() 
        {
            delete[] buf;
        };
        void push(T element)
        {
            Append(element);
            siftUp(len - 1);
        }
        void pop()
        {
            len--;
            buf[0] = buf[len];
            siftDown(0);
        }
        const T& top()
        {
            return buf[0];
        }
    private:
        T *buf;
        int len;
        int capacity;
        Comparator cmp;
        void grow()
        {
            T *new_buf = new T[capacity * 2];
            T *fin = new_buf + len;
            for (auto it = new_buf; it < fin; it++)
            {
                *it = top();
                pop();
            }
            delete[] buf;
            capacity *= 2;
            buf = new_buf;
        }
        void siftDown(int i)
        {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < len && !cmp(buf[left], buf[largest]))
                largest = left;
            if (right < len && !cmp(buf[right], buf[largest]))
                largest = right;
            if (largest != i)
            {
                std::swap(buf[largest], buf[i]);
                siftDown(largest);
            }
        }
        void siftUp(int i)
        {
            if (i == 0)
                return;
            int parent = (i - 1) / 2;
            if (cmp(buf[parent], buf[i]))
            {
                std::swap(buf[i], buf[parent]);
                siftUp(parent);
            }
        }
        void Append(T new_el)
        {
            if (len > capacity)
                grow();
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
        bool operator<(const Capsule& r) const
        {
            return data < r.data;
        }
};
template <typename T>
int CompareCapsules(Capsule<T> a, Capsule<T> b)
{
    return a.data - b.data;
}

template <typename T>
int MergeArrays(T **matrix, int *lens, int k, int n, int *res)
{
    Heap<Capsule<T>> solver(k);
    for (int i = 0; i < k; i++)
    { 
        if (lens[i] > 0)
        {
            lens[i]--;
            Capsule<T> temp(matrix[i][lens[i]], i);
            solver.push(temp);
        }
    }
    int cur = n - 1;
    for (int i = 0; i < n; i++)
    {
        Capsule<T> temp = solver.top();
        solver.pop();
        res[cur] = temp.data;
        cur--;
        int arr_number = temp.arr_number;
        if (lens[arr_number] > 0)
        {
            lens[arr_number]--;
            Capsule<T> temp(matrix[arr_number][lens[arr_number]], arr_number);
            solver.push(temp);
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
    int **matrix;
    int rows;
    int *lengths;
    int n = 0;
    std::cin >> rows;
    matrix = new int*[rows];
    lengths = new int[rows];
    for (int i = 0; i < rows; i++)
    {
        int columns = 0;
        std::cin >> columns; 
        matrix[i] = new int[columns];
        lengths[i] = columns;
        n += columns;
        for (int j = 0; j < columns; j++)
        {
            std::cin >> matrix[i][j];
        }
    }
    int *res = new int[n];  
    MergeArrays<int>(matrix, lengths, rows, n, res);
    for (int i = 0; i < n; i++)
        std::cout << res[i] << " ";
    delete[] res;
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] lengths;
    return 0;
}