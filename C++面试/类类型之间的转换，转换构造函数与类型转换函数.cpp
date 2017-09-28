#include <iostream>
using namespace std;

/*
题目描述：
	实现对象类型之间的转换，主要有哪些方式
分析：
	1）如果是子类与父类之间，子类对象可以对父类的引用或者指针进行初始化，子类对象也可以直接对一个父类对象进行赋值，这是那种转换都是隐式的转换。而父类对象的引用或者指针到子类对象的引用或者指针的转换是需要进行显式的转换的。父类的对象不能直接转换为子类的对象，即使是强制转换也不可以。
	2）如果两个对象不存在继承的关系，那么可以使用转换构造函数转换，也可以使用类型转换函数进行转换。具体的，类型构造函数指的是这个构造函数存在唯一参数（后面如果还有其他的参数，应该有默认值），这个参数的类型是要转换的源类型。而类型转换函数的定义是一个成员函数，这个函数没有参数，不指定返回值类型，但是在这个函数的名称是(operator + 要转换到的另一个类型的类型名)（这个类型也可以是基本数据类型）而且函数体内部需要返回一个目标类型的变量.
	3）可以使用explicit修饰转换构造函数，那么这个构造函数只能显式调用，而不能用作隐式的转换表达式，也即是说（B  b = a）如果相应的构造函数被explicit修饰，那么这个表达式会编译通不过。
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
	virtual void func(){
		cout << "B... " << x << endl;
	}
};


class C
{
public:
	int x = 222;
	virtual void func(){
		cout << "C... " << x << endl;
	}
	C(){}
	//转换构造函数
	C(const B& b){
		x = b.x;
	}
	//类型转换函数，没有返回值，但是需要返回一个要转换到的目标类型的对象
	operator B(){
		B temp;
		temp.x = x;
		return temp;
	}
	//到基本类型的转换
	operator int(){
		return  x;
	}
};


class D
{
public:
	int x = 6666;
	virtual void func(){
		cout << "D... " << x << endl;
	}
	D(){}
	//使用explicit修饰转换构造函数，这样就先定了这个构造函数不能用于隐式转换（也就是不能直接 D d = b;）
	explicit D(const B& b){
		x = b.x;
	}
};

int main(){
	/*在子类与父类之间转换*/
	B b;
	A & a = b; //子类对象初始化父类引用，可以隐式转换
	a.func(); //B...111
	B & d = (B&)a; //子类引用到父类引用需要进行强制转换
	d.func();

	/*没有继承关系类型之间的转化*/
	C c = b; //使用构造函数转换
	c.func();
	B b2 = c; //使用C类中的类型转换函数，将其中的临时对象赋给这里的B对象
	b2.func();

	//到基本类型的转换
	cout << (int)c << endl;

	//使用explicit修饰转换构造函数，禁止隐式转换
	D d1(b); //直接显示调用构造函数，可行
	d1.func();
	D d2 = b; //隐式转换，由于使用了explicit修饰相应的转换构造函数，所以这里会出现编译错误：conversion from B to non-scalar type D
	return 0;
}