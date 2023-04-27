#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include <iostream>

template<typename T>
class Linklist{
    private:
        struct Node{ T Item; Node* Next;};
        Node* head;
        int num;
    public:
        Linklist();
        bool isempty()const;
        bool add(T& item);
        bool del(T& item);
        ~Linklist();
};

template<typename T>
Linklist<T>::Linklist()
{
    head = nullptr;
    num = 0;
}
template<typename T>
bool Linklist<T>:: isempty()const
{
    return (num == 0)? true:false;
}
template<typename T>
bool Linklist<T>:: add(T& item)
{
    Node* NewNode = new Node;
    NewNode->Item = item;
    NewNode->Next = head->Next;
    head = NewNode;
    return true; 
}
template<typename T>
bool Linklist<T>:: del(T& item)
{
    if(isempty()) return false;
    else{
        Node* temp = head;
        item = head->Item;
        head = head->Next;
        delete temp;
        return true;
    }
}
template<typename T>
Linklist<T>:: ~Linklist()
{
    Node* temp = head;
    while(head){
        head = head->Next;
        delete temp;
        temp = head;
    }
}
#endif