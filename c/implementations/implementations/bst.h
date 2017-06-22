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
    BSTNode* root;
} typedef BST;

BSTNode* NewBstNode(BSTNode* parent, int value);
BSTNode* BST_Add(BST* tree, int value_to_add);
bool     BST_Delete(BST* tree, int value_to_delete);
BSTNode* BST_Find(BST* tree, int value);

int BST_NodeCount(BSTNode* root);

void BST_Print_LevelOrder(BST* tree);
void BST_Print_PreOrder(BSTNode* root);
void BST_Print_InOrder(BSTNode* root);
void BST_Print_PostOrder(BSTNode* root);

// MyCodeSchool
BSTNode* BST_Insert(BSTNode* root, int value_to_add);
bool BST_Search(BSTNode* root, int value_to_find);

BSTNode* BST_Min(BSTNode* root);
int BST_Max(BSTNode* root);
int BST_Height(BSTNode* root);

bool is_BST(BSTNode *root);




#endif