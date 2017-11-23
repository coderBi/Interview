#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;

/*
问题描述：
	栈的应用之后缀表达式：如何将一个中缀表达式转换为后缀表达式。一个后缀表达式，如何计算值。
后缀表达式计算值：
	后缀表达式的好处是完全不需要使用括号。后缀表达式是波兰人提出因此也称为逆波兰式。后缀表达式的计算可以使用一个栈，扫描表达式如果遇到了操作数就压入栈，如果遇到了操作符就从栈中取出两个操作数计算结果并且将结果重新压入栈。当整个表达式扫描结束的时候最后栈中留下的就是最终的结果。
关于中缀表达式转换后缀表达式：
	1）如果这个问题出在面试笔试中，可以使用一种加括号的方法，首先在中缀表达式上对不同优先级加上所有的括号，然后再将所有的操作符移到括号的后面，最后去掉所有的括号，就得到了所求的后缀表达式。例如 a+b*c+(d*e+f)*g，这个中缀加上括号的形式是((a + (b*c)) + (((d*e) + f)*g))，将所有操作符移动到括号的外部并且去掉括号为abc*+de*f+g*+。另一种在笔试中常见的方法是将中缀表达式对应的语法二叉树画出来，然后对这个树进行直接写出后缀。
	2）这个问题如果是要代码求解，那么一般可以使用两个栈，一个用来存放扫描到的操作符，另一个存放最终的结果(准确的说，这个结果是倒的)。当扫描到操作数的时候直接存入到结果栈中，当扫描到操作符的时候，如果操作符是左括号，那么直接入栈，如果是右括号就将所有的读到了左括号之前的操作符都压入结果栈，左括号出栈丢弃(实际上一对括号包裹的是一个同样的子问题)。对于操作符的优先级，如果读到的操作符的优先级比操作符栈中的更低或者一样那么要先计算前面的表达式，然后才能将当前的操作符入栈。当所有的扫描结束之后，如果操作符栈还有内容就全部出栈压入结果栈.
*/


/**
* 将一个中缀表达式的字符串转换为后缀表达式的字符串
*
* @param std::string str 传入的中缀表达式字符串
* @return std::string 获取到的后缀表达式字符串
*/
std::string InOrder2Post(std::string str){
	std::string toReturn;
	stack<char> op, result;
	map<char,int> priorities; //存放所有的操作符对应的优先级
	priorities['(']  = 0; //优先级最低
	priorities['+'] = priorities['-'] = 1;
	priorities['*'] = priorities['/'] = priorities['%']  = 2;

	//扫描
	auto end = str.end();
	char c;
	for(auto it = str.begin(); it != end; ++it){
		c = *it;
		switch(c){
			case '(':
				//左括号，直接压入操作符栈
				op.push(c);
				break;
			case ')':
				//将一对括号中还没有出栈的符号全部弹出，最后丢弃前面的左括号
				while(op.top() != '('){
					result.push(op.top());
					op.pop();
				}
				//弹出左括号
				op.pop();
				break;
			case '-':
			case '+':
			case '*':
			case '/':
			case '%':
				//是符号，那么将栈顶比当前符号优先级更高或者一样的符号先进行运算
				while(!op.empty() && priorities[op.top()] >= priorities[c]){
					result.push(op.top());
					op.pop();
				}
				//将当前的操作符压入操作符存储栈
				op.push(c);
				break;
			default:
				//是操作数，直接入结果栈
				result.push(c);
				break;
		}
	}
	//将操作符栈中还没有出栈的所有的操作符出栈
	while(!op.empty()){
		result.push(op.top());
		op.pop();
	}
	//将结果栈中字符依次读出，构成结果字符串
	while(!(result.empty())){
		toReturn.push_back(result.top());
		result.pop();
	}
	//将结果字符串翻转，因为栈中存放的结果读取到的是反的
	reverse(toReturn.begin(),toReturn.end());
	return toReturn;
}

int main(){
	//测试
	string s = "a+b*c+(d*e+f)*g";
	cout << InOrder2Post(s) << endl; //abc*+de*f+g*+
	return 0;
}