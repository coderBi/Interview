#include <iostream>
#include <vector>
using namespace std;

/*
问题描述：
	一个二叉树上面每一个节点上存放一个int，寻找所有满足路径上的节点的和是一个给定的int的路径。这个路径节点不需要一定通过根节点或者是叶节点。
分析：
	如果使用递归的思路，可以这样考虑，要根节点的时候在左右子树寻找sum减去根节点的值，不要根节点的时候在左右子树寻找sum。这个算法的复杂度个人推出来的是n*n。
*/

struct Node
{
	int data;
	Node *left, * right;
};

/**
* 在一个已经确定了一部分路径的前提下，在一个子树上寻找节点和是某一个sum的的路径
* 
* @param Node *T 要操作的二叉子树
* @param int sum 要寻找的节点值之和
* @param std::vector<int> valuesAdded 在进入这个子树之前已经确定保存了的节点
*/
void FindRouteImpl(Node * T, int sum, std::vector<int> valuesAdded){
	if(!T)
		return;
	if(!valuesAdded.size()){
		//已经保存的节点值的集合为空，那么可以在左右子树中寻找满足和为sum的路径
		FindRouteImpl(T->left, sum, valuesAdded);
		FindRouteImpl(T->right, sum, valuesAdded);
	}

	valuesAdded.push_back(T->data);
	//判断路径
	if(T->data == sum){
		//打印路径
		std::cout << "{";
		for(auto item = valuesAdded.begin(); item != valuesAdded.end(); item++){
			std::cout << " " << *item;
		}
		std::cout << " }" << std::endl;
	}
	//采用当前的根节点的前提下，在左右子树寻找sum-T->data
	FindRouteImpl(T->left, sum - T->data, valuesAdded);
	FindRouteImpl(T->right, sum - T->data, valuesAdded);
}

/**
* 在一个二叉树上面寻找节点的和是某一个整数的所有路径
* 
* @param Node * T 要查询的二叉树
* @param int sum 节点值构成的目标和
*/
void FindRoute(Node * T, int sum){
	std::vector<int> v;
	FindRouteImpl(T, sum, v);
}

/**
* 从下向根节点查找路径上节点值的和是某一个int的所有路径
*
* @param Node * T 当前查找到的二叉树子树
* @param int sum 要计算的目标和
* @param std::vector<int> valuesFromRoot 记录的是从根节点向下到当前节点之前的路径节点的值
*/
void FindRouteFromBottom2Top(Node *T, int sum, std::vector<int> valuesFromRoot){
	if(!T)
		return;
	valuesFromRoot.push_back(T->data);
	//从当前的元素向后根节点回溯
	int size = valuesFromRoot.size();
	int sum1 = sum; //另存一个值在循环里面使用
	for(int i = size -1; i >= 0; i--){
		sum1 -= valuesFromRoot[i];
		if(!sum1){
			//打印路径
			std::cout << "{";
			for(int j = i; j <= size -1; j++){
				std::cout << " " << valuesFromRoot[j];
			}
			std::cout << " }" << endl;
		}
	}
	//向下一层递归
	FindRouteFromBottom2Top(T->left, sum, valuesFromRoot);
	FindRouteFromBottom2Top(T->right, sum, valuesFromRoot);
}

int main(){
	//准备测试数据：构建一棵树，这个树根节点下有两个节点，每一个子节点下面有存在两个子节点，一共存在三层。
	Node * t = new Node;
	t->data = 0; t->left = new Node; t->right = new Node;
	Node * p = t->left;
	p->data = 2; p->left = new Node; p->right = new Node;
	p = p->left;
	p->data = 3; p->left = p->right = nullptr;
	p = t->left->right;
	p->data = 4; p->left = p->right = nullptr;
	p = t->right;
	p->data = 1; p->left = new Node; p->right = new Node;
	p = p->left;
	p->data = 5; p->left = p->right = nullptr;
	p = t->right->right;
	p->data = 6; p->left = p->right = nullptr;

	/*
	结果为：
		{ 2 4 }
		{ 6 }
		{ 1 5 }
		{ 0 2 4 }
		{ 0 1 5 }
	*/
	FindRoute(t, 6);

	cout << "------- 测试分割线-------" << endl;

	/*
	结果为：
		{ 2 4 }
		{ 0 2 4 }
		{ 1 5 }
		{ 0 1 5 }
		{ 6 }
	*/
	FindRouteFromBottom2Top(t, 6, std::vector<int>());
	return 0;
}