#include "bst.h"

template <typename T>
const T& BST<T>::operator[](int i) const
{
    // This function overloads operator[] whereby when value i is indexed, the (i+1)th smallest value is returned
    
    // Hint: remember to handle out of bound indexing
    int size = totalNodes();

    if(i>=0)
    {
        i%=size;
    }
    else
    {
        i = (-i)%size;
        if(i!=0)
            i = size - i;
    }

    // cout<<"i:"<<i<<endl;
    const BSTnode* node = root;
    int sizeleft = node->left.totalNodes();
    // cout<<"root node value:"<<node->value<<endl;
    while(sizeleft != i)
    {
        // cout<<"current value:"<<node->value<<endl;
        sizeleft = (node->left.root != nullptr)?node->left.totalNodes():0;
        // cout<<"sizeleft:"<<sizeleft<<endl;
        // cout<<"i:"<<i<<endl;
        if(sizeleft<i)
        {
            // cout<<"right"<<endl;
            i-=sizeleft;
            i--;
            sizeleft = node->right.totalNodes();
            node = node->right.root;
            
            
        }
        else if(sizeleft>i)
        {
            // cout<<"left"<<endl;
            sizeleft = node->left.totalNodes();
            node = node->left.root;
        }
        else
        {
            // cout<<"equal"<<endl;
            break;
        }
        // cout<<"none"<<endl;
    }
    
    // while(!node->right.is_empty())
    //     node = node->right.root;

    // cout<<"found value:"<<node->value<<endl;
    return node->value;
}

template <typename T>
BST<T> BST<T>::operator+(BST<T>& bst)
{
    // This function overloads operator+, this serves to illustrate when two BSTs merge into one BST
    // or in Virus-Cell-Vaccine scenario, it is when the Virus consumes the Cell
    // When the virus tries to consume the cell, it first needs to check if it has a node with counter value of at least 4.
    // If yes, then the virus will consume the cell, and else the virus does NOT consume and temp object of the virus created is returned from the function.

    // Suppose virus BST is A and cell BST is B. when we do A + B, return a new BST such that it's node values
    // are the same as when you insert all B's nodes from smallest to largest
    // NOTE: You only need to add each value of B once, in another words, you can ignore the counter value associated with the nodes of B

    // Hint: you could consider taking advantage of operator[] if you have implemented it before this!
    if(getMaxcounter()>=4)
    {
        BST temp(*this);
        for(int i = 0; i<bst.totalNodes();i++)
        {
            temp.insert(bst[i]);
        }       
        bst.beKilled();
        return temp;
    }
    return *this;
}

template <typename T>
void BST<T>::operator++(int)
{
    // This function should increment counter value present in ALL nodes of the BST
    if(is_empty())
        return;
    root->counter++;
    root->left++;
    root->right++;
}

template <typename T>
BST<T>& BST<T>::operator=(const BST& bst)
{
    // This function should overload the operator= such that it carries out deepcopy
    if(this != &bst)
    {
        if(bst.is_empty())
        {
            delete root;
            root = nullptr;
            return *this;
        }
        root = new BSTnode(*bst.root);
    }
    return *this;
}