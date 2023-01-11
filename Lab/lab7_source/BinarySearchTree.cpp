//
// Created by ck on 2021/11/5.
//

#include <iostream>

#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree(int id)
    : id(id), leftSubTree(nullptr), rightSubTree(nullptr) {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& other): id(other.id)
{
    // TODO: Clone the two subtrees accordingly.
    if(other.leftSubTree)
        leftSubTree = new BinarySearchTree(*other.leftSubTree);
    if(other.rightSubTree)
        rightSubTree = new BinarySearchTree(*other.rightSubTree);
}

BinarySearchTree::~BinarySearchTree()
{
    // TODO: release the resources occupied by the two subtrees if any.
    if(leftSubTree)
        delete leftSubTree;
    if(rightSubTree)
        delete rightSubTree;
}

void BinarySearchTree::add(int newId)
{
    // TODO: Insert the newId to the current tree.
    // You need to create a new node for the newId and attach it to the correct place.
    // Do nothing if the id is already in the tree.
    if(hasId(newId))
        return;
    if(newId<id)
    {
        if(leftSubTree != nullptr)
            leftSubTree->add(newId);
        else
        {
            leftSubTree = new BinarySearchTree(newId);
        }   
    }
    else
    {
        if(rightSubTree != nullptr)
            rightSubTree->add(newId);
        else
        {
            rightSubTree = new BinarySearchTree(newId);
        }
    }
    
}

bool BinarySearchTree::hasId(int idToFind) const
{
    // TODO: Check whether the given id is in the tree.
    // You need to determinate whether to seach the left subtree or right subtree.
    if(id == idToFind)
        return true;
    if(idToFind<id)
    {
        if(leftSubTree)
            return leftSubTree->hasId(idToFind);
        else
            return false;
    }
    if(rightSubTree)
        return rightSubTree->hasId(idToFind);
    else
        return false;

    // if(id == idToFind)
    //     return true;
    // else if(rightSubTree==nullptr && leftSubTree==nullptr)
    //     return false;
    // else if(idToFind<id)
    //     return (leftSubTree!=nullptr)?leftSubTree->hasId(idToFind):false;
    // else
    //     return (rightSubTree!=nullptr)?rightSubTree->hasId(idToFind):false;
}

int BinarySearchTree::height() const
{
    // TODO: Calculate the height of the tree.
    // Tree like this has height 0:
    //    O
    //
    // Trees like these have height 1:
    //    O        O       O
    //  /  \        \     /
    // O    O        O   O
    if(leftSubTree == nullptr && rightSubTree == nullptr)
        return 0;
    int heightOfLeft = (leftSubTree)?leftSubTree->height():0;
    int heightOfRight = (rightSubTree)?rightSubTree->height():0;
    return 1+((heightOfLeft>=heightOfRight)?heightOfLeft:heightOfRight);   
}

void BinarySearchTree::printDFSPrefix() const
{
    std::cout << id << " ";
    if (leftSubTree != nullptr)
        leftSubTree->printDFSPrefix();

    if (rightSubTree != nullptr)
        rightSubTree->printDFSPrefix();
}

void BinarySearchTree::printDFSInfix() const
{
    if (leftSubTree != nullptr)
        leftSubTree->printDFSInfix();
    std::cout << id << " ";
    if (rightSubTree != nullptr)
        rightSubTree->printDFSInfix();
}
