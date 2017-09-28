#include <iostream>
using namespace std;

/*
题目描述：
	菱形的虚继承中，对于祖父类子对象的实例化进行了多少次
分析：
	1) 只进行了一次，虚继承保证了祖父类的子对象的只存在一个，而在直接继承的两个父类中存在bptr，用来保存相对于这个祖父类的子对象的偏移。正因为如此，所以在两个父类的初始化列表中和当前子类的初始化列表中都应该指定祖父类的实例化使用的构造函数（保证这三个类都能正常的实例化对象）。
	2）如果祖父类中没有默认的构造函数，那么在孙子类的初始化列表中必须指定祖父类中的构造函数，否则会编译失败，因为使用虚继承，对祖父类的实例化只进行一次，而初始化的指定只能出现在最终的孙子类中.
*/

class GrandParent
{
public:
		int x;
		int y;
		int z;
		GrandParent(int x){
			this->x = x;
			this->y = 222;
			this->z = 333;
			cout << "create GrandParent" << endl;
		}
		GrandParent(int x, int y){
			this->x = x;
			this->y = y;
			this->z = 333;
			cout << "create GrandParent" << endl;
		}
		GrandParent(int x, int y, int z){
			this->x = x;
			this->y = y;
			this->z = z;
			cout << "create GrandParent" << endl;
		}
};
class Parent1 : virtual public GrandParent
{
public:
	Parent1(int x) : GrandParent(x){
		cout << "create Parent1" << endl;
	}
};
class Parent2 : virtual public GrandParent
{
public:
	Parent2(int x, int y) : GrandParent(x,y){
		cout << "GrandParent2" << endl;
	}
};
class Child : public Parent1, public Parent2
{
public:
	//这里需要提供祖父类A的初始化
	Child() : GrandParent(666,777,888), Parent1(111), Parent2(222,333){
		cout << "create child" << endl;
	}

	void func(){
		cout << x << "..." << y << "..." << z << endl;
	}
	
	/*
	//这个构造函数并不指定GrandParent的构造函数，编译的时候会报错：no matching function for call to GrandPrant::GrandParent()也就是说使用了虚继承，如果祖父类中没有默认的构造函数，那么必须在孙子类中指定祖父类的构造函数，否则会应为调用默认的而出错（编译阶段）
	Child(int x) : Parent1(111), Parent2(222,333){
		cout << "create child" << endl;
	}
	*/
};
int main(){
	//打印的顺序是 GrandParent..Parent1...Parent2...Child。可以看到对于构造Parent1和Parent2的时候，并没有再次调用祖父类中的构造函数(尽管在初始化列表中也分别指定了相应的构造函数，但是由于child类中已经对祖父类的子对象进行了初始化，所以这里的初始化列表的中的代码并不会执行)
	Child c;
	cout << "--------------分割线-------------" << endl;
	c.func(); // 666 777 888 结合上面的构造函数的执行的顺序，可以发现在Parent1和Parent2的初始化列表中指定的GrandParent的构造函数并没有执行.

	cout << "--------------分割线-------------" << endl;
	//直接实例化Parent1，其中指定的GrandParent的构造函数又会执行到
	Parent1 p1(999);
	cout << p1.x << endl; //999
	return 0;
}