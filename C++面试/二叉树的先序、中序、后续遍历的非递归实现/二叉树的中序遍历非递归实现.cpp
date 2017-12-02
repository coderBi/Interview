#include <iostream>
#include <stack>
using namespace std;

/*
问题描述：
	给出二叉树的非递归的形式的先序、中序、后续遍历代码
分析：
先序分析：
	先序的访问顺序是先根节点然后左子树（访问左子树必定先要访问左子节点），待整个左子树访问完毕之后再去访问整个右子树（访问右子树必定先访问右子节点）。所以可以先从根节点开始一直e->left访问所有的左边的节点，在这个过程中使用栈保存所有的e->right（除非为空不保存），然后当e->left为空的时候就说明要访问上一个保存的right节点，这个时候从栈中取出最近的一个right节点，然后可以视为把它当做一个“根节点”重复上面的步骤，整个循环结束的条件是e->left为空了并且栈为空取不出来元素了。
中序分析：
	中序和先序有点类似，但是中序应该首先将根节点和e->left一直到空的节点都保存到栈。如果e->left为空了就从栈中取出来一个节点进行访问，然后将这个节点的右子节点当做“根节点”重复进行上述操作，如果右子节点为空或者访问结束就从栈中取出下一个节点。循环结束的条件是节点指针e->right为空并且栈中没有元素可以取出。
后序遍历分析：
	首先，和中序一样，将根节点和e->left全部进行保存到栈。当e->left为空的时候可以认为一个左子树访问完毕，这个时候从栈中取出一个元素，去访问其右子树，对于右子树的访问，因为可以认为是一个递归，所以可以套入一个循环中只是调整“根节点”。当右子树访问完毕之后，就可以访问栈中之前取出来的元素，然后将其从栈中移除，移除这个操作可以认为是一个“左子树”的访问完毕(这个时候可以把循环中的e置空，效果可以认为是将一个左子树看做了null)。重复上面的过程一直到最后一个将e置为null并且栈中没有元素。现在分析一个麻烦问题：因为在从栈中取出一个元素如果其右子树不为空，那么先要访问其右子树，也就是这个时候这个元素是仍然保存在栈中的，那么其右子树访问完毕之后，再取到这个元素的时候如何避免重复又去访问其右子树。这个问题是后序遍历与另两种遍历的相比的麻烦所在（因为节点是后与其右子树得到访问，节点在访问右节点之前是不能出栈的）。解决这个问题的一个好的解决方案是，设置一个指针变量，保存每一次访问的节点。因为一个节点的右子节点是紧邻它之前的一个访问元素，那么在访问一个节点之前只需要查看该节点的右子节点是否是保存的最近访问节点就知道是否该将这个元素出栈了。
*/

struct Node
{
	int data;
	Node *left, * right;
};

/**
* 使用非递归的方式，进行中序遍历二叉树
*
* @param Node *T 要遍历的二叉树
*/
void InOrderWithoutRecursion(Node * T){
	std::stack<Node*> s; //用于保存后续要访问的左子树(左子节点)
	Node * p = T;
	std::cout << "{";
	while(p || !s.empty()){
		if(p){
			//将p压入栈
			s.push(p);
			p = p->left;
		}else{
			//p为空，从栈中取出一个节点访问，然后将指针置到右子树(因为先序和中序遍历，在访问完毕一棵子树之后p一定为null)
			p = s.top();
			s.pop();
			std::cout << " " << p->data;
			p = p->right;
		}
	}
	std::cout << " }" << std::endl;
}

int main(){
	//测试
	//准备测试数据：构建一棵树，这个树根节点下有两个节点，每一个子节点下面有存在两个子节点，一共存在三层。每一次的存放的数据依次为0~6
	Node * t = new Node;
	t->data = 0; t->left = new Node; t->right = new Node;
	Node * p = t->left;
	p->data = 1; p->left = new Node; p->right = new Node;
	p = p->left;
	p->data = 3; p->left = p->right = nullptr;
	p = t->left->right;
	p->data = 4; p->left = p->right = nullptr;
	p = t->right;
	p->data = 2; p->left = new Node; p->right = new Node;
	p = p->left;
	p->data = 5; p->left = p->right = nullptr;
	p = t->right->right;
	p->data = 6; p->left = p->right = nullptr;

	InOrderWithoutRecursion(t); //{ 3 1 4 0 5 2 6 }
	return 0;
}