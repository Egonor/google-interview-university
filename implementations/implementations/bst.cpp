#include "stdafx.h"
#include "bst.h"


// Helper function to create a new node...
// malloc(sizeof(struct BSTNode)
BSTNode* NewBstNode(BSTNode* parent, int value) {
        BSTNode* new_node = (BSTNode *)malloc(sizeof(BSTNode));
        //BSTNode* newNode = new BSTNode();
        // Assigned in struct BSTNode order
        new_node->parent = parent;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
}


// BST_Min/Max is Min/Max of Tree, not from a node (see BST_InOrderPredecessor)
BSTNode* BST_Min(BST tree) {
    if (tree.root == NULL)
        return NULL;
    while (tree.root->left != NULL) {
        tree.root = tree.root->left;
    }
        return tree.root;
}
BSTNode* BST_Max(BST tree) {
    if (tree.root == NULL)
        return NULL;
    while (tree.root->right != NULL) {
        tree.root = tree.root->right;
    }
    return tree.root;
}

// Height = number of edges between node and root
int BST_Height(BSTNode* root) {
    if (root == NULL)
        return -1;    
    return std::max(BST_Height(root->left), BST_Height(root->right)) + 1;
}

int BST_NodeCount(BSTNode* root) {
    int count = 0;
    if (root != NULL) {
        if (root->left != NULL)
            count += BST_NodeCount(root->left);
        if (root->right != NULL)
            count += BST_NodeCount(root->right);
        return count + 1;
    }
    else
        return count;
}

BSTNode* BST_Add(BST* tree, int value_to_add) {
    if (tree->root == NULL) {
        tree->root = NewBstNode(NULL, value_to_add);
        return tree->root;
    }

    // There will always be a null root node
    BSTNode* curr = tree->root;
    while (curr != NULL) {  // Loop until an empty slot is found in BST.
        if (value_to_add < curr->value) {
            if (curr->left == NULL) {
                curr->left = NewBstNode(curr, value_to_add);
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
        else if (value_to_add > curr->value) {
            if (curr->right == NULL) {
                curr->right = NewBstNode(curr, value_to_add);
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
}

bool BST_Delete(BST* tree, int value_to_delete) {
    BSTNode* node_to_delete = BST_Find(tree, value_to_delete);  // get node_to_delete to val_to_delete
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

BSTNode* BST_Find(BST* tree, int value_to_find) {
    BSTNode* cursor = tree->root;
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

// Need MCS_Min/Max because it works (finds min/max) from any node in the tree).
BSTNode* BST_InOrderPredecessor(BST* tree, int value) {
    BSTNode *current = BST_Find(tree, value);

    if (current == NULL)
        return NULL;
    if (current->left != NULL) {
        return MCS_Max(current->left); // TODO: rewrite to handle BST
    }
    else {
        BSTNode* parent = current->parent;
        while (parent != NULL && current == parent->left) {
            current = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

void BST_Print_LevelOrder(BST* tree) {
    std::queue<BSTNode *> q;
    q.push(tree->root);
    while (!q.empty()) {
        int current_size = (int)q.size();
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
void BST_Print_PreOrder(BSTNode* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        BST_Print_PreOrder(root->left);
        BST_Print_PreOrder(root->right);
    }
}
void BST_Print_InOrder(BSTNode* root) {
    if (root != NULL) {
        BST_Print_InOrder(root->left);
        printf("%d ", root->value);
        BST_Print_InOrder(root->right);
    }
}
void BST_Print_PostOrder(BSTNode* root) {
    if (root != NULL) {
        BST_Print_PostOrder(root->left);
        BST_Print_PostOrder(root->right);
        printf("%d ", root->value);
    }
}

// MYCODESCHOOL (Mostly recursion)
// https://www.youtube.com/watch?v=COZK7NATh4k&list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P&index=28

BSTNode* MCS_Min(BSTNode* root) {
    if (root == NULL)
        return NULL;
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
BSTNode* MCS_Max(BSTNode* root) {
    if (root == NULL) return NULL;

    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

BSTNode* MCS_Insert(BSTNode* root, int value_to_add) {
    if (root == NULL) {
        root = NewBstNode(NULL, value_to_add);
        return root;
    }
    else if (value_to_add <= root->value) {
        root->left = MCS_Insert(root->left, value_to_add);
    }
    else {
        root->right = MCS_Insert(root->right, value_to_add);
    }
    return root;
}
bool     MCS_Search(BSTNode* root, int value_to_find) {
    if (root == NULL)
        return false;
    else if (value_to_find == root->value)
        return true;
    else if (value_to_find < root->value)
        return MCS_Search(root->left, value_to_find);
    else  //(value_to_find > root->value)
        return MCS_Search(root->right, value_to_find);
}
BSTNode* MCS_Delete(BSTNode* root, int value) {
    if (root == NULL) return root;
    else if (value < root->value) root->left = MCS_Delete(root->left, value);
    else if (value > root->value) root->right = MCS_Delete(root->right, value);
    else    // Found Node
    {
        // Case: No Child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }
        else if (root->left == NULL) {
            BSTNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL) {
            BSTNode *temp = root;
            root = root->left;
            delete temp;
        }
        else {
            BSTNode *temp = MCS_Min(root->right);
            root->value = temp->value;
            root->right = MCS_Delete(root->right, temp->value);
        }
        return root;
    }
}

bool MCS_BstUtil(BSTNode* root, int min, int max) {
    // Doesn't handle duplicates
    if (root == NULL) return true;

    if (root->value > min &&
        root->value < max &&
        MCS_BstUtil(root->left, min, root->value) &&
        MCS_BstUtil(root->right, root->value, max))
        return true;
    else
        return false;
}
bool MCS_isBST(BSTNode* root) {
    return MCS_BstUtil(root, INT_MIN, INT_MAX);
}

BSTNode* MCS_Successor(BST* tree, int value) {
    // Ben: Modified to use tree instead of root node source.
    // Ben: Algorithm doesn't use parent pointers.
    // Find the node: O(h)
    BSTNode* current = BST_Find(tree, value);
    if (current == NULL) return NULL;
    // Case 1: Node has right subtree
    if (current->right != NULL) {       // O(h)
        return MCS_Min(current->right); // Min in right subtree
    }
    // Case 2: No right subtree
    else {
        BSTNode* successor = NULL;
        BSTNode* ancestor = tree->root;
        while (ancestor != current) {
            if (current->value < ancestor->value) {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else {
                ancestor = ancestor->right;
            }
        }
        return successor;
    }
}
// END OF MYCODESCHOOL
