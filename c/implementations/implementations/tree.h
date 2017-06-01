#include "stdafx.h"

#pragma once

#ifndef TREE_H
#define TREE_H

#endif


template <class T>
class TreeNode {
private:
    T value;
    TreeNode parent;        //TODO: is treenode fine like this? only generic type is T value
    TreeNode<T> leftChild;
    TreeNode<T> rightChild;

public:
    TreeNode(T val, TreeNode<T> par) {
        value = val;
        parent = par;
        left = NULL;
        right = NULL;
    }

    // 
    TreeNode<T> GetLeftChild(TreeNode<T> node);         // returns a TreeNode's left Child
    TreeNode<T> AddLeftChild(T value);                  // returns the completed tree node

    TreeNode<T> GetRightChild(TreeNode<T> node);        // returns a TreeNode's right Child.
    TreeNode<T> AddRightChild(T value);

};

template<typename T>
TreeNode<T> TreeNode::GetLeftChild(TreeNode<T> node) {
    return node.left;
}

template<typename T>
TreeNode<T> TreeNode::AddLeftChild(T value) {
    this.left = new TreeNode<T>(value, this);
    return this.left;
}

template<typename T>
TreeNode<T> TreeNode::GetRightChild(TreeNode<T> node) {
    return node.right;
}

template<typename T>
TreeNode<T> TreeNode::AddRightChild(T value) {
    this.right = new TreeNode<T>(value, this);
    return this.right;
}
