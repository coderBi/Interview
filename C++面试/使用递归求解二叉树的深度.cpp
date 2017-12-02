#include <iostream>
#include <algorithm>
using namespace std;

/*
问题描述：
	使用递归求解二叉树的深度。
分析：
	一个二叉树的深度是根节点到树叶的路径中的最长者。如果使用递归求解深度，二叉树的深度等于根节点的左右子树的深度的较大者然后加1.
*/

typedef struct Node
{
	int data;
	Node *left, *right;
} *PNode;

int GetHeight(PNode T){
	if(!T)
		return -1; //空树的高度是-1，注意这种写法下，第一层根节点的深度是0，表示第0层。但是对于根节点有的书上说的是第1层，有的书上说的是第0层，这里存在理解上的小差异。
	return 1 + std::max(GetHeight(T->left), GetHeight(T->right));
}

int main(){
	//测试
	PNode t = new Node;
	t->left = new Node; t->right = nullptr;
	t->left->left = t->left->right = nullptr;
	cout << GetHeight(t) << endl; //1
	return 0;
}