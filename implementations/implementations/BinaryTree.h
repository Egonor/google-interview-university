/*

//#include <queue>
using namespace std;

#pragma once

#ifndef BINARYTREE_H
#define BINARYTREE_H

template <class T>
class BinaryTree {
private:
    TreeNode<T>* root;
    
public:
    //BinaryTree();
    BinaryTree(T rootValue);

    void Print();

    TreeNode<T> Add(T toAdd);
    //bool AddFromVideo(T toAdd);
    TreeNode<T> Find(T toFind);
    //bool Delete(T toDelete);

    //TreeNode<T> preOrder(TreeNode<T>* node, T toFind);
    //TreeNode<T> postOrder(TreeNode<T>* node, T toFind);
    //TreeNode<T> inOrder(TreeNode<T>* node, T toFind);
    //TreeNode<T> levelOrder(TreeNode<T>* node, T toFind);
};
//
//template<typename T>    BinaryTree<T>::BinaryTree() {
//    root = new TreeNode<T>(NULL, NULL); 
//}

template<typename T>    BinaryTree<T>::BinaryTree(T rootValue) { 
    root = TreeNode<T>(rootValue, NULL); 
}

template<typename T>    void BinaryTree<T>::Print() {
    queue<TreeNode<T>> q = new list<TreeNode>();
    q.push(this->root);
    while (!q.empty()) {
        TreeNode<T> curr = q.pop();
        if (curr != NULL) {
            // curr.visit()
            printf("\n %d", curr.GetValue());
            q.add(curr.GetLeftChild());     // Could check if NULL before adding
            q.add(curr.GetRightChild());
        }
        return NULL; // redundant
    }
}

template<typename T>    TreeNode<T> BinaryTree<T>::Find(T toFind) {
    TreeNode<T> curr* = root;
    while (curr != NULL) {
        if (toFind < curr.GetValue())
            curr = curr.GetLeftChild();
        else if (toFind > curr.GetValue())
            curr = curr.GetRightChild();
        else
            return curr;
    }
    return NULL;
}
template<typename T>   TreeNode<T> BinaryTree<T>::Add(T toAdd) {
    TreeNode<T> curr* = root;
    while (curr != NULL) {
        if (toAdd < curr.GetValue()) {
            if (*curr.GetLeftChild() == NULL) {
                curr.AddLeftChild(toAdd);
                return curr.GetLeftChild();
            }
            else
                curr = curr.GetLeftChild();
        }            
        else if (toAdd > curr.GetValue()) {
            if (*curr.GetRightChild() == NULL) {
                curr.AddRightChild(toAdd);
                return curr.GetRightChild();
            }
            else
                curr = curr.GetRightChild();
        }            
        else
            std::exception("Value already exists!"); // Or we have weird string things happening
    }
    return NULL;
}

// Taken from https://www.coursera.org/learn/data-structures-optimizing-performance/lecture/u7J70/support-code-for-bst-s-insert-method
//template<typename T>    bool BinaryTree<T>::AddFromVideo(T toAdd) {
//    TreeNode<T> curr = this.root;
//    T val = curr.GetValue();
//    while (toAdd < val && curr.GetLeftChild() != NULL ||
//           toAdd > val && curr.GetRightChild() != NULL) 
//    {
//        if (toAdd < val)
//            curr = curr.GetLeftChild();
//        else
//            curr = curr.GetRightChild();
//        val = curr.GetValue();
//    }
//    if (val < 0)
//        curr.AddLeftChild(toAdd);
//    else if (val > 0)
//        curr.AddRightChild(toAdd);
//    else 
//        return false;
//    return true;
//}

//template<typename T>    bool BinaryTree<T>::Delete(T toDelete) {
//    TreeNode<T> del = Find(toDelete);
//}


//template<typename T>    TreeNode<T> BinaryTree<T>::preOrder(TreeNode<T>* node, T toFind) {
//    if (node != NULL) {
//        if (node.value == toFind) {
//            return node;
//        }
//        else {
//            preOrder(node.getLeftChild(), toFind);
//            preOrder(node.getRightChild(), toFind);
//        }
//    }
//    return NULL; // TODO: IS THIS CORRECT?
//}
//template<typename T>    TreeNode<T> BinaryTree<T>::postOrder(TreeNode<T>* node, T toFind) {
//    if (node != NULL) {
//        postOrder(node.getLeftChild(), toFind);
//        postOrder(node.getRightChild(), toFind);
//        if (node.value == toFind) {
//            return node;
//        }
//    }
//    return node; // node == NULL so redundant?
//}
//template<typename T>    TreeNode<T> BinaryTree<T>::inOrder(TreeNode<T>* node, T toFind) {
//    if (node != NULL) {
//        inOrder(node.getLeftChild(), toFind);
//        if (node.value == toFind) {
//            return node;
//        }
//        inOrder(node.getRightChild(), toFind);
//    }
//    return NULL;
//}
//template<typename T>    
//TreeNode<T> BinaryTree<T>::levelOrder(TreeNode<T>* node, T toFind) {
//    queue<TreeNode<T> q = new list<TreeNode<T>>();
//    q.push(this->root);
//    while (!q.empty()) {
//        TreeNode<T> curr = q.pop();
//        if (curr != NULL) {
//            // curr.visit()
//            if (curr.value == toFind) {
//                return curr;
//            }
//            else {
//                q.add(curr.GetLeftChild());     // Could check if NULL before adding
//                q.add(curr.GetRightChild());
//            }
//        }
//        return NULL; // redundant
//    }
//}

#endif

*/