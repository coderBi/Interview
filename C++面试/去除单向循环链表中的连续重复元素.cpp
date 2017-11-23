#include <iostream>
using namespace std;

/*
问题描述：
	一个单向循环链表，设计一个算法去除连续的重复元素。
分析：
	1)首先从头到尾（这里指的是下一次回到头之前）遍历，如果后一个元素和前面的元素的内容重复就删除后一个元素，这里存在两个指针，一个保存前一个元素一个保存后一个元素。如果进行了后一个元素的删除，那么前一个元素的指针维持不变，否则两个指针都会进行后移。
	2)其次，一直删除到最后一个元素，再次回到头节点的时候，如果最后一个元素的内容与头结点重复了，那么会删除头结点，然后整个链表返回的头结点发生了改变。这个时候如果要保留返回的头结点不变，而是删除最后一个重复元素，可以知道由于是单向链表，需要保留删除的尾节点的前一个元素，而这种保留对于之前遍历去重操作来说是不一致的，是麻烦的。所以总体来看，这里如果是尾节点和头结点重复了，最方便的做法是删除头结点。

*/

typedef struct Node
{
	int data;
	Node * next;
} *PNode;


/**
* 去除一个单向循环链表中的连续重复元素
*
* @param PNode link 要删除的链表
* @return PNode 返回删除之后的循环链表
*/
PNode RemoveDuplicate(PNode link){
	if(!link)
		return link;
	PNode p = link, q = link->next, tmp = nullptr; //分别为前一个元素，后一个元素
	while(q != link){
		tmp = q->next;
		if(q->data == p->data){
			//去重，删除后续元素
			delete q;
			p->next = tmp;
		}else{
			p = q;
		}
		q = tmp;
	}
	//q为传入的头节点，p为尾部节点，处理这种特殊情况
	if(q == p){
		//特殊情况，q和p重合了，表示这个链表中原先所有的元素都是一样的
		return p;
	}
	if(q->data == p->data){
		p->next = q->next;
		delete q;
		return p;
	}
	return link; //返回传入的头结点
}

void PrintList(PNode link){
	if(!link){
		cout << "{the list is empty}" << endl;
		return;
	}
	cout << "{ " << link->data;

	for(PNode next = link->next; next != link; next = next->next){
		cout << " " << next->data;
	}
	cout << " }" << endl;
}

int main(){
	//测试
	PNode n1 = new Node, n2 = new Node, n3 = new Node, n4 = new Node, n5 = new Node;
	n1->data = 1; n1->next = n2;
	n2->data = 3; n2->next = n3;
	n3->data = 3; n3->next = n4;
	n4->data = 2; n4->next = n5;
	n5->data = 1; n5->next = n1;
	PrintList(n1); //{ 1 3 3 2 1 }
	n1 = RemoveDuplicate(n1);
	PrintList(n1); //{ 1 3 2 }，第一个元素对应的是n5
	return 0;
}