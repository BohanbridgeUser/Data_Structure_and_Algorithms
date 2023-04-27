#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>

template<typename T>
class Stack{
    private:
        struct Node{ T item; Node* next;};
        Node* head;
        int num;
    public:
        Stack();
        ~Stack();
        bool isempty()const;
        bool push(T& i);
        bool pop(T& i);
        int count()const;
};

template<typename T>
Stack<T>:: Stack()
{
    head = nullptr;
    num = 0;
}
template<typename T>
Stack<T>:: ~Stack()
{
    Node* temp = head;
    while(head){
        head = head->next;
        delete temp;
        temp = head;
    }
}
template<typename T>
bool Stack<T>::isempty()const
{
    return (num == 0)? true:false;
}
template<typename T>
bool Stack<T>::push(T& i)
{
    if(isempty()) {
        head = new Node;
        head->item = i;
        head->next = nullptr;
        num++;
    }else{
        Node* NewNode = new Node;
        NewNode->item = i;
        NewNode->next = head;
        head = NewNode;
        num++;
    }
    return true;
}
template<typename T>
bool Stack<T>::pop(T& i)
{
    if(isempty()) return false;
    else{
        i = head->item;
        Node* temp = head;
        head = head->next;
        delete temp;
        num--;
        return true;
    }
}
#endif