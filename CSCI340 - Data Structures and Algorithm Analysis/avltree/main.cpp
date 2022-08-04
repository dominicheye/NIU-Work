#include <iostream>
#include "AVLTree.h"

using namespace std;

void print(int x)
{
	cout << x << endl;
}
int main()
{	
	AVLTree tree;

	int input = 0;
	cout << "Enter number:";
	cin >> input;
	while (input!=-1)
	{
		tree.Insert(input);
		tree.PrintTree();
		cout << "Enter number:";
		cin >> input;		
	}
	
	//tree.InOrder(print);
	tree.PrintTree();
}
