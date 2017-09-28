#include <iostream>
using namespace std;

/*
问题描述：
	下面的代码有什么问题，其中A是B的父类
	B b;
	A * pa = &b;
	delete pa;
分析：
	编译通过，会出现运行时错误，因为栈上空间不能通过delete释放(注意，与free类似，在变量delete之后应该置空，对于空指针（不能直接将nullptr传入，要传指针测试）的delete不会进行任何操作)。
*/

class A
{
public:
	int x = 111;
	virtual void func(){
		cout << "A... " << x << endl;
	}
};

class B : public A
{
public:
	int x = 222;
	virtual void func(){
		cout << "B... " << x << endl;
	}
};

int main(){
	B b;
	A * pa = &b;
	cout << pa->x << endl; //这一行代码如果没有下面的delete好像并没有报错，个人的分析是编译器的一种优化方案，就是b这个对象的初始化（真正的执行）在使用其中的元素之前是有延后的。
	delete pa; //编译没有问题，按照说明栈上空间不能使用delete释放否则会出现运行是问题。但是这里测试没有问题，可能是进行了优化.(补充说明，经过多次的测试，发现有时候会崩有时候不会，具体的问题有待分析)
	cout << pa->x << endl;
	return 0;
}