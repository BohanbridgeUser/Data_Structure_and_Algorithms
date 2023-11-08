#include <iostream>

/**
 * @name Quick Pow Algorithm
 * @brief the main idea is dicotomy(二分法)
 * @details the first method is using recursive thought.
 *          the second method is using low of powers.
*/

double quickPow(double x, long long N){
    if(N==0)return 1.0;

    double temp = quickPow(x,N/2);
    if(N%2) return temp * temp * x;
    else return temp * temp;
}

double quickPow2(double x, long long N){
    double ans = 1.0;
    double x_ = x;
    while(N>0){
        if(N%2) ans *= x_;
        x_ *= x_;
        N /= 2;
    }
    return ans;
}


int main(){
    
    return 0;
}