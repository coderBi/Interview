#include <iostream>
#include <assert.h>
using namespace std;

/*
题目描述：
	不用va_list实现一个n个数的加法运算函数
分析：
	va_list va_arg那一套底层其实就是在上一个参数的地址上进行设定的偏移，然后一次取出多少的字节的数据。所以程序中在控制好取数据的次数的前提下，可以自己操作指针。
*/

/*
	实现n个数的加法
@param int num 要进行相加运算的数字的个数，最小为1
@param ... 多个要进行相加的数
@return int 多个数相加的结果
*/
int Add(int num, ...){
	assert(num >= 1);
	//获取第一个数字的其实地址
	int *p = (int*)&num + 1; //其实就是下一个int
	int sum = 0;
	for(int i = 0; i < num; ++i){
		sum += *p++;
	}
	return sum;
}

int main(){
	//Add的第一个参数提供是要相加的元素的个数
	cout << Add(4,1,2,3,4) << endl;
	return 0;
}