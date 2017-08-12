#include <iostream>
#include <vector>
using namespace std;

/*
题目描述：
	找出一个数组中所有满足下面条件的元素：这个元素的所有的左边的元素小于等于它，右边的所有的元素都大于等于它。
分析：
	1）一个显而易见的常规分析是：对于每一个元素，遍历它的前后所有元素进行判断。这个算法的复杂度是O(n*n)
	2）上面的O(n*n)算法，很明显做了很多次的重复比较，存在优化的空间。假设我们构建两个数组leftMax和rightMin分别表示一个元素左边包括其自身的最大值和一个元素右边包括其自身的最小值，那么只要对应的leftMax[i] <= rightMin[i]，这个i就是符合要求的。实际考虑到内存的开销，可以只使用一个数组leftMax或者是rightMin，记录下来单边的的最值情况，然后从另一边进行遍历，在遍历计算另一边的最值的时候同时判断i是不是符合要求。
*/


/*
	算法1：复杂度O(n*n)
*/
std::vector<int> cal1(int input[], int length){
	vector<int> result;
	for(int i = 0; i < length; ++i){
		int j = 0;
		for(; j < i; ++j){
			if(input[j] > input[i])
				break;
		}
		if(j < i)
			continue;
		for(j++; j < length; ++j){
			if(input[j] < input[i])
				break;
		}
		if(j < length)
			continue;
		result.push_back(i);
	}
	return result;  //返回找到的符合要求的脚标数组
}

/*
	算法2）: 使用一个rightMin数组  复杂度是O(n)
*/
std::vector<int> cal2(int input[], int length){
	std::vector<int> result;
	if(!input || length <= 0){
		std::cerr << "the input array is null or its length is no more than 0" << std::endl;
		return result;
	}
	int *rightMin = new int[length];
	if(!rightMin){
		std::cerr << "new memory fail" << std::endl;
		return result;
	}
	//构建righMin数组
	rightMin[length -1] = input[length -1];
	for(int i = length -2; i >= 0; --i){
		if(input[i] < rightMin[i+1])
			rightMin[i] = input[i];
		else
			rightMin[i] = rightMin[i+1];
	}

	//从左向右计算leftMax
	int leftMax = 0x8fffffff; 
	for(int i = 0; i < length; ++i){
		//获取前面0~i的最大值
		if(input[i] > leftMax)
			leftMax = input[i];
		if(leftMax <= rightMin[i])
			result.push_back(i);
	}
	//释放资源
	delete [] rightMin;
	return result;
}

/*
	遍历输出结果
*/
void PrintResult(std::vector<int> v, int arr[]){
	std::cout << "----------------begin------------" << std::endl;
	for(auto item : v){
		std::cout << item << ": " << arr[item] << endl;
	}
	std::cout << "----------------end------------" << std::endl;
}

int main(){
	//测试cal1
	int arr[7] = {7,10,2,6,19,22,32};
	vector<int> result = cal1(arr,7);
	PrintResult(result,arr);

	//测试cal2
	result = cal2(arr,7);
	PrintResult(result,arr);
	return 0;
}