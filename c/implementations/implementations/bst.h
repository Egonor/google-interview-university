#pragma once

#ifndef BST_H
#define BST_H

// Written "C-like" because I got annoyed with templates.

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
BSTNode* BST_Min(BST tree);                             // good
BSTNode* BST_Max(BST tree);                             // good
int BST_Height(BSTNode* root);                          // good
int BST_NodeCount(BSTNode* root);                       // good

BSTNode* BST_Add(BST* tree, int value_to_add);          // good
bool     BST_Delete(BST* tree, int value_to_delete);    // good
BSTNode* BST_Find(BST* tree, int value);                // good

BSTNode* BST_InOrderPredecessor(BST* tree, int value);

void BST_Print_LevelOrder(BST* tree);
void BST_Print_PreOrder(BSTNode* root);
void BST_Print_InOrder(BSTNode* root); // good
void BST_Print_PostOrder(BSTNode* root);

// MyCodeSchool
BSTNode* MCS_Min(BSTNode* root);
BSTNode* MCS_Max(BSTNode* root);
BSTNode* MCS_Insert(BSTNode* root, int value_to_add);
bool     MCS_Search(BSTNode* root, int value_to_find);
BSTNode* MCS_Delete(BSTNode* root, int value);
bool MCS_isBST(BSTNode* root);
BSTNode* MCS_Successor(BST* tree, int value);


#endif