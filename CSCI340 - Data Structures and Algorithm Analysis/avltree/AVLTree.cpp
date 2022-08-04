#include <vector>
#include <sstream>
#include <iostream>
#include <list>
#include <string> 
#include <cmath>

#include "AVLTreeNode.h"
#include "AVLTree.h"

using namespace std;


// Public methods

void AVLTree::Insert(int val)
{
	if (_root == nullptr)
	{
		_root = new AVLTreeNode(val);
	}
	else
	{
		Insert(_root, val);
	}
}

int AVLTree::Height(AVLTreeNode* node)
{
	if (node != nullptr)
	{
		return node->Height >=0 ? node->Height : -1;
	}
	return -1;
}

void AVLTree::InOrder(void(*f)(int))
{
	InOrder(_root, f);
}

void AVLTree::PrintTree()
{
	PrintTree(_root, nullptr, false);
}


// Private Methods
void AVLTree::Insert(AVLTreeNode*& node, int val)
{
	if (node == nullptr)
	{
		node = new AVLTreeNode(val);
	}
	else if (val < node->Data)
	{
		Insert(node->Left, val);
	}
	else if (val >= node->Data)
	{
		Insert(node->Right, val);
	}

	Balance(node);
}

int Max(int x, int y)
{
	return x > y ? x : y;
}

void AVLTree::RotateLeft(AVLTreeNode*& k2)
{
	AVLTreeNode* k3 = k2->Left;
	k2->Left = k3->Right;
	k3->Right = k2;
	k2->Height = Max(Height(k2->Left), Height(k2->Right)) + 1;
	k3->Height = Max(Height(k3->Left), k2->Height) + 1;
	k2 = k3;
}

void AVLTree::RotateRight(AVLTreeNode*& k1)
{
	AVLTreeNode* k2 = k1->Right;
	k1->Right = k2->Left;
	k2->Left = k1;
	k1->Height = Max(Height(k1->Left), Height(k1->Right)) + 1;
	k2->Height = Max(Height(k2->Right), k1->Height) + 1;
	k1 = k2;
}

void AVLTree::DoubleRotateRightLeft(AVLTreeNode*& k3)
{
	RotateRight(k3->Left);
	RotateLeft(k3);
}

void AVLTree::DoubleRotateLeftRight(AVLTreeNode*& k1)
{
	RotateLeft(k1->Right);
	RotateRight(k1);
}

void AVLTree::Balance(AVLTreeNode*& node)
{
	if (node == nullptr)
	{
		return;
	}

	if (Height(node->Left) - Height(node->Right) > 1)
	{
		if (Height(node->Left->Left) >= Height(node->Left->Right))
		{
			RotateLeft(node);
		}
		else
		{
			DoubleRotateRightLeft(node);
		}
	}
	else if (Height(node->Right) - Height(node->Left) > 1)
	{
		if (Height(node->Right->Right) >= Height(node->Right->Left))
		{
			RotateRight(node);
		}
		else
		{
			DoubleRotateLeftRight(node);
		}
	}

	node->Height = Max(Height(node->Left), Height(node->Right)) + 1;
}

void AVLTree::InOrder(AVLTreeNode* node, void(*f)(int))
{
	if (node == nullptr)
	{
		return;
	}
	InOrder(node->Left, f);
	f(node->Data);
	InOrder(node->Right, f);
}


// Helper function to print branches of the binary tree
void showTrunks(Trunk* p)
{
	if (p == nullptr)
		return;

	showTrunks(p->prev);

	cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void AVLTree::PrintTree(AVLTreeNode* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr)
		return;

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	PrintTree(root->Left, trunk, true);

	if (!prev)
		trunk->str = "---";
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else
	{
		trunk->str = "`---";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << root->Data << endl;

	if (prev)
		prev->str = prev_str;
	trunk->str = "   |";

	PrintTree(root->Right, trunk, false);