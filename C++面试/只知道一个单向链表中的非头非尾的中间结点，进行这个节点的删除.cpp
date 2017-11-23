#include <iostream>
using namespace std;

/*
题目描述：
	如果只知道一个单向链表中的非头非尾的中间结点，写一个算法，从链表中删除这个节点。
分析：
	因为是中间节点，可以巧妙的将这个节点和其后续节点的内容进行互换(又因为后序节点要删除，所以这种互换只需要将后序节点的内容赋给当前节点)，然后再删除后续的那个节点，这样将当前的节点的next重置就完成了删除。考虑这个算法可以发现如果传入的节点是尾节点或者是null，那么这个算法是没有办法正常工作的。题目中已经说了传入的非头非尾，保证了算法的可行性。
*/

struct Node
{
	int data;
	Node * next;
};

/**
* 在只知道一个非头非尾的中间节点的情况下，删除这个节点
*
* @param Node * item  要删除的节点
* @return bool  成功删除一个元素返回true 否则返回false
*/
bool DeleteMiddle(Node * item){
	if(!item || !item->next)
		return false;
	Node * next = item->next;
	item->data = next->data;
	item->next = next->next;
	delete next; //删除后续节点
	return true;
}

/**
* 打印单向链表
*
* @param Node* head 待打印的链表的头
*/
void PrintLinkedList(Node* head){
	std::cout << "[ ";
	while(head){
		std::cout << head->data << " ";
		head = head->next;
	}
	std::cout << "]" << std::endl;
}

int main(){
	//测试
	Node * head = new Node();
	head->data = 1; head->next = nullptr;
	Node * item = new Node;
	head->next = item; item->data = 2; item->next = nullptr;
	Node * tail = new Node;
	item->next = tail; tail->next = nullptr; tail->data = 3;
	//删除之前
	PrintLinkedList(head); //[ 1 2 3 ]
	cout << "删除结果: " << DeleteMiddle(item) << endl; //1
	cout << "删除结果: " << DeleteMiddle(nullptr) << endl; //0
	//删除后
	PrintLinkedList(head); //[ 1 3 ]
	return 0;
}