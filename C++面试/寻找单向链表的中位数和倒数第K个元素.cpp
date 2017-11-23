#include <iostream>
using namespace std;

/*
问题描述：
	给出一个单向链表，如果通过快慢指针操作寻找其中的中位数或者是寻找倒数第K个元素。
分析：
1）对于寻找中位数，可以用一个快指针设置为步长为2，一个慢指针设置为步长为1，这样当快指针为null或者是快指针的next为null的时候慢指针就指向了中位数。这个结果分析如下：假设快指针停止的时候慢指针走了x步，如果快指针停止的时候快指针本身是null，那么一共存在节点1+2x-1，这个时候慢指针停在了1+x的位置，可以得到这种情况下总的节点数的是偶数，这个时候慢指针的前一位是中位数。另一种情况，如果快指针停止的时候快指针的next为null，那么总的节点数1+2x,而慢指针停在了1+x的位置，所以慢指针这个时候返回的就是中位数。对于总的节点数是偶数的情况，上面指出多移动了一次慢指针，而单向链表中指针回倒是麻烦的，一个简单的方法是在循环的时候记录下慢指针的前一个节点。
2）对于寻找倒数第K的元素，我们可以用两个步长为1的指针看，第一个指针先走K步，如果在这之前这个指针到达了null说明一共存在的元素不到K个。当第一个指针走了k步之后，然另一个指针从链表的起始位置开始走，然后在第一个指针到达null的时候另一个指针停在的位置就是倒数第K个元素（两个指针一直相差K，而其中一个停在了null，可以从null假设为0往回数K）。
*/

typedef struct Node
{
	int data;
	Node * next;
} *PNode;

/**
* 获取一个单向链表的中位数

* @param PNode head 要获取中位数的链表
* @return PNode 返回中位数的指针，如果链表是空的就返回nullptr
*/
PNode GetMedian(PNode head){
	PNode slow = head, fast = head, pre = head; 
	while(fast && fast->next){
		pre = slow; //记录下慢指着的前一个元素
		fast = fast->next->next;
		slow = slow->next;
	}
	if(!fast)
		return pre; //快指针最后到了null，说明链表节点数为偶数，这个时候返回的是慢指针最终位置的前一个节点
	return slow;
}

/**
* 获取一个单向链表中的倒数第K个 元素
*
* @param PNode head 要获取中位数的链表
* @param int k 要获取的位置k
* @return 返回倒数第K个元素，如果整个链表的长度不足K那么会返回nullptr
*/
PNode GetLastKElement(PNode head, int k){
	PNode slow = head, fast = head;
	int i = 0;
	while(i < k && fast){
		i++;
		fast = fast->next;
	}
	if(i < k){
		//整个链表的长度是小于K的
		return nullptr;
	}
	while(fast){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

int main(){
	//测试
	PNode head = new Node;
	PNode p = head;
	for(int i = 0; i < 5; ++i){
		p->next = new Node;
		p->data = i;
		p = p->next;
	}
	p->next = nullptr; p->data = 5;

	//测试寻找中位数
	PNode result = GetMedian(head);
	if(!result)
		cout << "链表为空，无中位数" << endl;
	else
		cout << "第一次寻找中位数的结果是：中位数的索引为 " << result->data << endl; //2，寻找的序列是0~5
	result = GetMedian(head->next);
	if(!result)
		cout << "链表为空，无中位数" << endl;
	else
		cout << "第二次寻找中位数的结果是：中位数的索引为 " << result->data << endl; //3，寻找的序列是1~5

	//测试寻找倒数第K个元素
	result = GetLastKElement(head, 2);
	if(!result)
		cout << "链表的长度过短，小于传入的K" << endl;
	else
		cout << "第一次寻找，找到的倒数第K的位置索引是： " << result->data << endl; //4
	result = GetLastKElement(head, 7);
	if(!result)
		cout << "链表的长度过短，小于传入的K" << endl; //链表长度小于7
	else
		cout << "第二次寻找，找到的倒数第K的位置索引是： " << result->data << endl;
	return 0;
}