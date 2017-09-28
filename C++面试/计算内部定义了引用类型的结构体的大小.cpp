#include <iostream>
using namespace std;

/*
题目描述：
	下面的代码最后打印的结果是多少
		struct Base
		{
			int i;
			char c;
		};

		struct S
		{
			Base & b; //如果存的是引用，那么在实例化对象的时候必须要进行相应的初始化
			short si;
		};

		int main(){
			Base b = {110, 'c'};
			S s = {b, 2}; 
			cout << (int)&s.si - (int)&s.b << endl;
			return 0;
		}
分析：
	1）C++中引用数据类型的内容存储的是所绑定对象的地址，也就是说和指针类型存放的内容是一样的，所以引用类型的实际占用的内存空间的大小一般可以认为也是4。
	2）对引用变量进行取址操作，返回的是所绑定对象的地址，而不是引用变量的存储单元的地址
	3）一个函数中调用的时候，先是形参从右到左依次入栈，然后是内部定义的变量依次入栈。上面的代码中由于b先入栈，然后是s入栈，所以s的地址比b的地址小sizeof(s)=8。由于&s.b获取的是main中中变量b的地址，所以最终的打印结果是 (4 - 8) = -4
*/

struct Base
{
	int i;
	char c;
};

struct S
{
	Base & b; //如果存的是引用，那么在实例化对象的时候必须要进行相应的初始化
	short si;
};

int main(){
	cout << sizeof(S) << endl; //8，引用变量占用的数据空间大小为4
	Base b = {110, 'c'};
	S s = {b, 2}; //因为存放了引用类型的成员，所以必须初始化
	cout << s.b.i << endl; //110
	cout << hex << (int)&s << endl;
	cout << hex << (int)&s.b << endl; //这里值得注意的是如果对引用的类型进行取址操作，返回的是所绑定对象的地址（对引用没有释放操作）。
	cout << hex << (int)&s.si << endl; //main函数内部的变量进行入栈的顺序是先入栈了一个b，然后入栈一个s。所以执行到这里s的起始地址比b的小sizeof(s) = 8。又因为对引用的取址操作返回的是引用变量所绑定对象的地址(也即是main里面的局部变量b的地址)，所以这里的打印结果比上面的&s会大出来8
	cout << dec << (int)&s.si - (int)&s.b << endl; //((int)&s + 4) - ((int)&s + 8) = -4

	return 0;
}