#ifndef H_BINARYTREE
#define H_BINARYTREE

#include "node.h"

typedef enum {left_side, right_side } SIDE;

SIDE rnd(){ 
    return rand()%2 ? right_side : left_side;
}// End of rnd()

template <typename T> class BinaryTree{

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T&);                     // inserts node in tree
    void         Inorder(void (*)(const T&));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T> *) const;                 // private version of getSize()
    unsigned _getHeight(Node<T> *) const;               // private version of getHeight()
    void     _Insert(Node<T> *&, const T&);             // private version of Insert()
    void     _Inorder(Node<T> *, void (*)(const T&));   // private version of Inorder()
};

template <typename T>
BinaryTree<T>::BinaryTree()
    {
    root = nullptr;
    }

template <typename T>
unsigned int BinaryTree<T>::getSize() const
    {
    return _getSize(root);
    }

template <typename T>
unsigned int BinaryTree<T>::_getSize(Node<T> *node) const
    {
    unsigned int cnt = 1;
    if(node == nullptr)
        return 0;
    if(node->left != nullptr)
        cnt += _getSize(node->left);
    if(node->right != nullptr)
        cnt += _getSize(node->right);
    return cnt;
    }

template <typename T>
unsigned int BinaryTree<T>::getHeight() const 
    {
    return _getHeight(root);
    }

template <typename T>
unsigned int BinaryTree<T>::_getHeight(Node<T> *node) const
    {
    if(node == nullptr)
        return 0;

    else
        {
        int left = _getHeight(node->left);
        int right = _getHeight(node->right);

        if(left > right)
            return ++left;
        else
            return ++right;
        
        }
    }   


template <typename T>
void BinaryTree<T>::Insert(const T& newData)
    {
    _Insert(root, newData);
    }


template <typename T>
void BinaryTree<T>::_Insert(Node<T> *&node, const T &newData)
    {
    if(node == nullptr)
        node = new Node<T>(newData, nullptr, nullptr);
    else
        {
        SIDE decide;
        decide = rnd();
        if(decide == left_side)
            _Insert(node->left, newData);
        else
            _Insert(node->right, newData);
        }  
    }

template <typename T>
void BinaryTree<T>::Inorder(void (*f)(const T&))
    {
    _Inorder(root, f);
    }

template <typename T>
void BinaryTree<T>::_Inorder(Node<T> *node, void (*f)(const T&))
    {
    if(node != nullptr)
        {
        _Inorder(node->left, f);
        f(node->data);
        _Inorder(node->right, f);
        }
    }


#endif // End of H_BINARYTREE
