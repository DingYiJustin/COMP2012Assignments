#include <iostream>
#include "bst.h"
using namespace std;

template <typename T>          
bool BST<T>::breakbond(const T& x)
{
    // This function should find the first bond that exceeds the value of x, break it and return
    // If no such bond exists, then simply return
    // When implementing, take note of the following:
    // 1. Search from the leftmost branch and iteratively move to the rightmost branch (similar to how we search from smallest value in normal BST search)
    // 2. But take note! that this is trying to find the 'bond' which is the absolute value of the difference in value instead of the value itself!
    // 3. Upon finding the first bond that is greater than the function parameter value x, break the bond and return. Careful: Only break the first bond that meets this criteria
    // 4. breakbond function should return true when a bond has been broken otherwise return false
    
    // Hint: You could consider taking advantage of the boolean returned for recursive call
    if(is_empty())
        return false;
    if(!root->left.is_empty())
    {
        int temp = root->value - root->left.root->value;
        temp = (temp>=0)?temp:-temp;
        if(temp>x)
        {
            //delete 
            root->left.beKilled();
            return true;
        }
    }
    if(root->left.breakbond(x))
        return true;
    if(!root->right.is_empty())
    {
        int temp = root->value - root->right.root->value;
        temp = ((temp>=0)?temp:-temp);
        if(temp>x)
        {
            //delete 
            root->right.beKilled();
            return true;
        }
    }
    if(root->right.breakbond(x))
        return true;
    return false;
}

template <typename T>
BST<T>::BST(const BST<T>& bst)
{
    // This function should perform deep-copy of one BST to another
    *this = bst;  
}

template <typename T>
int BST<T>::getMaxcounter() const
{
    // This function should find the maximum counter value of all the nodes present in BST
    if(root == nullptr)
        return 0;
    if(root->left.is_empty() && root->right.is_empty())
        return root->counter;
    else
    {
        int maxCounterLeft = root->left.getMaxcounter();
        int maxCounterRight = root->right.getMaxcounter();
        if(root->counter >= maxCounterLeft)
        {
            if(root->counter >= maxCounterRight)
                return root->counter;
            else
                return maxCounterRight;
        }
        else
        {
            if(maxCounterLeft >= maxCounterRight)
                return maxCounterLeft;
            else
                return maxCounterRight;
        }
    }
         
}

template <typename T>
int BST<T>::getMaxHeight() const{
    // This function should return the maximum height of the BST
    if(root == nullptr)
        return 0;
    int heightLeft = root->left.getMaxHeight();
    int heightRight = root->right.getMaxHeight();
    return 1+((heightLeft>=heightRight)?heightLeft:heightRight);
    
}

template <typename T>          
void BST<T>::insert(const T& x)
{
    // This function inserts the given value into the BST
    // If the value to be inserted already exists in the BST, remember to handle the counter!
    if(root == nullptr)
        root = new BSTnode(x);
    else if(x == root->value)
        root->counter++;
    else if(x<root->value)
        root->left.insert(x);
    else
        root->right.insert(x);
}

template <typename T>
void BST<T>::mutate()
{
    // This function aims to mutate the virus such that it minimizes bond length while maintaining all the nodes
    // Write a function that reorders the nodes of the BST such that the bond length is minimized
    // This reordering can only occur if the height of the tree is at least 3. If less than 3, then do nothing.

    // NOTE: In the process of mutating, the virus BST loses information of its nodes' counter values.
    //       In another words, you do not need to worry about preserving the counter value when reordering the nodes!

    // Hint: 
    // 1. You could consider using operator[] if you have implemented it prior to this
    // 2. Suppose we have two nodes A and B. The bond length (difference between value of A and B) is minimal when
    //    there are no other nodes with value in between A and B. Hope this helps~
    BST temp;
    for(int i = 0; i<this->totalNodes();i++)
    {
        temp.insert((*this)[i]);
    }
    this->beKilled();
    *this = temp;
}

template <typename T>
int BST<T>::totalNodes() const{

    // This function should return the total number of nodes present in the BST
    if(root == nullptr)
        return 0;
    else
        return 1+root->left.totalNodes()+root->right.totalNodes();
}
