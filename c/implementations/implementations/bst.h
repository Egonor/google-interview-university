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
    BSTNode root;
} typedef BST;

BSTNode* NewBstNode(BSTNode* par, int value);
BSTNode* AddToTree(BST* tree, int value_to_add);
BSTNode* AddToTreeCoursera(BST* tree, int value_to_add);

bool DeleteFromTree(BST* tree, int value_to_delete);

BSTNode* Find(BST* tree, int value);

void PrintTree(BST* tree);


#endif