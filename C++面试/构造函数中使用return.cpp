#include <iostream>
using namespace std;

/*
题目描述：
	构造函数中是否可以使用return
分析：
	1）C++中，构造函数不返回任何类型的值，连void的都没有。所以在构造函数中不能使用return返回任何的值，否则会出现编译错误，但是单独使用return可以控制提前退出函数调用，这个是可行的。
	2）结论：可以单独使用return控制退出函数调用，但是不能return任何类型的值。
*/

class Test
{
public:
	int i;
	Test(int i): i(i){
		if(i){
			cout << "i is not zero" << endl;
			return; //没有返回任何值，只是控制函数调用结束
		}
		cout << "i is zero" << endl;
		//return ''; //报错，说是构造函数中不能返回任何值
	}
};

int main(){
	//下面的打印说明构造函数中可以是使用return控制函数调用的提前返回
	Test t2(1);
	Test t1(0);
	return 0;
}