#include <iostream>
using namespace std;

struct Element{
	int val;
	Element * next;
};

/*
	打印一个链表的内容
@param Element * L  待打印的链表
*/
void PrintLinkedList(Element * L){
	Element * e = L;
	while(e){
		cout << e->val << " ";
		e = e->next;
	}
	cout << endl;
}

/*
	合并两个有序链表
思路：
	从设置两个变量从开头遍历两个链表L1,L2，如果L1的元素小于L2就将L1中的元素添加到新的链表中，同时L1的指针向后移动，否则如果L2中的元素小于L1中的就将L2中的元素添加到新的链表中并且将L2的指针后移。
	如果两个链表中的元素大小相同，那么将L1中的元素添加到新的链表中，并且将L1和L2中的指针都向后移动。
	L1、L2中只要有一个指针移动到末尾为NULL就将另一个链表中的剩余元素追加到新的链表中.
@param Element* L1 待合并的链表1
@param Element* L2 待合并的链表2
@return Element* 返回合并之后的新链表（头）
*/
Element* MergeSortedLists(Element* L1, Element* L2){
	Element *p1 = NULL, *p2 = NULL;
	Element * toReturn = NULL; //新的链表头
	
	//为了不在循环里面反复的判断新的头是否为NULL，这里先设置一个哑元为新的链表头，后面在返回之前将这个哑元删除并且修改为真实的链表头
	toReturn = new Element;
	toReturn->next = NULL;
	Element * e = toReturn;

	//遍历两个链表，将筛选之后的元素添加到新链表
	for(p1 = L1, p2 = L2; p1 && p2;){
		if(p1->val < p2->val){
			//添加L1中元素到新链表
			e->next = p1;
			e = p1;
			p1 = p1->next;
		}else if(p1->val > p2->val){
			//添加L2中元素到新链表
			e->next = p2;
			e = p2;
			p2 = p2->next;
		}else {
			//添加L1中元素到新链表，将L1、L2中的指针同时后移
			e->next = p1;
			e = p1;
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	//将剩余的元素追加到新链表
	while(p1){
		e->next = p1;
		e = p1;
		p1 = p1->next;
	}
	while(p2){
		e->next = p2;
		e = p2;
		p2 = p2->next;
	}
	
	//删除表头的哑元，将表头重置为真实的第一个元素
	e = toReturn;
	toReturn = toReturn->next;
	delete e;

	return toReturn;
}

int main(){
	//构建两个链表
	Element * L1 = new Element, *L2 = new Element;
	L1->val = 1;
	L2->val = 2;
	Element *tail1 = L1, *tail2 = L2, *e = NULL;
	for(int i = 1; i < 5; ++i){
		//填充链表1
		e = new Element;
		e->val = 2*i + 1;
		tail1->next = e;
		tail1 = e;
		//填充链表2
		e = new Element;
		e->val = 2 + 2*i;
		tail2->next = e;
		tail2 = e;
	}
	//添加一个相同的尾巴
	e = new Element; e->next = NULL; e->val = 100;
	tail1->next = e; tail1 = e;
	e = new Element; e->next = NULL; e->val = 100;
	tail2->next = e; tail2 = e;

	//测试
	//输出原来的两个链表
	PrintLinkedList(L1);
	PrintLinkedList(L2);
	//合并
	Element * newL = MergeSortedLists(L1, L2);
	//输出合并之后的链表
	PrintLinkedList(newL);
	return 0;
}