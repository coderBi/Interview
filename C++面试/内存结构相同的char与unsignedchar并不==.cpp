#include <iostream>
using namespace std;

/*
分析以下问题：
	char a = 0xf1;
	unsigned char b = a;
	if(a == b){ cout << "yes" << endl;}
	上面的语句是否会输出yes？
分析：
	这里涉及到一个整型提升的问题。凡是表示能力比int若的在计算的时候都会先提升为int（如果待提升的数据和int的二进制位数一样并且为unsigned，那么会进一步提升为unsigned int）. 所以这里的表达式 a == b。会先将a和b提升为int，a和b的内存结构是一样的，但是a是有符号的b是无符号的，在进行内存提升的时候有符号的高位会补充符号位，而无符号的统一高位补充0. 由于a和b的高位是1，这里进行提升之后两个数据得到的int会出现差异。所以a != b
*/

int main(){
	char a = 0xf1;
	unsigned char b = a;
	//输出结果为no
	if(a == b){
		cout << "yes" << endl;
	}else{
		cout << "no" << endl;
	}
	return 0;
}