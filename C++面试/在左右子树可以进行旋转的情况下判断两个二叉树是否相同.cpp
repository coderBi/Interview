#include <iostream>
using namespace std;

/*
问题描述：
	两颗二叉树，在左右子树可以进行旋转的情况下，如果判断两个二叉树是否相同。
分析：
	如果是书写递归，这个会从语意上很容易完成，首先判断当前给的两个根节点是否相同，然后判断左右子树是否都相等（因为涉及到旋转，所以会有两种情况一种是左边对左边一种是左边对应另一颗树的右边）.
*/

struct Node
{
	int data;
	Node *left, * right;
};

/**
* 在二叉树的左右子树可以旋转的情况下，判读两个二叉树是否相同
*
* @param Node * T1 比较的二叉树1
* @param Node * T2 比较的二叉树2
* @return bool 如果两个二叉树相同返回true，否则返回false 
*/
bool Equal(Node * T1, Node * T2){
	if(!T1 && !T2)
		//两个都是空树
		return true;
	else if(!T1 || !T2)
		//其中只有一个是空树
		return false;
	if(T1->data == T2->data){
		return Equal(T1->left, T2->left) && Equal(T1->right, T2->right) ||
				Equal(T1->left, T2->right) && Equal(T1->right, T2->left);
	}else{
		//根节点的值不一样
		return false;
	}
}

int main(){
	//测试
	Node * t1 = new Node, * t2 = new Node;
	t1->left = new Node, t1->right = new Node;
	t1->data = 0;
	t1->left->left = t1->left->right = t1->right->left = t1->right->right = nullptr;
	t1->left->data = 1, t1->right->data = 2;
	t2->left = new Node, t2->right = new Node;
	t2->data = 0;
	t2->left->left = t2->left->right = t2->right->left = t2->right->right = nullptr;
	t2->left->data = 1, t2->right->data = 2;

	cout << boolalpha << Equal(t1, t2) << endl; //true

	t2->right->data = 1, t2->left->data = 2; //旋转
	cout << boolalpha << Equal(t1, t2) << endl; //true

	t2->right->data = 3;
	cout << boolalpha << Equal(t1, t2) << endl; //false
	return 0;
}