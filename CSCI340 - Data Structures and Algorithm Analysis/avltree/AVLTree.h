#include "AVLTreeNode.h"
#include "Trunk.h"
#pragma once

class AVLTree
{
public:
	void Insert(int val);
	int Height(AVLTreeNode* node);	
	void InOrder(void (*f)(int));
	void PrintTree();


private:
	AVLTreeNode* _root = nullptr;
	void Insert(AVLTreeNode*& node, int val);
	void RotateLeft(AVLTreeNode*& k2);
	void RotateRight(AVLTreeNode*& k1);
	void DoubleRotateRightLeft(AVLTreeNode*& k3);
	void DoubleRotateLeftRight(AVLTreeNode*& k1);
	void Balance(AVLTreeNode*& node);	
	void InOrder(AVLTreeNode* node, void (*f)(int));
	void PrintTree(AVLTreeNode* root, Trunk* prev, bool isLeft);
};

