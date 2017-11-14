
#include "TreeNode.h"
#include <iostream>
#include <iomanip>
using namespace std; 


TreeNode::TreeNode(DBentry* _entryPtr)
{
    entryPtr = _entryPtr;
    left = NULL;
    right = NULL;
}

TreeNode::~TreeNode()
{
    delete entryPtr;
    if (left) delete left;
    if (right) delete right;
}


void TreeNode::setLeft(TreeNode* newLeft)
{
    left = newLeft;
}


void TreeNode::setRight(TreeNode* newRight)
{
    right = newRight;
}

TreeNode* TreeNode::getLeft() const
{
    return left;
}

TreeNode* TreeNode::getRight() const
{
    return right;
}

DBentry* TreeNode::getEntry() const
{
    return entryPtr;
}

