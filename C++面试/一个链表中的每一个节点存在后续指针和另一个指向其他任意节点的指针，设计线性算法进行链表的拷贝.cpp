#include <iostream>
using namespace std;

/*
问题描述：
	一个链表中每一个节点，除了保存一个后续元素的指针，还保存一个链表中的其他的元素的指针。对于这样的结构的链表，设计一个算法进行链表的拷贝。
分析：
	1)构建新的链表，可以依次遍历原来的链表，进行节点的拷贝和next指针的赋值，但是这里出现的一个问题是节点中存在的另一个指针可能指向了还没有构建出来的节点上，所以拷贝不能一步完成。考虑在创建完成拷贝链表的所有节点的情况下，如果依次遍历这个拷贝链表然后进行另一个指针的赋值，那么从原链表中的关系映射查找会出现一个二次复杂度的算法。如果在创建拷贝的链表的过程中，保留原节点和拷贝节点之间的映射关系为hash结构。这样可以将复杂度降为线程。
	2)实际上，在相关的书上可以找到不使用hash进行额外的空间开销也能实现线性的拷贝。方法是这样的，我们在拷贝节点的时候直接将每一个节点插入到原来的链表中的相应的节点的后面。这样就实现了一个类似的简单映射。在创建完成所有的节点拷贝节点之后，依次使用映射关系对拷贝节点的“另一个指针”进行赋值。然后，我们可以将所有的奇数位重组为原链表，而所有的偶数位重复为拷贝的结构(这里的重组指着的是重写修改每一个节点的next)。
*/

typedef struct Node
{
	int data;
	Node * next;
	Node * sibling; //另一个指针，保留链表中的任意节点的指针
} *PNode;

/**
* 拷贝一个指定格式的链表，这个链表中每一个节点除了拥有后续节点的指针还有一个指向其他任意元素的指针
*
* @param PNode src 要拷贝的链表
* @return PNode 拷贝得到的链表
*/
PNode CopyList(PNode src){
	if(!src)
		return nullptr;
	PNode p = src, q;
	//节点拷贝
	while(p){
		q = new Node;
		//将拷贝的节点插入到原节点的后面
		q->data = p->data;
		q->next = p->next;
		p->next = q;
		p = q->next;
	}
	//调整拷贝的节点的另一个指针
	for(p = src; p;){
		q = p->next; // 拷贝节点
		q->sibling = p->sibling->next;//映射关系
		p = q->next;
	}
	//调整next指针，将拷贝链表和原链表进行分离
	PNode toReturn = src->next;
	for(p = src; p; p = p->next){
		q = p->next;
		p->next = q->next;
		if(q->next)
			q->next =  q->next->next;
	}
	return toReturn;
}

void PrintList(PNode link){
	cout << "{";
	for(PNode p = link; p; p = p->next){
		//依次打印当前节点的值、后续节点的值、兄弟节点的值
		cout << " [ " << p->data << ", ";
		if(p->next)
			cout << p->next->data;
		cout << "; ";
		if(p->sibling)
			cout << p->sibling->data;
		cout << " ]";
	}
	cout << " }" << endl;
}

int main(){
	PNode n1 = new Node, n2 = new Node, n3 = new Node, n4 = new Node, n5 = new Node;
	n1->data = 1; n1->next = n2; n1->sibling = n2;
	n2->data = 2; n2->next = n3; n2->sibling = n2; 
	n3->data = 3; n3->next = n4; n3->sibling = n5;
	n4->data = 4; n4->next = n5; n4->sibling = n1;
	n5->data = 5; n5->next = nullptr; n5->sibling = n3;
	PrintList(n1); //{ [ 1, 2; 2 ] [ 2, 3; 2 ] [ 3, 4; 5 ] [ 4, 5; 1 ] [ 5, ; 3 ] }
	PNode cp = CopyList(n1);
	PrintList(cp); //{ [ 1, 2; 2 ] [ 2, 3; 2 ] [ 3, 4; 5 ] [ 4, 5; 1 ] [ 5, ; 3 ] }
	return 0;
}