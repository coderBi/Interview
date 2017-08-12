#include <iostream>
#include <sstream> //sstream头文件中定了三个流 ostringstream istringstream stringsteam. 用流可以更好的操作普通类型与字符串类型的转换和连接等问题
using namespace std;

typedef int ElementType;

struct Node
{
	ElementType val;
	Node * left;
	Node * right;
};

typedef Node* BinaryTree;

/*
	C++11增加了一批的to_string()函数，这里由于MingW版本低，所以自己利用流实现以个to_string
*/
std::string to_string(int n){
	ostringstream stream;
	stream << n;
	return stream.str();
}

/*
	二叉树的先序遍历,递归实现
@param BinaryTree T 要遍历的二叉树
@return std::string 遍历之后得到的结果字符串
*/
std::string PreOrder(BinaryTree T){
	std::string toReturn  = "";
	if(!T)
		return toReturn; //空树
	//获取树根的值
	std::string root = to_string(T->val);
	//遍历左子树
	std::string left = PreOrder(T->left);
	//遍历右子树
	std::string right = PreOrder(T->right);
	//添加根节点的值
	toReturn += root;
	//添加左右子树到返回结果
	if(left.length())
		toReturn += string(" ") + left;
	if(right.length())
		toReturn += string(" ") + right;
	return toReturn;
}


/*
	二叉树的中序遍历,递归实现
@param BinaryTree T 要遍历的二叉树
@return const std::string & 遍历之后得到的结果字符串
*/
std::string InOrder(BinaryTree T){
	std::string toReturn = "";
	if(!T)
		return toReturn; //空树
	//遍历左子树
	std::string left = InOrder(T->left);
	//获取树根的值
	std::string root = to_string(T->val);
	//遍历右子树
	std::string right = InOrder(T->right);
	//添加左子树到返回结果
	toReturn = left;
	//添加根节点的值到返回结果
	if(toReturn.length())
		toReturn += " " + root;
	else
		toReturn += root;
	//添加右子树到返回结果
	if(right.length())
		toReturn += " " + right;
	return toReturn;
}


/*
	二叉树的后序遍历,递归实现
@param BinaryTree T 要遍历的二叉树
@return const std::string & 遍历之后得到的结果字符串
*/
std::string PostOrder(BinaryTree T){
	std::string toReturn = "";
	if(!T)
		return toReturn; //空树
	//获取树根的值
	std::string root = to_string(T->val);
	//遍历左子树
	std::string left = PostOrder(T->left);
	//遍历右子树
	std::string right = PostOrder(T->right);
	//添加左右子树到返回结果
	if(left.length()){
		if(toReturn.length())
			toReturn += " " + left;
		else
			toReturn += left;
	}
	if(right.length()){
		if(toReturn.length())
			toReturn += " " + right;
		else
			toReturn += right;
	}
	//添加树根
	if(toReturn.length())
			toReturn += " " + root;
		else
			toReturn += root;
	return toReturn;
}

/*
	添加一个节点得到二叉树，这里的二叉树类似于查找树（之所以是类似，因为对于值完全一样的节点这里也是创建了新的节点并且插入到相应根节点的左边），但是树是不平衡的
@param BianaryTree T 要插入的目标二叉树
@param ElementType val 新插入的节点的值
@return BinaryTree 插入节点之后的新的二叉树
*/
BinaryTree Insert(BinaryTree T, ElementType val){
	if(!T){
		//构造新节点
		BinaryTree p = new Node;
		if(!p){
			//构造新节点失败，错误处理
			cout << "create new node fail" << endl;
			return T;
		}
		p->val = val;
		p->left = p->right = NULL;
		return p; //原来的是空树，直接返回新创建的树
	}
	if(val <= T->val)
		T->left = Insert(T->left,val); //插入到左子树
	else
		T->right = Insert(T->right,val); //插入到右子树
	return T;
}

int main(){
	//构造测试树
	BinaryTree T = NULL;
	for(int i = 5; i >= 0; --i){
		T = Insert(T,i);
		T = Insert(T,10-i);
	}
	
	//打印先序遍历
	cout << "preorder: { " << PreOrder(T) << " }" << endl;
	//打印中序遍历
	cout << "inorder: { " << InOrder(T) << " }" << endl;
	//打印后序遍历
	cout << "postorder: { " << PostOrder(T) << " }" << endl;
	return 0;
}