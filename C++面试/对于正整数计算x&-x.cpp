#include <iostream>
using namespace std;

/*
得到结论：
	x是正整数的情况下，X&-X的最终结果是将X进行二进制展开之后从低位到高位第一个1.
分析：
	-x是对x进行取反加1，如果正整数最低位是1，那么取反之后就是0，然后加1，就不会进行进位，那么结果就是1.
	如果最低位是0，那么取反是1，然后在加一就会进位，进位之后变成0，那么这一位与X向与运算之后一定是0。接来下分析这个“进位”实际上也就是在剔除掉最低位之后的数字上进行加1，这里进入了一个递归问题。
	通过上面描述，可以知道，x & -x 返回的是正整数二进制表示中从低位到高位的第一个1.
*/

inline int func(int x){
	if(x < 0){ //内联中可以有简单的if 不能有switch
		return -1;  //异常
	}
	return x & -x;
}

int main(){
	int x1 = 3;
	int x2 = 8;
	int x3 = 192;
	cout << func(x1) << endl;
	cout << func(x2) << endl;
	cout << func(x3) << endl;
	return 0;
}