#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <iostream>
template<typename T>
class Queue{
    private:
        struct Node{ T item; Node* next;};
        Node* head;
        Node* rear;
        int num;
    public:
        Queue();
        ~Queue();
        bool isempty()const;
        bool InQueue(T& i);
        bool DeQueue(T& i);
        int count()const;
};

template<typename T>
Queue<T>::Queue()
{
    head = rear = nullptr;
    num = 0;
}
template<typename T>
Queue<T>:: ~Queue()
{
    Node* temp = head;
    while(head){
        head = head->next;
        delete temp;
        temp = head;
    }
}
template<typename T>
bool Queue<T>:: isempty()const
{
    return (num == 0)? true:false;
}
template<typename T>
bool Queue<T>::InQueue(T& i)
{
    Node* NewNode = new Node;
    NewNode->item = i;
    num++;
    if(isempty()){
        NewNode->next = nullptr;
        head = NewNode;
        rear = NewNode;
        return true;
    }else{
        NewNode->next = head;
        head = NewNode;
        return true;
    }
}
template<typename T>
bool Queue<T>::DeQueue(T& i)
{
    if(!isempty()){
        i = head->item;
        Node* temp = head;
        if(head->next) head = head->next;
        else head = rear = nullptr;
        delete temp;
        num--;
        return true;
    }else{
        return false;
    }
}
template<typename T>
int Queue<T>::count()const
{
    return num;
}
#endif