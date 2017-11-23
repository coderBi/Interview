#include <iostream>
#include <stack>
using namespace std;

/*
测试目的：
	查看stl中的stack的拷贝是否是深拷贝
结果：
	通过测试，可以知道stack类的拷贝构造函数进行深拷贝的处理。两个stack的直接赋值是一种深拷贝。
*/

int main(){
	stack<int> s, p;
	s.push(1);
	cout << s.size() << endl; //1
	p = s;
	cout << p.size() << endl; //1 深拷贝
	s.pop(); 
	cout << s.size() << endl; //0
	cout << p.size() << endl; //1 stl中的stack的拷贝是深拷贝

	s.push(2);
	s.push(3);
	s.push(4);
	cout << s.size() << endl; //3
	cout << p.size() << endl; //1

	cout << p.top() << "..." << s.top() << endl; //1...4
	return 0;
}