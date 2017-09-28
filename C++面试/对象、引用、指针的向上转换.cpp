#include <iostream>
using namespace std;

/*
题目描述：
	对象类型、指针、引用的三种形式的向上转换
分析：
	1）对象的向上转换，是直接将一个对象中的子对象取出来进行赋值。这样获取到的是一个全新的父类对象（其中不包含任何的子类的成员）, 所以这个获取到的对象调用跟直接new一个对象没有任何的区别。
	2）对象的引用或者指针的向上转换，涉及到可能存在的虚表问题，如果父类中存虚函数，那么转换之后，函数的调用由于会查询虚表而存在多态效应。
*/

class Parent
{
public:
	int i;
	Parent():i(111){}
	virtual void print(){
		cout << i << endl;
	}
};

class Child: public Parent
{
public:
	int i;
	Child():i(222){}
	virtual void print(){
		cout << i << endl;
	}
};

int main(){
	Child c1;
	c1.print();
	//引用的上行转换
	Parent &p = c1;
	p.print(); //222 多态
	//指针的上行转换
	Parent *pp = &c1;
	pp->print(); //222 多态

	//对象的直接转换
	Parent pn = c1; //这里调用了拷贝构造函数，c1作为参入传入，然后重新构造了一个新对象（新对象中没有任何的子类的痕迹，因为（默认）拷贝构造函数中没有对应的操作）
	pn.print(); //111 只有父类对象，没有多态
	return 0;
}