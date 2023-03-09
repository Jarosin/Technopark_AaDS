#include <iostream>

//учесть возможность пустоты дека
class Deque
{
    public:
        Deque()
        {
            capacity = 2;
            buf = new int[capacity];
            size = 0;
            start = buf;
            end = buf + 1;
        }
        ~Deque()
        {
            delete[] buf;
        }
        void push_back(int new_el)
        {
            if (size == 0)
            {
                start = buf;
                end = buf + 1;
            }
            if (size + 1 > capacity)
                grow();
            size++;   
            end++; 
            if (end >= buf + capacity)
                end = buf;   
            *end = new_el;
        }
        int pop_back()
        {     
            int res = *end;
            if (isEmpty())
                return -1;
            end--;
            if (end < buf)
                end = buf + capacity - 1;        
            size--;
            return res;
        }
        int pop_front()
        {    
            int res = *start;
            if (isEmpty())
            {
                return -1;
            }      
            start++;
            if (start >= buf + capacity)
                start = buf;      
            size--;   
            return res;
        }
        void push_front(int new_el)
        {
            if (size == 0)
            {
                start = buf;
                end = buf + 1;
            }
            if (size + 1 > capacity)
                grow();
            size++;  
            start--;
            if (start < buf)
                start = buf + capacity - 1; 
            *start = new_el;
        }
        bool isEmpty()
        {
            return !size;
        }
    private:
        int *buf;
        int capacity;
        int size;
        int *start;
        int *end;
        int grow()
        {
            int *new_buf = new int[capacity * 2];
            int *fin = new_buf + size;
            //бежим до конца
            for (auto it = new_buf; it < fin; it++)
            {
                *it = pop_front();
            }
            delete[] buf;
            capacity *= 2;
            buf = new_buf;
            start = new_buf;
            size = fin - new_buf;
            end = new_buf + size + 1;
        }
};
int main()
{
    Deque deq;
    deq.push_front(44);
    deq.push_back(50);
    std::cout << deq.pop_front() << std::endl;
    return 0;
}