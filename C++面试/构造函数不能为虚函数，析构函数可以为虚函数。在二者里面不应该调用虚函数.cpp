#include <iostream>
using namespace std;

/*
题目描述：
	构造函数和虚构函数能否是虚函数，在构造函数和析构函数中能否调用虚函数。
分析：
	1) 父类的构造函数先于子类的执行，虚函数的调用是通过虚表实现的。那么在父类构造的时候，子类由于还有没有构造，所以也就没有指向子类的虚表的vptr，所以构造函数设置为virtual的没有任何的意义，构造函数在标准中是明确禁止为virtual的。而析构函数很多时候会设置为virtual的，原因是如果用父类对象的引用或者和指针对子类的对象进行保存或者传递，这中间的资源的释放在父类的析构为virtual的情况下会调用子类的保证子类中的资源可以得到有效释放，防止内存泄露。由于虚函数的调用会查询虚表，而父类构造的时候，子类中的vptr还没有初始化，所以在父类中调用虚函数也只是调用其本类中的，而在析构函数中由于子类独有的资源已经释放了，剩下的是父类类型的一个子对象，这个时候调用虚函数，也只是执行本类的方法，同样调用虚函数没有多态的效果。所以在构造和析构函数中应该避免调用虚函数.
	2）通过上慢的分析，任何时候在构造函数和析构函数中调用虚函数，都是执行本类（这个方法可能是继承来的）的方法，不会执行到之类中去
*/

class Parent
{
public:
	/*
	//构造函数不能是虚函数，编译错误： constructors cannot be declared 'virtual'
	virtual Parent(){}
	*/
	Parent(){
		cout << "create parent ... start..." << endl;
		func(); //调用虚函数，还是会执行本类的函数，这种调用据说最好规避
		cout << "create parent ... end..." << endl << endl;
	};
	virtual void func(){
		cout << "func in Parent" << endl;
	}
	virtual ~Parent(){
		cout << "release parent ... start..." << endl;
		func(); //调用虚函数，还是会执行本类的函数，这种调用据说最好规避
		cout << "release parent ... end..." << endl << endl;
	}
};

class Child : public Parent
{
public:
	Child(){
		cout << "create child ... start..." << endl;
		func();
		cout << "create child ... end..." << endl << endl;
	};
	virtual void func(){
		cout << "func in Child" << endl;
	}
	virtual ~Child(){
		cout << "release child ... start..." << endl;
		func(); 
		cout << "release child ... end..." << endl << endl;
	}
};

int main(){
	//可以看到任何时候构造函数和析构函数对虚函数的调用都是执行自己本类中的函数
	Child c; 
	return 0;
}