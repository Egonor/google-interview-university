#include "stdafx.h"
#include "bst.h"

// Helper function to create a new node...
// malloc(sizeof(struct BSTNode)
BSTNode* NewBstNode(BSTNode* parent, int value) {
        BSTNode* new_node = (BSTNode *)malloc(sizeof(BSTNode));
        // Assigned in struct BSTNode order
        new_node->parent = parent;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
}

BSTNode* AddToTree(BST* tree, int toAdd) {
    // There will always be a null root node
    BSTNode* curr = &tree->root;


    while (curr != NULL) {  // Loop until an empty slot is found in BST.
        if (toAdd < curr->value) {
            if (curr->left == NULL) {
                curr->left = NewBstNode(curr, toAdd);
                return curr->left;

                //BSTNode *l = (BSTNode*)malloc(sizeof(BSTNode)); // this goes away when scope closes?
                //l->value = toAdd;
                //l->parent = curr;
                //curr->left = l; // if we setup l as a pointer (*l) it is "uninitialized"
                //return l;   // if we return it does it stay? or only if we assign the return value
            }
            else {
                curr = curr->left;
            }
        }
        else if (toAdd > curr->value) {
            if (curr->right == NULL) {
                curr->right = NewBstNode(curr, toAdd);
                return curr->right;
            }
            else
                curr = curr->right;
        }
        else {
            // value already exists
            return NULL;
        }
    }
    // Set root here?
}

BSTNode* AddToTreeCoursera(BST* tree, int toAdd) {
    BSTNode *curr = &tree->root;
    int val = curr->value;
    while (toAdd < val && curr->left != NULL ||
            toAdd > val && curr->right != NULL)
    {
        if (toAdd < val)
            curr = curr->left;
        else
            curr = curr->right;
        val = curr->value;
    }
    if (val < toAdd) {
        BSTNode* l = NewBstNode(curr, toAdd);
        curr->left = l;
        return l;
    }
    else if (val > toAdd) {
        BSTNode* r = NewBstNode(curr, toAdd);
        curr->left = r;;
        return r;
    }
    else
        return NULL;  // Value already exists in BST.
}

BSTNode* Find(BST* tree, int value_to_find) {
    BSTNode* cursor = &tree->root;
    while (cursor != NULL) {
        if (value_to_find < cursor->value)
            cursor = cursor->left;
        else if (value_to_find > cursor->value)
            cursor = cursor->right;
        else
            return cursor;
    }
    return NULL; // Not Found
}
                                                                                
// free(BSTNode)
bool DeleteFromTree(BST* tree, int value_to_delete) {
    BSTNode* node_to_delete = Find(tree, value_to_delete);      // get node_to_delete to val_to_delete
    if (node_to_delete != NULL) {                               // val actually found
        // to_delete has two children
        if (node_to_delete->left != NULL &&
            node_to_delete->right != NULL) {
            // Find smallest value in right subtree            
            BSTNode* smallest = node_to_delete->right;
            while (smallest->left != NULL) {
                smallest = smallest->left;
            }
            // Replace deleted node's value with smallest
            node_to_delete->value = smallest->value;

            // delete right subtree duplicate
            node_to_delete = smallest->parent;
            node_to_delete->right = smallest->right;
            free(smallest);  // This jumps over and then frees smallest.
            return true;
        }
        else if (node_to_delete->left != NULL) {
            // check is necessesary to know which side of the parent we deleted
            if (value_to_delete < node_to_delete->parent->value)
                node_to_delete->parent->left = node_to_delete->left;
            else // (value > parent's value) so put it on parent's right child
                node_to_delete->parent->right = node_to_delete->left;

            node_to_delete->left->parent = node_to_delete->parent;
            free(node_to_delete);
            return true;
        }
        else if (node_to_delete->right != NULL) {
            if (value_to_delete < node_to_delete->parent->value)
                node_to_delete->parent->left = node_to_delete->right;
            else
                node_to_delete->parent->right = node_to_delete->right;

            node_to_delete->right->parent = node_to_delete->parent;
            free(node_to_delete);
            return true;
        }
        else {
            if (value_to_delete < node_to_delete->parent->value)
                node_to_delete->parent->left = NULL;
            else
                node_to_delete->parent->right = NULL;

            free(node_to_delete);
            return true;
            /* Old code
            node_to_delete = node_to_delete->parent;
            if (value_to_delete < node_to_delete->value) {
                free(node_to_delete->left);
                node_to_delete->left = NULL;
                return node_to_delete;
            }
            else {
                free(node_to_delete->right);
                node_to_delete->right = NULL;
                return node_to_delete;
            }*/   
        }
    }
    else {
        // Value not in tree.
        return false;
    }
}

void PrintTree(BST* tree) {
    std::queue<BSTNode *> q;
    q.push(&tree->root);
    while (!q.empty()) {
        int current_size = q.size();
        for (int i = 0; i < current_size; ++i) {
            BSTNode* curr = q.front();
            q.pop();
            if (curr != NULL) {
                if (curr->value != NULL)
                    printf("%d ", curr->value);
                if (curr->left != NULL)
                    q.push(curr->left);
                if (curr->right != NULL)
                    q.push(curr->right);
            }
        }
        printf("\n");
    }    
}