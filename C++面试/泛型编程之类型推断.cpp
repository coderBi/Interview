#include <iostream>
using namespace std;

/*
题目描述：
	下面的函数调用是否正确
	template <typename T> T add(T x, T y){
		return x + y;
	}
	add<float>(5.0,2);
	add(5.0,2);
分析：
	1）第一个调用add<float>说明模板里面传入的类型形参是float，那么里面的两个函数形参会当做float进行处理。
	2）第二个调用因为没有提供类型形参，所以编译器会根据传入的函数实参的类型进行相应的推断。第一个5.0会推断为double，而第二个2会推断为int，二者的类型并不一致，出现调用矛盾。
	3）泛型函数的返回值在template的申明和>之后。每一个类型形参都需要被typename或者是class修饰（class和typename没有区别）
*/

template <typename T> T add(T x, T y){
	return x + y;
}

int main(){
	//直接指定类型
	cout << add<float>(5.1,2) << endl;

	//没有指定类型，编译器通过传入的函数实参进行类型的推断
	//cout << add(5.1,2) << endl; //编译错误，提示无法匹配到add(double, int)
	return 0;
}