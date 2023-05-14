#include <iostream>

template<typename T>
class RBTree
{
    private:
        enum color { red, black };
    public:
        struct TNode
        {
            T k;
            color c;
            TNode* l;
            TNode* r;
            TNode* p;
        };
        using PTNode = TNode*;
    private:
        PTNode root;
        PTNode sentry;
        void left_rotation(PTNode pt);
        void right_rotation(PTNode pt);
        void insert_fixup(PTNode pt);
    public:
        RBTree();
        RBTree(const T& item);
        ~RBTree();
        PTNode find(const T& item, PTNode r);
        PTNode findmax(PTNode rot = root);
        PTNode findmin(PTNode rot = root);
        void insert(const T& item, PTNode r);
        void inordertraversal(PTNode pt);
        PTNode retroot()const { return root; }
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
    sentry->k = T();
    sentry->c = black;
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
typename RBTree<T>::PTNode RBTree<T>::find(const T& item, PTNode rot)
{
    if (rot == sentry) {
        return sentry;
    }
    else {
        if (rot->k == item) return rot;
        else if (rot->k < item) {
            return find(rot->l, item);
        }
        else if (rot->k > item) {
            return find(rot->r, item);
        }
    }
}
/* Here is an important thing. 
If you use a template which nesting a structure of class, 
You have to add "typename"-ex before the structrue of class*/
template<typename T>
typename RBTree<T>::PTNode RBTree<T>::findmax(PTNode rot)
{
    if (rot->r != sentry) return findmax(rot->r);
    else return rot;
}
template<typename T>
typename RBTree<T>::PTNode RBTree<T>::findmin(PTNode rot)
{
    if (rot->l != sentry) return findmin(rot->l);
    else return rot;
}
template<typename T>
void RBTree<T>::left_rotation(PTNode pt)
{
    PTNode x = pt, y = pt->r, z = x->p;
    y->p = z;
    if (z->l == x) {
        z->l = y;
    }
    else if (z->r == x) {
        z->r = y;
    }
    x->r = y->l;
    y->l->p = x;
    y->l = x;
    x->p = y;
}
template<typename T>
void RBTree<T>::right_rotation(PTNode pt)
{
    PTNode x = pt, y = pt->l, z = pt->p;
    y->p = z;
    if (z->l == x) {
        z->l = y;
    }
    else if (z->r == x) {
        z->r = y;
    }
    x->l = y->r;
    y->r->p = x;
    y->r = x;
    x->p = y;
}
template<typename T>
void RBTree<T>::insert_fixup(PTNode pt)
{
    PTNode z = pt->p, x = pt;
    while (z->c == red) {
        PTNode y = sentry;
        // if x is left child of z
        if (z == z->p->l) {
            y = z->p->r;
            // case 1 uncle and father are red
            if (y->c == red) {
                z->c = black;
                y->c = black;
                // obviouly left child and right child are red, the grandfather is black
                z->p->c = red;
                x = z->p;
                z = x->p;
            } else if (x == z->r) {
                left_rotation(z);
            }
            else {
                z->c = black;
                z->p->c = red;
                right_rotation(z->p);
            }
        }
        else {
            y = z->p->l;
            // case 1 uncle and father are red
            if (y->c == red) {
                z->c = black;
                y->c = black;
                z->p->c = red;
                x = z->p;
                z = x->p;
            }
            else if (x == z->l) {
                right_rotation(z);
            }
            else {
                z->c = black;
                z->p->c = red;
                left_rotation(z->p);
            }
            
        }
    }
    root->c = black;
}
template<typename T>
void RBTree<T>::insert(const T& item, PTNode pt)
{
    PTNode x = pt;
    PTNode y = sentry;
    PTNode NewNode = new TNode;
    NewNode->k = item;
    NewNode->l = sentry;
    NewNode->r = sentry;
    NewNode->c = red;
    while (x != sentry) {
        y = x;
        if (x->k > item) x = x->l;
        else x = x->r;
    }
    NewNode->p = y;
    if (y == sentry) root = NewNode;
    if (NewNode->k > y->k) y->r = NewNode;
    else y->l = NewNode;
    insert_fixup(NewNode);
}

template<typename T>
void RBTree<T>::inordertraversal(PTNode pt)
{
    if (pt != sentry) {
        inordertraversal(pt->l);
        std::cout << pt->k << ' ';
        inordertraversal(pt->r);
    }
}

int main()
{
    RBTree<int> root(11);
    root.insert(2,root.retroot());
    root.insert(14,root.retroot());
    root.insert(1,root.retroot());
    root.insert(7,root.retroot());
    root.insert(5,root.retroot());
    root.insert(8,root.retroot());
    root.insert(15,root.retroot());
    root.insert(4, root.retroot());
    root.inordertraversal(root.retroot());


    return 0;
}