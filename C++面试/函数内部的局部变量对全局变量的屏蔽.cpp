#include <iostream>
using namespace std;

/*
	1)这里的同样的代码，在js中测试的结果是undefined和2，原因是在一开始js就认为在函数内部进行了屏蔽，所以函数内部不会考虑全局的tt。由于第一个tt的打印的时候局部的tt还没有定义，所以会出现一个undefined
	2)note: 同样的打印如果出现在C/C++中，会打印aadd，原因是在第一个打印的语句的时候判断在函数的内部还没有对全局的tt进行屏蔽，所以会打印出aa。值得注意的是在php和js中没有复合语句的单独作用域，只会区分函数内还是函数外，这点与c和c++不同。
	3)在C++中如果判断当前局部变量已经定义，那么就会使用局部变量屏蔽全局的，这个时候如果还是要使用全局的变量，可使用::引用或者使用extern申明全局变量
*/

int tt = 1;
int ex = 100;

int main(){
	cout << tt << endl; //打印的结果是1 运行到这局部的变量还没有对全局的tt进行屏蔽
	int tt = 2;
	cout << tt << endl; //2，新定义的tt对全局的tt进行了屏蔽
	cout << ::tt << endl; //1，使用::指明要使用全局的变量

	int ex = 99;
	cout << ex << endl; //99
	{
		extern int ex; //对全局变量进行一次申明
		cout << ex << endl; //100
	}
	//extern int ex; //报错，因为同一个作用域下面前面存在一个int ex = 99; 这里判断为重定义。注意上面的{}括起来的是一个复合语句，有自己的作用域。
	return 0;
}