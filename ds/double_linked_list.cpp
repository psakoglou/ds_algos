
class DLL
{
private:
    struct Node
    {
        Node *next;
        Node *prev;
    };

    Node *head;
    Node *tail;

public:
    DLL();

    void push_back(Node *n)
    {
        if (head == nullptr)
        {
            head = n;
            tail = head;
            return;
        }
        tail->next = n;
        n = tail;
    }
};

int main()
{

    return 0;
}