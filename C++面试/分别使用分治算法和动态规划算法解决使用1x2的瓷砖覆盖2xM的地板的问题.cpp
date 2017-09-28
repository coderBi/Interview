#include <iostream>
#include <assert.h>
using namespace std;

/*
题目描述：
	分别使用分治算法和动态规划算法解决下面问题：使用1*2的瓷砖覆盖2*M的地板，一共有多少种摆法
分析：
	1）因为是2*M的地板，所以第一列可以是横着放一块1*2的瓷砖，那么由于只有两行，那么这一块瓷砖一定的下面一定还有一块1*2的瓷砖，它们一起填充前两列。另一种情况是第一列竖着放一块1*2的瓷砖，那么第一列就放好了，接下来直接考虑2*(M-1)的子问题就行。由于上面分析的两种情况中，第一列的摆放的不同的，那么这两种的摆放情况是不存在重叠的，所以总的摆放的方案的数量是f(m) = f(m-2)  + f(m-1)。
	2）上面的分析过程便是分治的过程，可以看到这个公式是斐波拉契的，会有很多的重复计算。如果采用自底向上的递推，然后保存中间量的形式，可以使用动态规划的思路优化计算。
扩展分析：
	1）如果是1*2的瓷砖去铺N*M的地面，又该如何分析。首先从左上角开始分析还是横着摆放第一块还是竖着摆放第一块这两种情况由于首个角的摆放不同而符合分治要求。但是与2*M不同，当横着摆放第一块的时候，这一块的下面不一定必须要一块横着摆的1*2的瓷砖，进一步分析，如果对于不同的行数N可能分析不一样，还有就是没有办法说先把上面的2*M铺满这样的分析，因为铺的过程中可能会产生不整齐的情况。所以总体上看，这只用N*M的摆放方案，没有直观的简便分析方法。
实现补充：
	一般的动态规划都是从下往上的，如果是要从上往下，那么可以先将中间保存的空间统一初始化为一个非法值，然后在递归的开始判断这个值是否已经计算过了，如果计算过了就直接取出。这样就可以实现自顶向下的动态算法。
*/

/*	
	使用分治的思路计算1*2的瓷砖填充2*M的地板的方案种数的问题
@param int m 要填充的地板的列数
@return int 所有的摆放的方案种数
*/
int DivideCal(int m){
	assert(m > 0);
	if(m <= 0)
		return 0;
	if(m == 1)
		return 1; //只有一列，所以只要一种摆法，竖放一块
	if(m == 2)
		return 2; //因为递归公式中使用到了f(m-2)，所以m=2的时候也因该是一个base
	return DivideCal(m - 2) + DivideCal(m - 1);
}


/*	
	使用动态规划的思路计算1*2的瓷砖填充2*M的地板的方案种数的问题
@param int m 要填充的地板的列数
@return int 所有的摆放的方案种数
*/
int DpCal(int m){
	assert(m > 0);
	if(m <= 0)
		return 0;
	int first = 1, second = 2, tmp = 0;
	if(1 == m)
		return first;
	for(int i = 3; i <= m; ++i){
		tmp = first + second;
		first = second;
		second = tmp;
	}
	return second;
}


#define MAX_COLUMN 1000
int save[MAX_COLUMN] = {0}; //保存中间计算数据
/*	
	自顶向下的dp
@param int m 要填充的地板的列数
@return int 所有的摆放的方案种数
*/
int DpFromTopCal(int m){
	assert(m > 0);
	if(m <= 0)
		return 0;
	if(!save[m-1]){
		//没有计算过，就计算save[m-1]
		save[m-1] = 1 == m ? 1 : ( 2 == m ? 2 : DpFromTopCal(m-2) + DpFromTopCal(m-1) );
	}
	return save[m-1];
}

int main(){
	cout << DivideCal(3) << endl;
	cout << DpCal(2) << endl;
	cout << DpCal(3) << endl;
	cout << DpFromTopCal(3) << endl;
	cout << DpFromTopCal(2) << endl;
	return 0;
}