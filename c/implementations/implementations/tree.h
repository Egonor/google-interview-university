#include "stdafx.h"

#pragma once

#ifndef TREE_H
#define TREE_H



template <class T>
class TreeNode {
private:
    T value;
    TreeNode<T>* parent;        //TODO: Why can I access these from BinaryTree?
    TreeNode<T>* leftChild;
    TreeNode<T>* rightChild;

public:
    TreeNode();
    TreeNode(T val, TreeNode<T> par);

    T GetValue();

    // 
    TreeNode<T> GetLeftChild();                         // returns a TreeNode's left Child
    TreeNode<T> GetRightChild();                        // returns a TreeNode's right Child.

    TreeNode<T> AddLeftChild(T value);                  // returns parent of added TreeNode
    TreeNode<T> AddRightChild(T value);                 // returns parent of added TreeNode

};

template<typename T>    TreeNode<T>::TreeNode() {

}

template<typename T>    TreeNode<T>::TreeNode(T val, TreeNode<T> par) {
    value = val;
    parent = par;
    leftChild = NULL;
    rightChild = NULL;
};


template<typename T>    T TreeNode<T>::GetValue() { return value; }

template<typename T>    TreeNode<T> TreeNode<T>::GetLeftChild()  { return leftChild;  }
template<typename T>    TreeNode<T> TreeNode<T>::GetRightChild() { return rightChild; }

template<typename T>    TreeNode<T> TreeNode<T>::AddLeftChild(T value) {
    leftChild = TreeNode<T>(value, this);
    return this;
}
template<typename T>    TreeNode<T> TreeNode<T>::AddRightChild(T value) {
    rightChild = TreeNode<T>(value, this);
    return this;
}


#endif