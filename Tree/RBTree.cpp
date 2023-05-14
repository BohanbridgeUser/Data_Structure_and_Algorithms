#include <iostream>

template<typename T>
class RBTree
{
    public:
        struct TNode 
        {
            T k;
            color c;
            TNode* l;
            TNode* r;
            TNode* p;
        }
    private:
        enum color{red, black};
        TNode* root;
        TNode* sentry;
        void left_rotation(TNode* pt);
        void right_rotation(TNode* pt);
        bool isempty()const;
        void insert_fixup(TNode* pt);
    public:
        RBTree(const T& item);
        ~RBTree();
        TNode*& find(TNode* r = root, const T& item);
        TNode*& findmax(TNode* rot = root);
        TNode*& findmin(TNode* rot = root);
        void insert(TNode* r = root, const T& item);
};

template<typename T>
RBTree<T>::RBTree(const T& item)
{
    sentry = new TNode;
    sentry->T = T();
    sentry->color = black;
    sentry->l = nullptr;
    sentry->r = nullptr;
    sentry->p = nullptr;

    root = new TNode;
    root->k = item;
    root->l = sentry;
    root->r = sentry;
    root->p = sentry;
}
template<typename T>
RBTree<T>::~RBTree()
{
    delete root->l;
    delete root->r;
    delete root;
    delete sentry;
}
template<typename T>
bool RBTree<T>::isempty()const
{
    return (root == nullptr);
}
template<typename T>
RBTree<T>::TNode*& RBTree<T>::find(TNode* rot, const T& item)
{
    if (rot == sentry) {
        return nullptr;
    } else {
        if ( rot->k == item ) return r;
        else if ( rot->k < item ) {
            return find(rot->l,item);
        } else if (rot->k > item ) {
            return find(rot->r,item);
        }
    }
}
template<typename T>
RBTree<T>::TNode*& RBTree<T>::findmax(TNode* rot)
{
    if ( rot->r != sentry ) return findmax(rot->r);
    else return rot;
}
template<typename T>
RBTree<T>::TNode*& RBTree<T>::findmin(TNode* rot)
{
    if (rot->l != sentry) return findmin(rot->l);
    else return rot;
}
