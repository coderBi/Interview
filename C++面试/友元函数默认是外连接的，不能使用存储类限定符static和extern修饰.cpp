#include <iostream>
using namespace std;

/*
题目描述：
	友元函数能否有权限修饰符和static
分析：
	1）友元函数除了不是是成员函数，不是通过this指针调用，友元函数必须在类中定义。由于友元函数不是成员函数，默认是外连接的，所以不受权限限定符public protected private等的控制，即使手动加上了也没有作用（实际上，在类中定义的函数，即使没有认为的书写权限限定符，也是会有默认的权限区间的）
	2）但是注意，友元函数默认是外连接的，C++标准中注明不能使用存储类限定符(static和extern)进行修饰（尽管在有些编译器中是通过编译的）
	3) 友元函数的参数一般至少会有一个本类型的引用，这样才能确定是调用哪一个类中的友元函数。如果没有提供任何的参数信息（例如参数为空），在编译阶段会判断为调用的地方找不到函数的定义。
*/

class Test
{
private:
	friend void func1(Test & t){
		cout << "hello func1" << endl;
	}
public:
	friend void func2(Test & t){
		cout << "hello func3" << endl;
	}
	friend void func5(){
		cout << "hello func5" << endl;
	}
	friend void func6(int x){
		cout << "hello func6" << endl;
	}
	friend void func6(int x, Test & t){
		cout << "hello func6" << endl;
	}
	/*
	//下面的两种写法是一样的，都是一个编译错误：storage class specifiers invalid in friend function declaration（存储类型的限定符不能出现在friend函数的申明中）
	static friend void func3(){
		cout << "hello func3" << endl;
	}
	friend static void func4(){
		cout << "hello func4" << endl;
	}
	*/
};

int main(){
	Test t;
	func1(t);
	func2(t);

	//func5(); //编译错误：找不到定义，因为可以用来找这个函数的信息不足。
	
	//func6(1); //编译错误：找不到定义，不能确定是哪一个类的友元

	func6(11,t);//func6
	return 0;
}