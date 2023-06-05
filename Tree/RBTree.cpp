#include <iostream>
#include <cstdlib>

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
        void delnode_fixup(PTNode pt);
        void transplate(PTNode pt1, PTNode pt2);
    public:
        RBTree();
        RBTree(const T& item);
        ~RBTree();
        PTNode find(const T& item, PTNode r);
        PTNode findmax(PTNode rot);
        PTNode findmin(PTNode rot);
        void insert(const T& item, PTNode r);
        void inordertraversal(PTNode pt);
        void preordertraversal(PTNode pt);
        void postordertraversal(PTNode pt);
        void destruct(PTNode pt);
        PTNode delnode(const T& item, PTNode r);
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
    root->c = black;
}
template<typename T>
void RBTree<T>::destruct(PTNode pt)
{
    if (pt != sentry) {
        T k = pt->k;
        destruct(pt->l);
        destruct(pt->r);
        delete pt;
        pt = nullptr;
        std::cout << k << ":destructor\n";
    }
}
template<typename T>
RBTree<T>::~RBTree()
{
    std::cout << root->k << ":destructor\n";
    destruct(root);
    delete sentry;
}

template<typename T>
typename RBTree<T>::PTNode RBTree<T>::find(const T& item, PTNode rot)
{
    if (rot == sentry) {
        return sentry;
    }
    else {
        if (rot->k == item) 
        {
            return rot;
        }
        else if (rot->k < item) {
            return find(item, rot->l);
        }
        else {
            return find(item, rot->r);
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
    PTNode x = pt, y = pt->r;
    y->p = x->p;
    if (x == root) {
        root = y;
    }
    else if (x->p->l == x) {
        x->p->l = y;
    }
    else {
        x->p->r = y;
    }
    x->r = y->l;
    y->l->p = x;
    y->l = x;
    x->p = y;
}
template<typename T>
void RBTree<T>::right_rotation(PTNode pt)
{
    PTNode x = pt, y = pt->l;
    y->p = x->p;
    if (root == x) {
        root = y;
    }
    else if (x->p->l == x) {
        x->p->l = y;
    }
    else {
        x->p->r = y;
    }
    x->l = y->r;
    y->r->p = x;
    y->r = x;
    x->p = y;
}
template<typename T>
void RBTree<T>::insert_fixup(PTNode pt)
{
    PTNode x = pt;
    while (x->p->c == red) {
        PTNode y = sentry;
        if (x->p == x->p->p->l) {
            y = x->p->p->r;
            // case 1 uncle and father are red
            if (y->c == red) {
                x->p->c = black;
                y->c = black;
                // obviouly left child and right child are red, the grandfather is black
                x->p->p->c = red;
                x = x->p->p;
            }
            else {
                if (x == x->p->r) { // case 2
                    x = x->p;
                    left_rotation(x);
                }
                x->p->c = black; // case 3
                x->p->p->c = red;
                right_rotation(x->p->p);
            }
        }
        else {
            y = x->p->p->l;
            // case 1 uncle and father are red
            if (y->c == red) {
                x->p->c = black;
                y->c = black;
                x->p->p->c = red;
                x = x->p->p;
                x->p = x->p;
            }
            else {
                if (x == x->p->l) { // case 2
                    x = x->p;
                    right_rotation(x);
                }
                x->p->c = black;
                x->p->p->c = red;
                left_rotation(x->p->p);
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
        std::cout << pt->k << ' ' << pt->c << std::endl;
        inordertraversal(pt->r);
    }
}
template<typename T>
void RBTree<T>::preordertraversal(PTNode pt)
{
    if (pt != sentry) {
        std::cout << pt->k << ' ' << pt->c << std::endl;
        preordertraversal(pt->l);
        preordertraversal(pt->r);
    }
}
template<typename T>
void RBTree<T>::postordertraversal(PTNode pt)
{
    if (pt != sentry) {
        postordertraversal(pt->l);
        postordertraversal(pt->r);
        std::cout << pt->k << ' ' << pt->c << std::endl;
    }
}
template<typename T>
void RBTree<T>::transplate(PTNode pt1, PTNode pt2)
{
    // replace 1 with 2 relative to pt1's parent
    if (pt1 == root) {
        root = pt2;
        pt2->p = sentry;
    }
    else if (pt1->p->l == pt1) {
        pt1->p->l = pt2;
    }
    else {
        pt1->p->r = pt2;
    }
    if (pt2 != sentry) pt2->p = pt1->p;
}
template<typename T>
void RBTree<T>::delnode_fixup(PTNode pt)
{
    // Because Y node is black so the path passed Y deduced 1. 
    // It's not hard to think of adding a node into the path by rotating.
    PTNode x = pt;
    while (x != root && x->c == black) {
        if (x->p->l == x) {
            PTNode w = x->p->r;
            if (w->c == red) {
                w->c = black;
                x->p->c = red;
                left_rotation(x->p);
                w = x->p->r;
            }
            if (w->l->c == black && w->r->c == black) {
                w->c = red;
                x = x->p;
            }
            else {
                if (w->r->c == black) {
                    w->l->c = black;
                    w->c = red;
                    right_rotation(w);
                    w = x->p->r;
                }
                w->c = x->p->c;
                x->p->c = black;
                w->r->c = black;
                left_rotation(x->p);
                x = root;
            }
        }
        else {
            PTNode w = x->p->l;
            if (w->c == red) {
                w->c = black;
                x->p->c = red;
                right_rotation(x->p);
                w = x->p->l;
            }
            if (w->r->c == black && w->l->c == black) {
                w->c = red;
                x = x->p;
            }
            else {
                if (w->l->c == black) {
                    w->r->c = black;
                    w->c = red;
                    left_rotation(w);
                    w = x->p->l;
                }
                w->c = x->p->c;
                x->p->c = black;
                w->r->c = black;
                right_rotation(x->p);
                x = root;
            }
        }
    }
    x->c = black;
}
template<typename T>
typename RBTree<T>::PTNode RBTree<T>::delnode(const T& item, PTNode rot)
{
    PTNode z = sentry, x = sentry;
    z = find(item, rot);
    PTNode y = z;
    color y_color = z->c; // y is relative to x, that was moved to z position. 
    if (z->l == sentry) { // only right child or no child
        x = z->r;
        transplate(z, z->r);
    }
    else if (z->r == sentry) {// only left child
        x = z->l;
        transplate(z, z->l);
    }
    else {// two child
        y = findmin(z->r);
        y_color = y->c;
        x = y->r;
        if (y == z->r && x != sentry) {
            x->p = y;
        }
        else {
            transplate(y, x);
            y->r = z->r;
            y->r->p = y;
        }
        transplate(z, y);
        y->l = z->l;
        y->l->p = y;
        y->c = z->c;
    }
    if (y_color == black && x != sentry) delnode_fixup(x);
    return z;
}

int main()
{
    {
        RBTree<int>* root = new RBTree<int>(11);

        root->inordertraversal(root->retroot());
        root->insert(2, root->retroot());
        root->inordertraversal(root->retroot());
        std::cout << std::endl;
        root->insert(14, root->retroot());
        root->inordertraversal(root->retroot());
        std::cout << std::endl;
        root->insert(1, root->retroot());
        root->inordertraversal(root->retroot());
        std::cout << std::endl;
        root->insert(7, root->retroot());
        root->inordertraversal(root->retroot());
        std::cout << std::endl;
        root->insert(5, root->retroot());
        root->inordertraversal(root->retroot());
        std::cout << std::endl;
        root->insert(8, root->retroot());
        root->inordertraversal(root->retroot());
        std::cout << std::endl;
        root->insert(15, root->retroot());
        root->inordertraversal(root->retroot());
        std::cout << std::endl;
        root->insert(4, root->retroot());
        root->inordertraversal(root->retroot());
        std::cout << std::endl;
        std::cout << root->retroot()->k << std::endl;
        
        root->delnode(7, root->retroot());
        root->inordertraversal(root->retroot());
        root->preordertraversal(root->retroot());
        std::cout << std::endl;
        std::cout << root->retroot()->k << std::endl;
        delete root;
    }

    return 0;
}