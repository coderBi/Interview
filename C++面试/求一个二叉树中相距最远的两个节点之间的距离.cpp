#include <iostream>
using namespace std;

/*
问题描述：
	求一个二叉树中相距最远的两个节点之间的距离。两个节点之间的距离指的是连通这两个节点的路径上的路径长。
分析：
	两个最远的节点可以是一个节点在左子树，一个节点在右子树，也可能是两个节点都在同一个子树上。如果采用递归可以这样想：求解左右子树上的最远距离，然后求解通过根节点的最远距离。通过根节点的距离的计算应该是左右子树中的最深的节点分别通过根节点相遇。这样就会发现递归的过程中需要保留下来左右子树的高度和左右子树的距离这两个数据。我们可以设计一个算法这个算法的返回值是一个复杂结构，结构两个部分分别保存距离和高度。对于空树，高度这里可以认为是-1，距离也是-1，只有一个节点的树高度是0距离是0。
*/

struct DistanceAndHeight
{
	int height;
	int distance;
};

struct Node
{
	int data;
	Node * left, * right;
};

/**
* 同时获取一个二叉树的中的最远的两个节点的距离和这个二叉树的高度
* 
* @param Node * T   要获取数据的二叉树
* @return DistanceAndHeight 返回二叉树中最远的两个节点的距离和二叉树的高度组成的一个复合结构
*/
DistanceAndHeight GetDistanceAndHeight(Node * T){
	DistanceAndHeight dh;
	if(!T){
		//空树
		dh.height = -1;
		dh.distance = 0;
		return dh;
	}
	//求解左右子树的高度和距离
	DistanceAndHeight dhl = GetDistanceAndHeight(T->left),
					  dhr = GetDistanceAndHeight(T->right);
	//通过左右子树的高度来求解整个树的高度
	dh.height = 1 + (dhl.height > dhr.height ? dhl.height : dhr.height);
	//通过左右子树的高度来求解通过根节点的最远的两个节点的距离
	dh.distance = 2 + dhl.height + dhr.height; //分别加上的是左右子树到根节点的路径1
	if(dh.distance < dhl.distance)
		dh.distance = dhl.distance;
	if(dh.distance < dhr.distance)
		dh.distance = dhr.distance;
	return dh;
}

/**
* 获取一个二叉树的最远的两个节点的距离
*
* @paramn Node * T 要获取的二叉树
* @return int 返回二叉树中最远的两个节点的距离
*/
int GetDistance(Node * T){
	return GetDistanceAndHeight(T).distance;
}

int main(){
	//测试
	//准备测试数据：构建一棵树，左子树有两层，右子树有一层
	Node * t = new Node;
	t->left = new Node; t->right = new Node;
	Node * p = t->left;
	p->left = new Node; p->right = new Node;
	p = p->left;
	p->left = p->right = nullptr;
	p = t->left->right;
	p->left = p->right = nullptr;
	p = t->right;
	p->left = p->right = nullptr;

	cout << GetDistance(t) << endl; //3，会通过根节点
	return 0;
}