#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;

/*
问题描述：
	用递归的思路实现单向链表的反序打印
分析：
	先打印头节点后面的节点，然后打印头节点.
补充：
	这同时给出不用递归反序打印的算法。一般来说递归对于数据规模稍微大一点的问题可能不是很合适
*/

template<class T> struct S
{
	T value;
	S * next;
};

/*
	递归实现单向链表的反序打印
*/
template<class T> void PostOrderPrintLinkedList(S<T> * s){
	assert(nullptr != s);
	//打印头节点的后面部分
	if(s->next)
		PostOrderPrintLinkedList(s->next);
	//打印头结点
	std::cout << s->value << std::endl;
}

/*
	非递归实现单向链表的反序打印
*/
template<class T> void PostOrderPrintLinkedListImplementedWithNoRecursion(S<T> * s){
	assert(nullptr != s);
	stack<T> result;
	//遍历链表，将值依次存入栈
	while(s){
		result.push(s->value);
		s = s->next;
	}
	//遍历栈 将结果依次输出
	while(!result.empty()){
		std::cout << result.top() << std::endl;
		result.pop();
	}
}

int main(){
	S<int> * s = new S<int>[3]();
	if(!s){
		cerr << "create struct failed" << endl;
		return -1;
	}
	for(int i = 0; i < 2; i++){
		s[i].value = i + 1;
		s[i].next = s + i + 1;
	}
	s[2].value = 3;

	//测试
	PostOrderPrintLinkedList(s);
	PostOrderPrintLinkedListImplementedWithNoRecursion(s);
	delete [] s;
	return 0;
}