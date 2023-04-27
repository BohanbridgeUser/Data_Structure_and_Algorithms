#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <iostream>
#include "LinkList.h"
#include <optional>
#include <cstdlib>
#include <stdexcept>
template <typename T, int N>
class Array{
    private:
        T items[N];
        int num;
        int qsize;
    public:
        Array();
        Array(T a[], int n);
        ~Array();
        T operator[](int n)const;
        T& operator[](int n);
};
template<typename T, int N>
Array<T,N>::Array():num(0),qsize(N)
{
}
template<typename T, int N>
Array<T,N>::Array(T a[], int n):num(n),qsize(N)
{
    for(int i=0;i<n;++i) {
        items[i] = a[i];
    }
}
template<typename T, int N>
Array<T,N>:: ~Array()
{
}
template<typename T, int N>
T Array<T, N>::operator[](int n)const
{
    if(n < 0 || n > qsize){
        throw std::logic_error("ERROR INDEX");
    }else{
        return items[n];
    }
}
template<typename T, int N>
T& Array<T,N>::operator[](int n)
{
    if(n < 0 || n > qsize){
        throw std::logic_error("ERROR INDEX");
    }else{
        return items[n];
    }
}
#endif