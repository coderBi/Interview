#include <iostream>
using namespace std;

/*
题目描述：
	下面的代码是否正确：
		Test test();
		test.func();
分析：
	1)这里的写法不正确，因为在栈上面常见对象，如果是使用没有参数的构造函数，那么变量名的后面是不能带上括号()的，因为如果这样是合法的，将存在歧义：如果解析为一个返回值类型为Test参数为空的test函数的申明也是合法的。
	2) 对于堆上分配内存，因为不存在歧义性，所以如果调用的是无参的构造函数，无论是否有括号，解析都是一样的。也就是 Test *p = new Test 和 Test *p = new Test() 的意思是一样的，都可以无歧义的通过编译.
*/

class Test
{
public:
	int x;
	Test(){}
	Test(int x){this->x = x;}
	void print(){
		cout << "hello print" << endl;
	}
};

int main(){
	//如果使用的是无参的构造函数，那么在栈上构建对象的时候，不能带上这里的()，否则会被编译器错误的理解为申明了一个返回值为Test参数为void的t函数.
	Test t(); 
	t.print();//编译错误,结合上面的分析，由于t被分析为一个函数，t不是对象，那么这里的t.print就是非法的

	//在堆上构建对象，因为没有歧义性，所以不存在问题
	Test *p = new Test();
	delete p;
	return 0;
}