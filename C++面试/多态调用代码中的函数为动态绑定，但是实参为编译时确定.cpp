#include <iostream>
using namespace std;

/*
要点：
	1）虽然函数在父类和子类之间存在多态性，如果是父类的指针或者引用指向子类对象，那么如果存在多态就会调用子类中的方法。
	2）但是对于调用代码中的实参的却是在编译阶段进行的（在执行的时候进行动态绑定，然后利用这里的实参对相应的绑定到的函数的形参进行赋值）。
*/

class A{
public:
	virtual void func(int num = 10){
		cout << "A, num : " << num << endl;
	}
};
class B: public A{
public:
	virtual void func(int num = 211){
		cout << "B, num : " << num << endl;
	}
};

int main(int argc, char* argv[]){
	B b;
	A & a = b;
	//func函数由于存在多态的原因，所以使用父类的引用进行调用实际动态绑定的是子类中的函数。但是对于调用的函数的参数（这里是默认参数）的绑定则是在编译阶段就已经绑定好了的。所以这里的参数传入的是10。因为在编译的阶段a.func()的参数已经确定了。
	a.func(); //打印结果是B, num : 10

	//指针调用，和引用调用一样
	A *p = &b;
	p->func(); //指针调用和引用调用一样，这输出B, num:10
	return 0;
}