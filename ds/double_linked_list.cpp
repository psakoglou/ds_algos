
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
};

int main()
{

    return 0;
}