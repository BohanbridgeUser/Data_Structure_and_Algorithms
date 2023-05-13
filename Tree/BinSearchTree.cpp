#include <iostream>
#include <stdio.h>

template<typename T>
class BinSTree
{
private:
    BinSTree* l;
    BinSTree* r;
    BinSTree* p;
    T k;
public:
    BinSTree();
    BinSTree(const T& item);
    ~BinSTree();
    BinSTree*& left() { return l; }
    BinSTree*& right() { return r; }
    BinSTree*& parent() { return p; }
    T& key() { return k; }
    BinSTree* find(const T& item);
    BinSTree* findmax();
    BinSTree* findmin();
    bool insert(const T& item);
    void del(const T& item);
    void preordertraversal(void (*p)(T& item));
    void inordertraversal(void (*p)(T& item));
    void postordertraversal(void (*p)(T& item));
};

template<typename T>
BinSTree<T>::BinSTree()
{
    l = r = p = nullptr;
    k = T();
}
template<typename T>
BinSTree<T>::BinSTree(const T& item)
{
    l = r = p = nullptr;
    k = item;
}
template<typename T>
BinSTree<T>::~BinSTree()
{
    std::cout << std::endl << k << ":destructor use\n";
    delete l;
    delete r;
}
template<typename T>
BinSTree<T>* BinSTree<T>::find(const T& item)
{
    if (item == k) {
        return this;
    }
    else if (k > item) {
        if (l == nullptr) return nullptr;
        else return l->find(item);
    }
    else {
        if (r == nullptr) return nullptr;
        else return r->find(item);
    }
}
template<typename T>
bool BinSTree<T>::insert(const T& item)
{
    if (item == k) {
        return true;
    }
    else if (k > item) {
        if (l == nullptr) {
            l = new BinSTree(item);
            l->parent() = this;
            return true;
        }
        else {
            return l->insert(item);
        }
    }
    else {
        if (r == nullptr) {
            r = new BinSTree(item);
            r->parent() = this;
            return true;
        }
        else {
            return r->insert(item);
        }
    }
}
template<typename T>
BinSTree<T>* BinSTree<T>::findmax()
{
    if (r == nullptr) {
        return this;
    }
    else {
        return r->findmax();
    }
}
template<typename T>
BinSTree<T>* BinSTree<T>::findmin()
{
    if (l == nullptr) {
        return this;
    }
    else {
        return l->findmin();
    }
}
template<typename T>
void BinSTree<T>::del(const T& item)
{
    BinSTree* target = find(item);
    if (target->l == nullptr && target->r == nullptr) {
        if (target == this) {
            target->key() = T();
            return;
        }
        if (target->p->left() == target) {
            BinSTree* temp = target;
            target->p->left() = nullptr;
            target->l = nullptr;
            target->r = nullptr;
            delete temp;
        }
        else {
            BinSTree* temp = target;
            target->p->right() = nullptr;
            target->l = nullptr;
            target->r = nullptr;
            delete temp;
        }
    }
    else if (target->l == nullptr && target->r != nullptr) {
        if (target->p->left() == target) {
            BinSTree* temp = target;
            target->p->left() = target->r;
            target->r->parent() = target->p;
            target->l = nullptr;
            target->r = nullptr;
            delete temp;
        }
        else {
            BinSTree* temp = target;
            target->p->right() = target->r;
            target->r->parent() = target->p;
            target->l = nullptr;
            target->r = nullptr;
            delete temp;
        }
    }
    else if (target->l != nullptr && target->r == nullptr) {
        if (target->p->left() == target) {
            BinSTree* temp = target;
            target->p->left() = target->l;
            target->l->parent() = target->p;
            target->l = nullptr;
            target->r = nullptr;
            delete temp;
        }
        else {
            BinSTree* temp = target;
            target->p->right() = target->l;
            target->l->parent() = target->p;
            target->l = nullptr;
            target->r = nullptr;
            delete temp;
        }
    }
    /* two methods: find the minimum of the right children of find the maximum of the left children */
    /* I chose to find the minimum of the right children */
    else {
        BinSTree* temp2 = target->r->findmin();
        target->k = temp2->k;
        temp2->del(temp2->k);
    }
}
template<typename T>
void BinSTree<T>::preordertraversal(void (*p)(T& item))
{
    if(k!=T()){
        p(k);
        if (l != nullptr) l->preordertraversal(p);
        if (r != nullptr) r->preordertraversal(p);
    }
}
template<typename T>
void BinSTree<T>::inordertraversal(void(*p)(T& item))
{
    if(k!=T()){
        if (l != nullptr) l->inordertraversal(p);
        p(k);
        if (r != nullptr) r->inordertraversal(p);
    }
    
}
template<typename T>
void BinSTree<T>::postordertraversal(void (*p)(T& item))
{
    if(k!=T()){
        if (l != nullptr) l->postordertraversal(p);
        if (r != nullptr) r->postordertraversal(p);
        p(k);
    }
}

void show(int& item)
{
    std::cout << item << ' ';
}

int main()
{
    BinSTree<int> root(6);
    root.insert(1);
    root.insert(3);
    root.insert(2);
    root.insert(5);
    root.insert(9);
    root.insert(7);
    root.insert(8);
    root.insert(4);
    std::cout << "Pre:\n";
    root.preordertraversal(show);
    std::cout << "\nIn:\n";
    root.inordertraversal(show);
    std::cout << "\nPost:\n";
    root.postordertraversal(show);
    /* delete and inordershow */
    std::cout << "\ndelete and inordershow:\n";
    // root.del(5);
    // root.inordertraversal(show);
    // std::cout << std::endl;
    // root.del(3);
    // root.inordertraversal(show);
    // root.del(6);
    // root.inordertraversal(show);
    for (int i=9;i>0;--i) {
        if (i==6) continue;
        else root.del(i);
    }
    root.inordertraversal(show);
    root.del(6);
    root.inordertraversal(show);
    return 0;
}