#include <iostream>
#include <assert.h>
#include <algorithm>
#include <limits>
using namespace std;

/*
问题描述：
	01背包问题。01背包指的是所有的物品每一个重量只有一个然后要么拿要么不拿不能拿一部分。考虑如下问题，用代码求解：背包容量为5，物品1重1价值60，物品2重2价值100，物品3重3价值120。求最大价值。如果要求背包必须装满的前提下修改代码求最大价值.
分析：
	首先考虑背包可以不装满的情况，这种情况是网络上分析的最多的问题。思路是一个递推公式用v[i][j]表示用前面i个物品填充容量j的情况下可以获取到的最大价值。那么v[i][j] =  max(value[i-1] + v[i-1][j-weigth[i-1]], v[i-1][j])，其中value数组代表价值，weight数组存储的是每个的重量。容易知道v[0][0~最大容量]=0，v[0~最多物品][0]=0。
	接着分析，在保证最后背包一定要装满的情况。首先考虑递推公式，原来的递推公式v[i][j] =  max(value[i-1] + v[i-1][j-weight[i-1]], v[i-1][j]依然是实用的，这个时候v[i][j]表示使用i个商品填满j的容量的最大价值。由于递推公式是一样的，那么只需要修改递推的初始条件。可以知道v[1~最大物品数][0]=0这个时候是装满的。而v[0][1~最大容量]=-INFINITY, 这里的意思是将没有装满的情况的价值设置为负无穷，而负无穷加上任何非无穷的数据还是负无穷（实际意义因为value[i-1] + v[i-1][j-weight[i-1]]在v[i-1][j-weight[i-1]]=-INFINITY的时候表示的依然是没有装满的状态）。通过上面的分析，对于保证必须装满的条件分析，只需要修改初始的递推条件和增加加法的额外判断就可以在原来的不需要装满的01背包的代码基础上完成保证装满条件下的01背包的代码
note:
	在考虑这个问题的时候，一开始分析递推公式的时候认为应该将传入的物品按照重量排序。后来发现这可能是现实中的一个错觉。实际上不用排序因为递推公式进行填表的时候囊括了所有的物品和容器的排列组合
*/

/**
*  获取在最后一定装满的情况下01背包的最大价值
*
* @param int value[] 所有物品的价值数组
* @param int weight[] 所有物品的重量数组
* @param int number 物品的数量
* @param int capactiy 提供的容量
* @return int 返回获取到的最大价值
*/
int MaxValueWhenMustFull(int value[], int weight[], int number, int capacity){
	assert(value && weight && number >= 0 && capacity >= 0);
	int **result = new int*[number + 1];
	const int INFINITY = std::numeric_limits<int>::min(); //最大负数，用来保存没有装满的时候的价值
	if(!result)
		throw "内存分配出错";
	for(int i = 0; i <= number; ++i){
		result[i] = new int[capacity + 1]();
		if(!result[i]){
			//释放已经分配的空间
			for(int j = 0; j < i; ++j)
				delete[] result[j];
			delete[] result;
			throw "内存分配出错";
		}
	}
	//将result[0][1~最大容量设置为INFINITY
	for(int i = 1; i <= capacity; ++i){
		result[0][i] = INFINITY;
	}
	//递推填表
	for(int i = 1; i <= number; ++i){
		for(int j = 1; j <= capacity; ++j){
			if(weight[i-1] <= j)
				result[i][j] = (INFINITY == result[i-1][j-weight[i-1]] ? INFINITY : result[i-1][j-weight[i-1]] + value[i-1]);
			result[i][j] = std::max(result[i][j], result[i-1][j]);
		}
	}
	int toReturn = result[number][capacity];
	//释放内部空间
	for(int i = 0; i <= number; ++i)
		delete[] result[i];
	delete[] result;
	return toReturn;
}


int main(){
	//测试
	int value[] = {500,100,120};
	int weight[] = {1,2,3};
	cout << MaxValueWhenMustFull(value,weight,3,5) <<endl; //正确结果220，可以看到那个最大价值为500的没有被选择
	return 0;
}