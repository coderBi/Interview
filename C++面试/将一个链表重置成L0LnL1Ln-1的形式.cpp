#include <iostream>
using namespace std;

/*
题目描述
	给定一个单向链表：(L0,L1,L2,....,Ln-1,Ln),写一个程序将这个链表重新排序成(L0,Ln,L1,Ln-1....)
节点结构：
	struct Node{
		int vaL;
		Node* next;
	}
要求：
	空间复杂度为O(1)
	对于一个节点，只有".next"属性可以被修改
*/

struct Node
{
	int vaL;
	Node * next;
};

/*
	将一个单向链表(L0,L1,L2,....,Ln-1,Ln)重新排序成(L0,Ln,L1,Ln-1....)形式
@param struct Node * L 待重排序的链表头
@return struct Node *  重排序之后返回的链表头
*/
Node * ReorderList(Node * L){
	if(!L)
		return NULL;
	Node * next = L->next;
	Node * tail = next, *pre = NULL;
	for(;tail && tail->next; tail = tail->next)
		pre = tail;
	L->next = tail;
	if(pre)
		pre->next = NULL;
	else
		next = NULL;  //如果pre为NULL 将next设置为NULL，否则next与q重合，进行了重复的计算
	next = ReorderList(next);
	if(tail)
		tail->next = next;
	return L;
}

/*
	打印链表
@param Node * L 待打印的链表头
*/
void PrintList(Node * L){
	for(Node * p = L; p; p = p->next)
		cout << p->vaL << ' ';
	cout << endl;
}

int main(){
	//测试
	//构造链表
	Node * L = NULL, *p = NULL, *q = NULL;
	L = new Node;
	L->next = NULL; L->vaL = 1;
	int i = 2;
	for(p = L; i <= 10; p = p->next){
		q = new Node;
		q->vaL = i++;
		q->next = NULL;
		p->next = q;
	}
	
	//打印之前的数据
	PrintList(L);
	
	//重排链表
	L = ReorderList(L);

	//打印之后的数据
	PrintList(L);
	return 0;
}