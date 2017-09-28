#include <iostream>
using namespace std;

/*
分析：
	1)初始化列表是真正的初始化，而构造函数体是初始化之后对各个成员变量的赋值。
	2)初始化列表的执行顺序与初始化列表的书写的顺序没有关系，只与各个成员在类的定义体中的定义顺序有关。
	3)对于全局的对象，如果一个属性没有在构造中初始化或者赋值，那么会被默认初始化为0，这是bss段的属性导致的。
*/

class B
{
public:
	int i;
	B(int i){
		std::cout << "init B" << std::endl;
		this->i = i;
	}
};

class A
{
public:
	string s;
	int i;
	B b; //由于B没有定义默认构造函数，所以必须要在初始化列表中初始化
	A():b(5){
		std::cout << "init A" << std::endl;
	}
};

//全局对象在bss段中，对于没有初始化的部分会置零
A g;

int main(){
	cout << "enter main..." << endl;
	cout << g.i << "..." << g.s << "-----" << g.b.i << endl; //由于在全局的bss中没有被初始化的部分是0，所以g.i是0，g.s使用默认的构造函数是空字符串
	A a; 
	cout << a.i << "..." << a.s << "-----" << a.b.i << endl; //i是垃圾值  s是空 b.i是5
	return  0;
}