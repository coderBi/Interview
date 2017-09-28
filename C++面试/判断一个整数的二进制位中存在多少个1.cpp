#include <iostream>
using namespace std;

/*
题目描述：
	一个整型，如何判断这个整数的二进制位中存在多少个1
分析：
	1）可以通过对1 << n，然后将这个结果与要判断的数字进行与运算取出整数的第n+1位数，然后判断是否是1。当然也可以每次都和1与运算而是把这个整数进行右移，只是这个时候要注意一定要将这个整数转换为unsigned的类型，否则如果是一个负数，那么右移高位补充的是符号位，会导致结果不正确。
	2）另一个有技巧的实现方式是将n &= (n-1)一直到n为0，n不为0的循环执行次数就是整数n中的1的个数。上面的算法之所以正确的，原因是每一次n &= (n-1)都会消掉从低位到高位的第一个1（n-1的结果是这个1的左边位不变，右边位都变成1(注意一点原来其右边的位都是0)，而其本身变成了0，所以n & (n-1)的结果就是消掉从低位到高位的第一个1）
*/

/*
	使用1不断进行左移法：获取一个整型的二进制位中的1的个数
@param int n 要获取的整数n
@return int 整数n的二进制数据中1的个数
*/
int Get1InBits1(int n){
	unsigned int x = 1; //因为是左移，这里的x是否有符号其实不重要
	int result = 0;
	//下面的循环中条件是x不为0，也就是当x移位过程中将唯一的1移出去了，循环结束
	while(x){
		if(n & x)
			//当前位是1，计数器加一
			result++;
		x <<= 1;
	}
	return result;
}

/*
	使用输入的整数不断右移法：获取一个整型的二进制位中的1的个数
@param int n 要获取的整数n
@return int 整数n的二进制数据中1的个数
@note: 这里的参数类型是unsigned int，因为如果是signed在移位的过程中会补充符号位。如果这里的形参不是unsigned一方面可以在内存再转换为unsigned，另一方面如果知道机器上的int的长度可以直接用这个长度控制移位的次数，但是这样书写不便于在不同的机器上进行移植
*/
int Get1InBits2(unsigned int n){
	int result = 0;
	while(n){
		if(n & 1)
			//最低位是1，计数器加一
			result++;
		n >>= 1;
	}
	return result;
}

/*
	使用n & (n-1)法：获取一个整型的二进制位中的1的个数
@param int n 要获取的整数n
@return int 整数n的二进制数据中1的个数
@note: 解析： 考虑n中从低位到高位的第一个1，n -1获取到的结果中这个1的左边的位都不变，右边的位都由0变成了1，而这一位其本身由1变成了0，所以每次的 n & (n-1)都是消掉n的从低位到高位的第一个1
*/
int Get1InBits3(int n){
	int result = 0;
	while(n){
		result++; //每次循环消掉了一个1
		n &= n-1;
	}
	return result;
}

int main(){
	int n = 0xaaaaaaaa, m = 0x55555555;
	cout << Get1InBits1(n) << "....." << Get1InBits1(m) << endl;
	cout << Get1InBits2(n) << "....." << Get1InBits2(m) << endl;
	cout << Get1InBits3(n) << "....." << Get1InBits3(m) << endl;
	return 0;
}