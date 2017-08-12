#include <iostream>
using namespace std;

typedef int ElementType; /*利用抽象的数据结构，方便一会可能进行的修改和复用*/

struct Node
{
	ElementType val;
	Node * previous;
	Node * next;
};

struct DoubleLinkedList
{
	Node * head;
	Node * tail;
};

/*
	按照值删除元素
@param DoubleLinkedList* L 要操作的链表
@param ElementType val 要删除的值
@version 1.0 功能性实现
@version 2.0 细节优化：由于是双向链表，所以不用向单链表那样，删除之前还需要保存上一个节点。这里去除掉循环里面的previous保存
*/
void DeleteByVal(DoubleLinkedList * L, ElementType val){
	if(!L)
		return;
	Node *p = L->head, *previous = NULL, *next = NULL;
	for(;p && val != p->val; p = p->next){
		//version 2.0 双向链表不用保存了
		//previous = p; //保存要删除节点的前一个节点
	}
	if(p){
		//找到了值，进行删除
		next = p->next;
		previous = p->previous;  //version 2.0
		if(previous)
			previous->next = next;
		else
			L->head = next; //删除的是头节点，需要修改头结点指针
		if(next)
			next->previous = previous;
		else
			L->tail = previous; //删除的是尾节点，需要修改尾部指针
		//删除p
		delete p;
	}
}

/*
	按照值删除掉所有的符合的元素
@param DoubleLinkedList* L 要操作的链表
@param ElementType val 要删除的值
@version 1.0 功能性实现
@version 2.0 细节优化：由于是双向链表，所以不用向单链表那样，删除之前还需要保存上一个节点。这里去除掉循环里面的previous保存
*/
void DeleteAllByVal(DoubleLinkedList * L, ElementType val){
	if(!L)
		return;
	Node *p = L->head, *previous = NULL, *next = NULL;
	for(;p; p = next){
		next = p->next;
		if(val == p->val){
			//找到了值，进行删除
			previous = p->previous; //version 2.0
			if(previous)
				previous->next = next;
			else
				L->head = next; //删除的是头节点，需要修改头结点指针
			if(next)
				next->previous = previous;
			else
				L->tail = previous; //删除的是尾节点，需要修改尾部指针
			//删除p
			delete p;
		}
		/*verson 2.0 双向链表，没有保留上一个节点的必要 
		else{
			//保存上一个p
			previous = p;
		}
		*/
	}
}

/*
	 构造一个双向链表
@return DoulbeLinkedList* 创建好的链表，如果创建失败返回NULL
*/
DoubleLinkedList* CreateDoubleLinkedList(){
	DoubleLinkedList * L = new DoubleLinkedList;
	if(!L)
		return NULL; //创建失败
	L->head = L->tail = NULL;
	return L;
}

/*
	在链表的尾部添加一个值
@param DoubleLinkedList *L 被添加的目标链表
@param ElementType val 要添加的元素的值
@return bool 如果添加成功返回true，添加失败返回false
*/
bool Push_Back(DoubleLinkedList * L, ElementType val){
	if(!L)
		return false; //参数传递错误，没有预先创建好链表
	//创建新节点
	Node *p = new Node;
	p->val = val;
	p->next = p->previous = NULL;
	if(!p)
		return false;  //创建新节点失败
	//添加新节点
	if(!L->tail){
		//链表中之前没有元素，所以新的元素是新的链表头和链表尾
		L->head = L->tail = p;
	}else{
		//添加到尾部，并且修改为新的尾节点
		L->tail->next = p;
		p->previous = L->tail;
		L->tail = p;
	}
	return true;
}

/**/
void PrintDoubleLinkedList(DoubleLinkedList * L){
	if(!L){
		cout << "{}" << endl;
		return;
	}
	cout << "{ ";
	for(Node * p = L->head; p; p = p->next){
		cout << p->val << ' ';
	}
	cout << "}" << endl;;
}

int main(){
	//构造链表
	DoubleLinkedList * L = CreateDoubleLinkedList();
	if(!L){
		//创建失败，错误处理
		cout << "create DoubleLinkedList fail" << endl;
		return -1;
	}
	//添加一批新元素
	for(int i = 0; i < 10; ++i){
		if(!Push_Back(L,i)){
			//添加一个节点错误，进行错误处理
			cout << "Push_Back fail" << endl;
			return -1;
		}
	}
	//打印原始链表
	PrintDoubleLinkedList(L);
	//删除
	DeleteByVal(L,5);
	//打印删除之后的链表
	PrintDoubleLinkedList(L);

	//进一步测试，删除头和尾和不存在的元素
	DeleteByVal(L,5); //删除不存在元素
	DeleteByVal(L,0); //删除头
	DeleteByVal(L,9); //删除尾
	//打印删除之后的链表
	PrintDoubleLinkedList(L);

	//进一步测试，删空整个结构
	for(int i = 0; i < 10; ++i){
		DeleteByVal(L,i);
	}
	//打印删除之后的链表
	PrintDoubleLinkedList(L);
	return 0;
}