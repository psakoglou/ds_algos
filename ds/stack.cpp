#include <cstring>
#include <iostream>

class Stack
{
private:
    int *data = nullptr;
    int m_size = 10;
    int m_top = 0;

private:
    void resize()
    {
        int *oldData = data;
        int oldSize = m_size;
        m_size *= 2;
        data = new int[m_size];
        std::memmove(oldData, data, oldSize);
        delete[] oldData;
    }

public:
    Stack()
    {
        data = new int[m_size];
    }

    ~Stack()
    {
        if (data != nullptr)
        {
            delete[] data;
        }
    }

    void push(int n)
    {
        if (m_top >= m_size)
        {
            resize();
        }
        data[m_top++] = n;
    }

    void pop()
    {
        if (m_top <= 0)
        {
            return;
        }
        m_top--;
    }

    int top()
    {
        if (m_top == 0)
        {
            return data[m_top - 1];
        }
        return data[m_top - 1];
    }

    int size()
    {
        return m_top;
    }
};

int main()
{
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);

    std::cout << s.top() << std::endl;
    std::cout << s.size() << std::endl;

    s.pop();

    std::cout << s.top() << std::endl;
    std::cout << s.size() << std::endl;

    return 0;
}