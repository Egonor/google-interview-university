#include "tree.h"
//#include <queue>
using namespace std;

#pragma once

#ifndef BINARYTREE_H
#define BINARYTREE_H

#endif


template <class T>
class BinaryTree {
private:
    TreeNode<T> root;
    TreeNode<T> preOrder(TreeNode<T> node, T toFind);
    TreeNode<T> postOrder(TreeNode<T> node, T toFind);
    TreeNode<T> inOrder(TreeNode<T> node, T toFind);
    TreeNode<T> levelOrder(TreeNode<T>, T toFind);)
};

template <typename T>
TreeNode<T> BinaryTree<T>::preOrder(TreeNode<T> node, T toFind) {
    if (node != NULL) {
        if (node.value == toFind) {
            return node;
        }
        else {
            preOrder(node.getLeftChild(), toFind);
            preOrder(node.getRightChild(), toFind);
        }
    }
    return NULL; // TODO THIS CORRENT?
}

template <typename T>
TreeNode<T> BinaryTree<T>::postOrder(TreeNode<T> node, T toFind) {
    if (node != NULL) {
        postOrder(node.getLeftChild(), toFind);
        postOrder(node.getRightChild(), toFind);
        if (node.value == toFind) {
            return node;
        }
    }
    return node; // node == NULL so redundant?
}

template <typename T>
TreeNode<T> BinaryTree<T>::inOrder(TreeNode<T> node, T toFind) {
    if (node != NULL) {
        inOrder(node.getLeftChild(), toFind);
        if (node.value == toFind) {
            return node;
        }
        inOrder(node.getRightChild(), toFind);
    }
    return NULL;
}

template <typename T>
TreeNode<T> BinaryTree<T>::levelOrder(TreeNode<T>, T toFind) {
    queue<TreeNode<T>> q = new list<TreeNode>();
    q.push(this->root);
    while (!q.empty()) {
        TreeNode<T> curr = q.pop();
        if (curr != NULL) {
            // curr.visit()
            if (curr.value == toFind) {
                return curr;
            }
            else {
                q.add(curr.GetLeftChild());     // Could check if NULL before adding
                q.add(curr.GetRightChild());
            }
        }
        return NULL; // redundant
    }
}
