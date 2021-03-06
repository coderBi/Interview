#include <iostream>
using namespace std;


/*
题目描述：
	引用类型的数据成员在哪里进行初始化
分析：
	1）如果存在引用类型的成员属性，那么必须要对这个成员进行初始化，这是引用的性质决定的
	2）这种数据成员的初始化只能放到初始化列表中，不能放到构造函数的内部。原因是在构造函数的内部进行是赋值操作不是初始化操作(调用函数传入的实参用来初始化了一个形参。之后相应的成员属性没有初始化而是在构造函数的内部进行了赋值，对于引用的赋值是作用在其绑定对象身上的)。
	3) 因为引用数据类型必须要初始化，所以对于每个构造函数都要添加引用数据类型的初始化代码.
	4）对于静态的引用类型，应该在类的定义体外部进行初始化。
*/

class Base
{
public:
	int b = 11;
}; 

class Test
{
public:
	int x;
	Base &m;
	/*
	//这个写法编译通不过，因为这个构造函数没有对引用类型的成员m 进行初始化的工作
	Test(){
		x = 1;
	}
	*/

	/*
	//注意下面的this->m = m是一个赋值操作，所以是不合法的，引用只能进行初始化操作。而传入的实参用来初始化这里的形参m了
	Test(Base & m){
		this->m = m; //会提示非静态的数据成员不能使用赋值操作
		this->x = 1;
	}
	*/

	//正常情况下，只能通过构造函数中的初始化列表进行初始化
	Test(Base & m): m(m){
		//调用静态的引用
		cout << s << endl;
		s = this->x = 1221;  //注意这里对s的赋值不是修改引用保存的地址，因为没有办法让引用重新绑定对象。实际上这里的赋值是对引用指向的对象的赋值
	}

	//静态引用
	static int & s;
};
int i = 999;
int& Test::s = i; //static在外面进行初始化

int main(int argc, char* arg[]){
	Base b;
	Test t(b);
	cout << t.s << endl;

	//因为构造函数存在初始化列表，在存在初始化列表的情况下不能使用{}进行对象的初始化
	//Test t1 = {77, b}; //测试{}初始化对象
	return 0;
}