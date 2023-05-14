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
        void insert_fixup(TNode* pt);
    public:
        RBTree();
        RBTree(const T& item);
        ~RBTree();
        TNode*& find(TNode* r = root, const T& item);
        TNode*& findmax(TNode* rot = root);
        TNode*& findmin(TNode* rot = root);
        void insert(TNode* r = root, const T& item);
};
template<typename T>
RBTree<T>::RBTree()
{
    sentry = new TNode;
    sentry->T = T();
    sentry->color = black;
    sentry->l = nullptr;
    sentry->r = nullptr;
    sentry->p = nullptr;
    
    root = sentry;
}
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
RBTree<T>::TNode*& RBTree<T>::find(TNode* rot, const T& item)
{
    if (rot == sentry) {
        return sentry;
    } else {
        if ( rot->k == item ) return rot;
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
template<typename T>
void RBTree<T>::left_rotation(TNode* pt)
{
    TNode* x = pt, y = pt->r, z = x->p;
    y->p = z;
    if (z->l == x) {
        z->l = y;
    } else if (z->r == x) {
        z->r = y;
    }
    x->r = y->l;
    y->l->p = x;
    y->l = x;
    x->p = y;
}
template<typename T>
void RBTree<T>::right_rotation(TNode* pt)
{
    TNode* x = pt, y = pt->l, z = pt->p;
    y->p = z;
    if (z->l == x) {
        z->l = y;
    } else if (z->r == x) {
        z->r = y;
    }
    x->l = y->r;
    y->r->p = x;
    y->r = x;
    x->p = y;
}
template<typename T>
void RBTree<T>::insert(TNode* pt, const T& item)
{
    x = pt;
    y = sentry;
    TNode* NewNode = new TNode;
    NewNode->k = item;
    NewNode->l = sentry;
    NewNode->r = sentry;
    NewNode->c = red;
    while (x!=sentry) {
        y = x;
        if (x->k > item) x = x->l;
        else x = x->r;
    }
    NewNode->p = y;
    if (y==root) root = NewNode;
    if (NewNode->k > y->k) y->r = NewNode;
    else y->l = NewNode;
    insert_fixup(TNode* NewNode);
}
template<typename T>
void RBTree<T>::insert_fixup(TNode* pt)
{
    
}