#include <iostream>
using namespace std;

/*
问题描述：
	不使用递归，实现单向链表的反序
分析：
	单向链表的反序，如果使用递归，是先将head->next反序，然后将head追加到这个反序结果的最后面。如果不使用递归，那么可以保留一个prev记录下一次操作节点要重置的next属性，然后遍历整个链表，依次重置整个链表所有节点的next属性即可。
*/
typedef int ElementType;
typedef struct Node{
	ElementType value;
	Node* next;
} *PNode;

/**
* 使用递归进行单向链表的反序
*
* @param PNode head 要反序的链表的头
* @return PNode 返回反序之后的新链表的头
*/
PNode ReverseUseRecursion(PNode head){
	if(!head || !head->next)
		return head;
	PNode next = head->next, subLink = nullptr;
	subLink = ReverseUseRecursion(next); //获取除了头节点的后续子链表的反序
	//将头结点添加到最终的结果上
	next->next = head;
	head->next = nullptr;
	return subLink;
}

/**
* 不使用递归进行单向链表的反序
*
* @param PNode head 要反序的链表的头
* @return PNode 返回反序之后的新链表的头
*/
PNode ReverseNoRecursion(PNode head){
	PNode prev = nullptr, next = head, tmp = nullptr;
	while(next){
		tmp = next->next;
		next->next = prev;
		prev = next;
		next = tmp;
	}
	return prev;
}

/**
* 打印单向链表
*
* @param PNode head 待打印的链表的头
*/
void PrintLinkedList(PNode head){
	std::cout << "[ ";
	while(head){
		std::cout << head->value << " ";
		head = head->next;
	}
	std::cout << "]" << std::endl;
}
int main(){
	//测试
	PNode head = new Node[5];
	for(int i = 0; i < 5; ++i){
		head[i].value = i + 1;
		head[i].next = head + i + 1;
	}
	head[4].next = nullptr;
	PrintLinkedList(head); //[ 1 2 3 4 5 ]
	head = ReverseUseRecursion(head);
	PrintLinkedList(head); //[ 5 4 3 2 1 ]
	head = ReverseNoRecursion(head);
	PrintLinkedList(head); //[ 1 2 3 4 5 ]
	return 0;
}