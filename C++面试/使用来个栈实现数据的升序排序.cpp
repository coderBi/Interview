#include <iostream>
#include <stack>
using namespace std;

/*
问题描述：
	写一个算法：使用来个栈实现数据的升序排序。
分析：
	一个栈当做结果栈，里面的数据是从小到大进行排序的，而另一个栈是传入栈。我们可以先从传入栈中拿出一个元素，然后和结果栈中的最顶端的元素相比较，如果结果栈的顶端比较大就将结果栈的栈顶压入传入栈，一直压到合适的栈顶，然后将取出来的元素压入结果栈。重复这个步骤一直到传入栈为空，返回结果栈，整个算法结束。
*/

/**
* 将一个stack中的元素进行升序排序
*
* @param stack<int> src 要排序的栈
* @return stack<int> 排好序的栈
*/
stack<int> SortStack(stack<int> src){
	stack<int> result; //结果栈
	int tmp;
	while(!src.empty()){
		//取出输入栈的顶端元素
		tmp = src.top();
		src.pop();
		//将结果栈中比当前要插入的元素更大的都再压入输入栈
		while(!result.empty() && result.top() > tmp){
			src.push(result.top());
			result.pop();
		}
		//将元素插入到结果栈的栈顶，此时结果栈保持了升序
		result.push(tmp);
	}
	return result;
}


int main(){
	//测试
	stack<int> src, result;
	src.push(2);
	src.push(1);
	src.push(3);
	src.push(0);
	result = SortStack(src);
	//下面打印的结果是 { 3 2 1 0 }，因为栈是先进后出的，所以结果是逆序的。
	cout << "{";
	while(!result.empty()){
		cout << " " << result.top();
		result.pop();
	}
	cout << " }" << endl;
	return 0;
}