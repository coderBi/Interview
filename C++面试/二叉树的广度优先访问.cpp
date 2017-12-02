#include <iostream>
#include <queue>
using namespace std;

/*
问题描述：
	二叉树的广度优先访问算法
分析：
	利用给队列，首先将根节点放入队列。然后进入一个循环：只要队列不为空，从队列取出一个元素，访问这个元素的内容，然后将这个元素的左右节点都插入到队列中。当循环结束的时候就访问到了整个树。
*/

struct Node
{
	int data;
	Node *left, *right;
};

/**
* 对一个二叉树进行广度优先访问
*
* @param Node *T 要访问的二叉树
*/
void WideFirst(Node * T){
	if(!T)
		return;
	std::queue<Node*> q;
	Node * t = nullptr;
	q.push(T);
	std::cout << "{";
	while(!q.empty()){
		//访问节点的内容
		t = q.front();
		std::cout << " " << t->data;
		//将节点的左右节点都插入队列
		if(t->left)
			q.push(t->left);
		if(t->right)
			q.push(t->right);
		//节点访问完毕，从度列中移除
		q.pop();
	}
	cout << " }" << endl;
}

int main(){
	//测试
	Node * t = new Node;
	t->data = 0; 
	t->left = new Node;
	Node * p = t->left;
	p->data = 1;
	p->left = new Node;
	p->right = nullptr;
	p = p->left;
	p->data = 3;
	p->left = p->right = nullptr;
	t->right = new Node;
	p = t->right;
	p->data = 2;
	p->left = p->right = nullptr;
	WideFirst(t); //{ 0 1 2 3 }
	return 0;
}