#include <iostream>
using namespace std;

#define N 10  //值得注意的是，很多地方在10的后面加上 “;” 这个是不合适的，因为这个";"也会拿过去带入替换

int main(){
	int arr1[N];  //N是宏 可以用来当做数组的长度，因为在编译的时候进行替换，编译器可以判断的出这个数组的长度。

	const int M = 10;
	int arr2[M]; //这个语句在C++中是可以编译通过的，但是在C语言中是错误的，因为两者的const关键字的有所区别
	
	int x = 10;
	int arr3[x];  //这个可以通过编译，因为gcc给了优化。但是这种写法是不对的。
	return 0;
}