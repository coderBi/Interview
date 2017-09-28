#include <iostream>
using namespace std;

/*
题目描述：
	设计一个函数，将一个整数的奇数位与偶数位进行替换
分析与答案：
	奇数位左移就偶数位，偶数位右移就是奇数位。当然这个分析的前提是这里的“整数”的位数是偶数，而这个在计算机中是成立的。使用与0x55555555相与可以取出一个整数的奇数位，使用与0xaaaaaaaa相与可以取出一个数的所有的偶数位.
*/

/*
	将一个int的奇数位与偶数位进行替换
@param int n 要被处理的int
@return int 替换之后的数据
*/
int ExchangeOddEvenBits(int n){
	int odd = sizeof(int) < 4 ? 0x5555 : 0x55555555; //这里的必要性并不强，因为只要保证提供的数据的长度不小于int的长度就行，因为如果溢出会进行低位截断。（那么，在现有通用的环境下，直接写成0x55555555也就是ok的）
	int even = odd << 1;
	return (n & odd) << 1 | (n & even) >> 1;
}

int main(){
	int m = 0x55555555;
	cout << hex << ExchangeOddEvenBits(m) << endl; //输出的结果为aaaaaaaa
	return 0;
}