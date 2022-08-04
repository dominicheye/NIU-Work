// include other header files (if any)
#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include "node.h"
#include "bstDriver.h"


//function and variable to find a random side for Insert in BinaryTree
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
}; // End of BinaryTree class


//default constructor, sets root to nullptr
template <typename T>
BinaryTree<T>::BinaryTree()
    {
    this->root = nullptr;
    }// End of BinaryTree()


//calls private version of getSize
template <typename T>
unsigned int BinaryTree<T>::getSize() const
    {
    return _getSize(this->root);
    }// End of getSize()


//recursive function that goes through left and right sides until past leaf, then counts until
//back to root from every side
template <typename T>
unsigned int BinaryTree<T>::_getSize(Node<T> *node) const
    {
    unsigned int cnt = 1;

    //starts going back through all called functions
    if(node == nullptr)
        return 0;

    //add count from called functions and return the final count
    if(node->left != nullptr)
        cnt += _getSize(node->left);
    if(node->right != nullptr)
        cnt += _getSize(node->right);
    return cnt;
    }// End of _getSize()


//calls private version of getHeight
template <typename T>
unsigned int BinaryTree<T>::getHeight() const 
    {
    return _getHeight(this->root);
    }// End of getHeight()


//goes to every leaf and then returns back up, only returns the bigger count from left or right
template <typename T>
unsigned int BinaryTree<T>::_getHeight(Node<T> *node) const
    {
    //starts going back up if past a leaf
    if(node == nullptr)
        return 0;
    
    else
        {
        //go down both branches
        int left = _getHeight(node->left);
        int right = _getHeight(node->right);

        //only return the bigger one.
        if(left > right)
            return ++left;
        else
            return ++right;
        
        }// End of else
    } // End of _getHeight()  

//calls private version of Insert
template <typename T>
void BinaryTree<T>::Insert(const T& newData)
    {
    _Insert(this->root, newData);
    }// End of Insert()

//inserts new data at as random node, based off of RND() function, uses  recursive
template <typename T>
void BinaryTree<T>::_Insert(Node<T> *&node, const T &newData)
    {
    //if it made it to clean spot, then insert new dynamic Node
    if(node == nullptr)
        {
        node = new Node<T>(newData);
        return;
        }// End of if
    //otherwise choose a side to go to
    else
        {
        //call rnd() to randomly decide a side
        SIDE decide;
        decide = rnd();

        //then based off of that go to that side 
        if(decide == left_side)
            _Insert(node->left, newData);
        else
            _Insert(node->right, newData);
        }// End of else  
    }// End of _Insert()

//calls private version of inorder
template <typename T>
void BinaryTree<T>::Inorder(void (*f)(const T&))
    {
    _Inorder(this->root, f);
    }// End of Inorder()

//sends the nodes of the tree inorder through function given.
template <typename T>
void BinaryTree<T>::_Inorder(Node<T> *node, void (*f)(const T&))
    {
    //if it is a nullptr, it stops the recursive calls
    if(node != nullptr)
        {
        //keep going left until hits nullptr, then output Left Center Right
        _Inorder(node->left, f);
        f(node->data);
        _Inorder(node->right, f);
        }// End of if
    }// End of _Inorder

/*


NEW CLASS ASSIGNMENT 8



*/
template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    void Insert(const T &x);       // inserts node with value x
    bool Search(const T &x) const; // searches leaf with value x
    bool Remove(const T &x);       // removes leaf with value x
private:
    void _Insert(Node<T> *&, const T &);      // private version of insert
    bool _Search(Node<T> *, const T &) const; // private version of search
    void _Remove(Node<T> *&, const T &);      // private version of remove
    bool _Leaf(Node<T> *node) const;          // checks if node is leaf
};// End of BinarySearchTree class

//calls private version of insert
template <typename T>
void BinarySearchTree<T>::Insert(const T &x)
    {
    _Insert(this->root, x);
    }// End of Insert()

//calls private version of Search
template <typename T>
bool BinarySearchTree<T>::Search(const T &x) const
    {
    return _Search(this->root, x);
    }// End of Search()


//calls search to see if given number is in a leaf, if not then returns false,
//or returns true if it is and was removed. also calls private version of remove 
template <typename T> 
bool BinarySearchTree<T>::Remove(const T &x)
    {
    if(Search(x)==true)
        {
        _Remove(this->root, x);
        return true;
        }// End of if
    else
        return false;
    }// End of Remove()

//inserts number in the tree so that it is in a spot that works for inorder
//looks to see if number given is bigger or smaller than data in given node 
//to call next function with left or right til nullptr node, then creates new node
template <typename T>
void BinarySearchTree<T>::_Insert(Node<T> *&node, const T &num)
    {
    //create new node if we made it to a nullptr
    if(node == nullptr)
        {
        node = new Node<T>(num);
        return;
        }// End of if
    //otherwise keep looking, go left if num is smaller than data in node,
    //or right is num is bigger than the data in the node
    else
        {
        if(node->data > num)
            _Insert(node->left, num);
        else if(node->data < num)
            _Insert(node->right, num);
        } // End of else

    }// End of _Insert()

//searches for num given in leafs, first checks if node is null to make sure
// it doesn't look for data in a nonexistant node. then looks in the direction of the
//data by comparing it to the data in the node we're in
template <typename T>
bool BinarySearchTree<T>::_Search(Node<T> *node, const T &num) const
    {
    //declare a variable that passes info function to function
    bool found = false;
    //checks that we didn't go past a leaf
    if(node == nullptr)
            return false;
    
    //if the node is a leaf and has the number return true
    if(_Leaf(node) == true)
        {
        if(node->data == num)
            return true;
        }// End of if

    //if it isn't then keep searching, go left if smaller than node data 
    //or right if bigger
    else
        {
        if(node->data < num)
        found = _Search(node->right, num);
        else if(node->data > num)
        found = _Search(node->left, num);
        }// End of else
    //return the recursive answer.
    return found;
    }// End of _Search()

//function to remove a leaf node, recursive and works through many steps
template <typename T>
void BinarySearchTree<T>::_Remove(Node<T> *&node, const T &num)
    {
    //if num isn't equal to what we have then keep looking
    if (node->data > num)
        _Remove(node->left, num);
    else if (node->data < num)
        _Remove(node->right, num);

    //if it is the same number then delete.
    else
        {
        //if it is a leaf, then delete and make it point to null
        if (_Leaf(node) == true)
            {
            delete node;
	        node = nullptr;
            }// End of if
        }// End of else
    }// End of _Remove()

//Returns true if the given node is a leaf, false if not
template <typename T>
bool BinarySearchTree<T>::_Leaf(Node<T> *node) const
    {
    //if both left and right nodes are nullptr then it is a leaf
    if(node->left == nullptr && node->right == nullptr)
        return true;
    else
        return false;
    }//End of _Leaf()



#endif // End of BINARYSEARCHTREE_H_