#pragma once
// TODO: Complete the DoubleLinkedList class
class DoubleLinkedList
{
private:
    template <typename T>
    struct Node
    {
        Node *prev;
        Node *next;
        T data;
    };
    // Node* head;

public:
    DoubleLinkedList(/* args */);
    ~DoubleLinkedList();
};

DoubleLinkedList::DoubleLinkedList(/* args */)
{
}

DoubleLinkedList::~DoubleLinkedList()
{
}
