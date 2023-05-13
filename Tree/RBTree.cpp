#include <iostream>

template<typename T>
class RBTree
{
    private:
        enum color{red, black};
        struct TNode 
        {
            T k;
            color c;
            TNode* l;
            TNode* r;
            TNode* p;
        }
        TNode* root;
        TNode* sentry;
    public:
        
};