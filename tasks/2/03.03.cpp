#include <cassert>
#include <iostream>

class List
{
    struct Node
    {
        int value;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    ~List()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    [[nodiscard]] bool empty() const
    {
        return head == nullptr;
    }

    void show() const
    {
        for (auto node = head; node != nullptr; node = node->next)
        {
            std::cout << node->value << (node->next ? " " : "");
        }
        std::cout << std::endl;
    }

    void push_front(int value)
    {
        auto node = new Node{ value, head };
        head = node;
        if (!tail)
        {
            tail = node;
        }
    }

    void push_back(int value)
    {
        auto node = new Node{ value, nullptr };
        if (tail)
        {
            tail->next = node;
        }
        else
        {
            head = node;
        }
        tail = node;
    }

    void pop_front()
    {
        if (empty()) return;

        auto temp = head;
        head = head->next;

        if (!head)
        {
            tail = nullptr;
        }

        delete temp;
    }

    void pop_back()
    {
        if (empty()) return;

        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            auto current = head;
            while (current->next != tail)
            {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
    }

    [[nodiscard]] int get() const
    {
        if (empty()) return 0;

        auto slow = head;
        auto fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->value;
    }
};

int main()
{
    List list;
    assert(list.empty());

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // List: 10 20 30
    list.show();
    assert(!list.empty());
    assert(list.get() == 20);

    list.push_front(5);
    // List: 5 10 20 30
    list.show();
    assert(list.get() == 20);

    list.push_back(40);
    // List: 5 10 20 30 40
    list.show();
    assert(list.get() == 20);

    list.pop_front();
    // List: 10 20 30 40
    list.show();
    assert(list.get() == 30);

    list.pop_back();
    // List: 10 20 30
    list.show();
    assert(list.get() == 20);

    list.pop_back();
    list.pop_back();
    // List: 10
    list.show();
    assert(list.get() == 10);

    list.pop_front();
    assert(list.empty());

    list.push_front(100);
    list.pop_back();
    assert(list.empty());
}