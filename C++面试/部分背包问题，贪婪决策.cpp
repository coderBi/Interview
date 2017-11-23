#include <iostream>
#include <math.h>
#include <assert.h>
using namespace std;

/*
问题描述：
	部分背包问题：01背包形象的将每一个物品描述成了一个完整的不可拆卸的整体，要么都拿走要么完全不拿。而部分背包是将所有物品形象描述为一袋一袋的金粉，可以拿一部分。这种情况下应该如何做到价值最大。
分析：
	一直按“密度”最大拿物品，一直拿到容器填充完成。部分背包的递推是贪婪的，而01背包却只能用动态规划做决策，因为在01背包的情况下没有办法决定最开始拿的最优最后一定用的上：例如如果一开始拿一个密度最大的，那么可能由于容器容量限制导致不是最终的最优。
*/

/**
*  获取部分背包问题的最大价值
*
* @param int value[] 所有物品的价值数组
* @param int weight[] 所有物品的重量数组
* @param int number 物品的数量
* @param int capactiy 提供的容量
* @return int 返回获取到的最大价值
*/
int MaxValueWhenWeightCanBeResolved(int value[], int weight[], int number, int capacity){
	assert(value && weight && number >= 0 && capacity >= 0);
	//按密度进行排序，这里在内部排序索引数组，而不是操作传入的两个数组，这也是符合一般的使用情况的。例如现实情况可能是更多组的更庞大的数据集合，一般不应该直接操作原来的数据。而且这里涉及到两个数组，而关联它们的是索引，所以进行索引标号排序是最合适的逻辑
	int *indexes = new int[number](); //用来保存所有物品的索引标号
	float *densities = new float[number](); //保存所有的物品的密度
	if(!indexes || !densities){
		delete[] indexes;
		delete[] densities;
		throw "内存分配出错";
	}
	for(int i = 0; i < number; ++i){
		indexes[i] = i;
		densities[i] = (float)value[i] / weight[i];
	}
	//进行索引数组按照“密度”从大到小的排序 这里为了保证代码的效率和代码的内联，采用了希尔排序
	for(int step = number / 2; step > 0; step *= 2){
		for(int i = step; i < number; ++i){
			int index = indexes[i], density = densities[i], j;
			for(j = i; j - step >= 0 && density > densities[j - step]; j -= step){
				//将密度较小的元素后移
				densities[j] = densities[j - step];
				indexes[j] = indexes[j - step];
			}
			densities[j] = density;
			indexes[j] = index;
		}
	}
	int result = 0;
	//按密度从大到小装入容器
	for(int i = 0; i < number && capacity > 0; ++i){
		if(capacity > weight[indexes[i]]){
			result += value[indexes[i]];
			capacity -= weight[indexes[i]];
		}else{
			result += round(capacity * densities[i]); //最终的结果进行四舍五入
			capacity = 0;
		}
	}
	//释放内部空间
	delete[] indexes;
	delete[] densities;
	return result;
}

int main(){
	//测试
	int value[] = {500,100,120};
	int weight[] = {1,2,3};
	cout << MaxValueWhenWeightCanBeResolved(value,weight,3,5) <<endl;  //680 = 500 + 100 +　80
	return 0;
}