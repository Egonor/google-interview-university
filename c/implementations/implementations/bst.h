#pragma once

#ifndef BST_H
#define BST_H

// ***********************NOTES*************************
// Written "C-like" because I got annoyed with templates.
// TODO: Reimplement/Cleanup. My code uses Tree, MCS uses root.
//       Either way is fine but using both together is confusing/cumbersome.
// *It's difficult to write a tree without specific (a problem's) constraints.

struct BSTNode {
    BSTNode* parent = NULL;
    int value = NULL;
    BSTNode* left = NULL;
    BSTNode* right = NULL;
} typedef BSTNode;


struct BST {
    BSTNode* root = NULL;
} typedef BST;

//BSTNode* NewBstNode(BSTNode* parent, int value);

// ***Can use the MCS_isBstUtil pattern to "fake" accessing 

                                                        // TESTED:
BSTNode* BST_Min(BST tree);                             // good
BSTNode* BST_Max(BST tree);                             // good
int BST_Height(BSTNode* root);                          // good
int BST_NodeCount(BSTNode* root);                       // good

BSTNode* BST_Add(BST* tree, int value_to_add);          // good
bool     BST_Delete(BST* tree, int value_to_delete);    // good
BSTNode* BST_Find(BST* tree, int value);                // good

BSTNode* BST_InOrderPredecessor(BST* tree, int value);  // good

void BST_Print_LevelOrder(BST* tree);                   // good
void BST_Print_PreOrder(BSTNode* root);                 // good
void BST_Print_InOrder(BSTNode* root);                  // good
void BST_Print_PostOrder(BSTNode* root);                // good

// MyCodeSchool
BSTNode* MCS_Min(BSTNode* root);                        // good
BSTNode* MCS_Max(BSTNode* root);                        // good
BSTNode* MCS_Insert(BSTNode* root, int value_to_add);   // ...
bool     MCS_Search(BSTNode* root, int value_to_find);  // ...
BSTNode* MCS_Delete(BSTNode* root, int value);          // ...
bool MCS_isBST(BSTNode* root);                          // ***Important
BSTNode* MCS_Successor(BST* tree, int value);           // ***Important


#endif