#include <iostream>
#include <assert.h>
using namespace std;

struct Node
{
	char data;
	Node *left, *right;
};


Node * GetTreeFromPreOrderAndInOrderSequenceImpl(const std::string & preOrder, std::string inOrder, int & count){
	if(!inOrder.length())
		//中序序列为空，表示这个分支为空
		return nullptr;
	Node * root = new Node;
	if(!root){
		std::cerr << "内存申请失败" << std::endl;
		return nullptr;
	}
	//读取先序序列的第一个元素，为根元素的内容
	assert(preOrder.length()); //这里如果先序是空的其实一个异常，因为中序不是空的，说明传入的序列有问题
	root->data = preOrder[count];
	count++; //先序中已经查询了的元素个数加一 
	//在中序序列中寻找根元素的值
	int inLength = inOrder.length();
	int pos;
	for(pos = 0; pos < inLength; ++pos){
		if(inOrder[pos] == root->data)
			break;
	}
	//递归构建左右子树
	root->left = GetTreeFromPreOrderAndInOrderSequenceImpl(preOrder, inOrder.substr(0, pos), count);
	root->right = GetTreeFromPreOrderAndInOrderSequenceImpl(preOrder, inOrder.substr(pos + 1), count);
	return root;
}

Node * GetTreeFromPreOrderAndInOrderSequence(const std::string & preOrder, std::string inOrder){
	int count = 0;
	return GetTreeFromPreOrderAndInOrderSequenceImpl(preOrder, inOrder, count);
}

std::string GetPostOrder(Node * T){
	std::string result = "";
	if(!T)
		return result;
	result += GetPostOrder(T->left);
	result += GetPostOrder(T->right);
	result += T->data;
	return result;
}

int main(){
	cout << GetPostOrder(GetTreeFromPreOrderAndInOrderSequence("fbacdegh","abdcefgh")); //adecbhgf
	return 0;
}