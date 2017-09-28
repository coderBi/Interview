#include <iostream>
using namespace std;

/*
题目描述：
	有一种计算机，其中只存在以下的原子操作：
		1）赋值a=b
		2）+1操作,++a和a+1
		3)指定循环次数的循环for(变量){//循环中对于变量的修改不会在改变for里面的循环的次数了。}
		4) 只能处理0和正整数
		5）函数调用func(参数列表)
	问题：使用伪代码在以上的给定环境下实现加法、减法和乘法。
分析：
	由于只要+1的操作和赋值，可以从控制循环的次数入手思考问题.把一个变量0先自加a次然后再自加b次就是a+b(或者直接将一个变量直接赋值为a然后让a自增b次)。写一个嵌套的循环外层循环a次内层循环b次，那么一个初始化为0的变量在这个循环中的经历了a*b次的自加最后得到乘法器。对于减法器我们可以考虑首先实现自减1运算，for(a){b=i;++i;}这样就可以记录下i最后一次自加之前的值，而经过最后的一次自加i成了a，那么之前的那个值就是a-1。实现了自减的操作的基础上，接下来无非就是将一个变量赋值给a，然后让a自减b次就得到了a-b。
*/

int Plus(int a, int b){
	int result = a;
	while(b--){
		++result;
	}
	return result;
}

/* 自减 */
int dec(int n){
	int result = 0, temp = 0;
	while(n--){
		result = temp;
		++temp;
	}
	return result;
}

int Sub(int a, int b){
	int result = a;
	while(b--)
		result = dec(result);
	return result;
}

int Multi(int a, int b){
	int result = 0, temp = b;
	while(a--){
		temp = b;
		while(temp--)
			++result;
	}
	return result;
}

int main(){
	int a = 6, b = 3;
	cout << Plus(a,b) << "---" << Sub(a,b) << "---" << Multi(a,b) << endl;
	return 0;
}