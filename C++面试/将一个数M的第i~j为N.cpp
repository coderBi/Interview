#include <iostream>
using namespace std;

/*
题目描述：
	设计一个函数，实现以下功能：两个整数M、N，要求将M的第i~j位替换为N，其中N的长度为j-i+1.
分析：
	(1 << (i-1)) - 1 可以获取到第1~i-1位的全0。同样的，(1 << j) - 1 可以获取到的j为的全0，使用~0可以获取到所有位都是全0，然后用这个结果减去(1 << j) - 1 可以获取到第j+1到最高位的全0。利用上面的分析可以将M的被替换位的前后的数据取出来。然后与m << (i-1)与前后的数据进行或运算就可得到最终的结果。
--note：
	m << i会将m的最低位移动到第i+1位。
	上面的分析步骤也可以先得到被替换的前面部分，然后再得到被替换部分的后面部分，将两部分进行或运算。这里还是采取上面描述的，先得到对应的前后位都为1的mask然后一次性获取到不要被替换位的数据。
*/

/*
	将一个数据的第i~第j为替换为另一个数
@param int m 要被替换的数据
@param int n 用来替换原来数据的数
@param int i 要被替换的低位
@param int j 要被替换的高位
@return int 替换之后的结果
*/
int updateBits(int m, int n, int i, int j){
	int high = ~0 - ((1 << j) - 1);
	int low = (1 << i - 1) - 1;
	int mask = low | high;
	return m & mask | n << (i-1);  //注意数学运算符优先级 > 移位 > 位运算的& > 位运算的|
}

int main(){
	int m = 0xffffffff;
	int n = 0x0;
	//将第5~9位替换为0
	cout << hex << updateBits(m, n, 5,9) << endl;
	return 0;
}