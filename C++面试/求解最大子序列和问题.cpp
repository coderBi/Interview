#include <iostream>
#include <assert.h>
using namespace std;

/*
问题描述：
	子序列和最大值问题：一个数组的各个子数组中所有的元素的和构成各个子序列的和，求所有子序列和的最大值。
分析：
	这个问题是非常常见的题目。网络上有多种版本的算法，在数据结构和算法的书籍上也可以见到这个问题的分析。主要的有n * n * n的暴力求解、n * n的简单优化(优化的部分是每一个起点往后依次求和，每次求和可以用上前面已经有的求和结果)、n * log(n)的分治(取出一个中间元素，不包括这个元素的左边求出最大右边求出最大，包括这个元素的时候依次往左累加计算最大，依次往右累加加上最大然后将变量的值加上这个中间值构成中间最大)、最简洁的却没有简单数学证明的一次遍历O(n)算法。
*/

/**
* 求解最大子序列和，算法复杂度O(n)
*
* @param int input[] 输入的待求解的数组
* @param int length 输入数组的长度
* @return int 返回最大子序列和
*/
int MaxSubsequencePlus(int input[], int length){
	assert(input && length >= 0);
	int result = 0, sum = 0;
	for(int i = 0; i < length; ++i){
		sum += input[i];
		if(sum < 0)
			sum = 0;
		if(sum > result)
			result = sum;
	}
	return result;
}

int main(){
	//测试
	int input[] = {-2,5,3,-6,4,-8,6};
	cout << MaxSubsequencePlus(input, 7) << endl; // 8 = 5 + 3
	return 0;
}