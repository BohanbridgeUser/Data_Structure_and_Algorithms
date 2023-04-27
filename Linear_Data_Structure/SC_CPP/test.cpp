#include "Array.h"
#include <cstdio>
#include <exception>
#include "Stack.h"
int main()
{
    // Array<int,10> a;
    // std::cout << a[20] << std::endl;
    // for(int i=0;i<10;++i) a[i] = i;
    // for(int i=0;i<15;++i) {
    //     try{
    //         std::cout << a[i] << std::endl;
    //     }
    //     catch(std::logic_error& e1) {
    //         std:: cout << e1.what() << std::endl;
    //         continue;
    //     }
    // } 
    Stack<int> S;
    for(int i=0;i<10;++i) S.push(i);
    int x;
    for(int i=0;i<10;++i) {
        S.pop(x);
        std::cout<< x << std::endl;
    }
    system("pause");
    
    return 0;
}