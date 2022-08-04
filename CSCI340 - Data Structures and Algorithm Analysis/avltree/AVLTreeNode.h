#pragma once
#include <string>
// Class: TreeNode
// Purpose:  Represent the nodes of a binary search tree.  
//           Note that the fields Left and Right are exposed directly as properties. 
//           This is due to an inability to use properties as references.
//           Later modifications should include changes to address this
class AVLTreeNode
{
public:
	int Data;
	AVLTreeNode* Left;
	AVLTreeNode* Right;
	int Height;

	AVLTreeNode(int value)
	{
		Data = value;
		Left = nullptr;
		Right = nullptr;
		Height = -1;
	}

	bool IsLeaf()
	{
		return Left == nullptr && Right == nullptr;
	}

	bool HasBothSubTrees()
	{
		return Left != nullptr && Right != nullptr;
	}

	std::string ToString()
	{

		return std::to_string(Data);
	}
};