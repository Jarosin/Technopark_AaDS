/*
ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!

Пара слов называется стековой анаграмой, если одно слово можно получить из другого, проведя последовательность стековых операций с его буквами (взять очередную букву исходного слова и поместить ее в стек; взять букву из стека и добавить ее в конец выходного слова). Для заданной пары слов требуется определить, можно ли выполнить последовательность стековых операций, переводящую первое слово во второе. Все буквы в слове различные. Длина анаграммы ≤ 10000.

Формат ввода
Пара слов, являющихся анаграммой.

Формат вывода
YES, если последовательность стековых операций существует и NO в противном случае.

Ввод
STOL SLOT 
Вывод:
YES

Ввод
ABC CAB
Вывод:
NO
*/
#include <iostream>
#include <string>
template<typename T>
class Stack
{
    public:
    Stack(int len)
    {
        buf_ = new T[len];
        end_ = buf_ + len;
        cur_ = buf_;
    }
    void push(T item)
    {
        if (cur_ > end_)
            return;
        *cur_ = item;
        cur_++;
    }
    T pop()
    {
        cur_--;
        T res = *cur_;
        return res;
    }
    T top()
    {
        T res;
        if (empty())
            return res;
        return *(cur_ - 1);
    }
    bool empty()
    {
        return cur_ == buf_;
    }
    ~Stack()
    {
        delete[] buf_;
    }
    private:
    T *end_;
    T *buf_;
    T *cur_;
};

int stack_anagram(std::string first, std::string second)
{
    Stack<char> st(first.size());
    std::string res = "";
    int j = 0, i = 0;
    while (i < second.size())
    {
        if (!st.empty() && second[i] == st.top())
        {
            res += st.pop();
            i++;
        }
        else if (j < first.size())
        {
            st.push(first[j]);
            j++;
        }
        else if (!st.empty())
        {
            res = res + st.pop();
        }
        else
            break;
    }
    return res == second;
}
int main()
{
    std::string first;
    std::string second;
    std::cin >> first >> second;
    std::string ans = stack_anagram(first, second) ? "YES" : "NO";
    std::cout << ans;
    return 0;
}
