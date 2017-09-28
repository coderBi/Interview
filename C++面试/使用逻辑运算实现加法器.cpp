#include <iostream>
#include <stdarg.h>
using namespace std;


/*
题目描述：
	使用逻辑运算实现加法器
分析：
	逻辑运算实现加法器的思路为：如果两个相加的数相与的结果是0，那么也就是说两个数没有同一位都是1的情况，也就是说不存在进行的问题。这个时候两个数相加的结果就是两个数的异或（因为对于任何一位只有可能存在一个数字是1或者是全0）。如果这两个数相与的结果不是0，那么说明存在进位，这个与的结果是1的位表示这个两个数的这一位都是1，那么把两个数与的结果左移一位就应该是产生的进位。将进位 +　没有考虑进位也就是两个数的异或　＝　最终的两个数的和，这里进入了一种递归表述，这个递归的base是两个相加的数其中有一个为0（这个数也就是充当了进位）.
实际编码改进：
	1）实际编码的过程中，发现一个问题，就是关于api的设计思路。如果直接写一个递归充当这个加法器函数，那么哪一个是与的结果哪一个是异或的结果，就会是确定的。而对于一般的加法运算，这个两个运算数的顺序应该是无关的。一个最直观的结果，如果直接这么设计加法那么 0 + 100 和 100 + 0内部的执行效率是不一样的。例如如果把与结果放到第二个参数，那么100 + 0直接就可以结束计算，而0 + 100需要多进行一次递归（尽管在这里计算量并不是很大，但是这里指出这种设计可能存在一些调用不均衡的问题）。所以这里改进的算法将递归放到加法器的内部调用。
	2）更一般的算法，可能需要进行无限个数字的相加（不考虑溢出），这里也给出相应的实现
*/

/*
	基础算法实现：用逻辑运算实现加法器
@param int a 被加数
@param int b 加数
@return int  返回两个数相加的结果
@note: 这里的算法对调用的参数的顺序敏感，例如 100 + 0 与 0 + 100的执行会出现不同，后者多了一次递归
*/
int PlusImplementedWithLogic(int a, int b){
	if(!b)
		return a;
	return PlusImplementedWithLogic(a ^ b, (a & b) << 1); //移位运算符优先级 > 逻辑运算符 > 位运算符。所以这里需要将(a & b)括起来
}

/*
	递归计算两个数的异或与两个数的与的和
@param int _xor 两个数异或的结果
@param int _and 两个数与的结果
@return int  返回两个数相加的结果
*/
int AddXorWithAnd(int _xor, int _and){
	if(!_and)
		return _xor;
	return AddXorWithAnd(_xor ^ _and, (_xor & _and) << 1);
}


/*
	改良后的算法实现：用逻辑运算实现加法器
@param int a 被加数
@param int b 加数
@return int  返回两个数相加的结果
*/
int PlusImplementedWithLogicImproved(int a, int b){
	if(!a)
		return b;
	if(!b)
		return a;
	return AddXorWithAnd(a ^ b, (a & b) << 1); //移位运算符优先级 > 逻辑运算符 > 位运算符。所以这里需要将(a & b)括起来
}

/*
	利用逻辑运算实现多个数相加
@param int a 第一个加数
@param int b 第二个加数
@param int ... 后续更多的加数，如果有的话
@return int 多个加数相加的结果
@note: 从第三个参数开始如果传入了一个参数为0就表示停止计算。所以这里会有两个影响，一个是如果传递了多余两个参数，那么最后一个参数一定要设置为0(额外的终结标志)，否则可能会计算到了垃圾值；另一个问题是这个函数需要对传递的要计算的参数进行过滤，保证在最后一个元素之前不能出现0，否则会漏掉元素.
*/
int MultiPlusImplementedWithLogic(int a, int b, ...){
	int result = PlusImplementedWithLogicImproved(a,b);
	va_list va;
	va_start(va,b);
	int next;
	while(next = va_arg(va,int)){
		result = PlusImplementedWithLogicImproved(result,next);
	}
	va_end(va);
	return result;
}

int main(){
	//测试基础加法实现
	cout << "------------测试分割线--------------" << endl;
	cout << PlusImplementedWithLogic(10,21) << endl;
	cout << (10 + 21) << endl;

	//测试测试改良之后的两个数相加
	cout << "------------测试分割线--------------" << endl;
	cout << PlusImplementedWithLogicImproved(10,21) << endl;
	cout << (10 + 21) << endl;

	//测试多个数相加
	cout << "------------测试分割线--------------" << endl;
	cout << MultiPlusImplementedWithLogic(10,21,10,100,0,1001) << endl; //0只能放到最后 否则只计算了一部分的元素
	cout << MultiPlusImplementedWithLogic(10,21,10,100,1001) << endl; //没有0 可能会有垃圾值
	cout << MultiPlusImplementedWithLogic(10,21,10,100,1001,0) << endl; //正常调用
	cout << (10 + 21 + 10 + 100 + 0 + 1001) << endl;
	return 0;
}