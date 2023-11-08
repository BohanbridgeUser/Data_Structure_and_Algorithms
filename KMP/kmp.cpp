#include <iostream>
#include <vector>
#include <string>

/**
 * @name   KMP Algorithm
 * @brief  Algorithm is used for fast matching a substring in a given string
 * @details 
 *          1.Calulate the next/prefix array;
 *          2.Match string by next array;
 * */

using namespace std;

vector<int> CalNext(string const& needle){
    int j=0;
    vector<int> next(needle.size(),0);
    for(int i=1;i<needle.size();++i){
        while(needle[i]!=needle[j] && j!=0){
            j = next[j-1];
        }
        if(needle[i]==needle[j]) j++;
        next[i] = j;
    }
    return next;
}


int main()
{
    /** 
     * @brief @param needle is substring that used for matching.
     *        @param haystack is the string that be matched.
     *        If there is a @param needle in @param haystack, output the first index of substring in @param haystack.
     *        Otherwise output -1.
     * */
    string needle,haystack;
    vector<int> next = CalNext(needle);
    int i=0,j=0;
    while(i<haystack.size() && j<needle.size()){
        while(needle[j]!=haystack[i]){
            j = next[j-1];
        }
        if(needle[j] == haystack[i]) j++;
        i++;
    }
    if(i==haystack.size() && j!=needle.size()) cout <<  -1;
    cout << i-j;
    return 0;
}
