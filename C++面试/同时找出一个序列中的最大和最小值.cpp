#include <iostream>
using namespace std;

/*
题目描述：
	在n个整数的序列中，要计算出最大值和最小值，至少需要多少次比较：A.2n-2 B.3n/2 C.n-1 D.4n/3
答案与分析：
	1）按照一般性写法，用两个变量分别保存最大和最小值，初始的时候将这两个值都设置为arr[0]，然后遍历这个数组，通过对每一个元素与最大最小值的比较和互换最终确定这个序列的最大和最小值。这个比较的次数是 2(n-1)
	2）因为要计算的是最大和最小值，可以先进行没两个两个的比较，将这个比较中间较大的放到一个数组，将较小的放到一个数组。然后利用上面1）的描述分别在两个子序列中找出最大和最小值（这个算法如果要追求不用空间上的优化，可以直接将奇数位设置为较小，偶数位设置为较大，不过这样导致了输入数组的更改）。这个算法的复杂度是 n/2 + (n/2 - 1) + (n/2 - 1)近似为3n/2
	----下界分析：能够优化上面思路1）的部分，应该是在尽可能的不让每一个数据都和最大最小值进行比较，而如果对于任意一个数只要知道它不能是最大值就不用和最大值比较，同样的分析适用于最小值。那么这个优化方案也就是在内部两两配对进行分组。这样与最大值最小值的比较次数缩减了一半，从2n-2次缩减为n-1次，但是内部产生了n/2次比较。所以要同时计算出最大最小值需要的比较次数应该不少于3n/2。
*/

/*
	算法1）实现：常规思路，比较次数为2n-2
@param int input[] 要进行查找的输入数组
@param int length 输入数组的长度
@param int max 用于返回计算得到的最大值
@param int min 用于返回计算得到的最小值
*/
void cal1(int input[], int length, int &max, int &min){
	if(length <= 0){
		std::cerr << "the input array is empty" << std::endl;
		return;
	}
	//初始max min
	min = max = input[0];
	//遍历数组后续元素 分别与最大最小值进行比较  进行最大最小值的调整
	for(int i = 1; i < length; ++i){
		//通过书写代码的过程，发现下面的代码其实也是可以进行优化的，原因是如果min > input[i]，那么由于max >= min就不能存在 max < input[i]，通过这么一分析，这里的实际比较次数可以进行降低。但是由于数据分布的不可控，这里即使修改为 if(min > input){}else if(max < input[i])也还是可能出现所有的数据都需要执行两个if（例如第一项就是最小值）。鉴于这里的代码对于实际使用存在价值，所以还是进行了相应的修改优化
		if(min > input[i])
			min = input[i];
		//if(max < input[i]) //这里是未优化
		else if (max < input[i]) //这里是一个逻辑上的优化，对于实际效率可能会有提升
			max = input[i];
	}
}


/*
	算法2）实现：先在数据内部进行分组，然后在可能的最大值中寻找最大值，在可能的最小值中间寻找最小值。
		这个实现这里使用了额外的数组，比较的次数为3n/2
@param int input[] 要进行查找的输入数组
@param int length 输入数组的长度
@param int max 用于返回计算得到的最大值
@param int min 用于返回计算得到的最小值
*/
void cal2(int input[], int length, int &max, int &min){
	if(!input || length <= 0){
		std::cerr << "the input array is null or empty" << std::endl;
		return;
	}
	int * low = new int[length];
	if(!low){
		std::cerr << "new memory fail" << std::endl;
		return;
	}
	int * high = new int[length];
	if(!high){
		std::cerr << "new memory fail" << std::endl;
		delete [] low;
		return;
	}
	//对输入的input进行分组
	int lowLen = 0, highLen = 0;
	//如果是奇数，那么将最后一个元素先加入到两个数组中
	if(length / 2)
		low[lowLen++] = high[highLen++] = input[length -1];
	for(int i = 0; i < length - 1; i += 2){
		if(input[i] <= input[i+1]){
			//一个小细节，如果相邻的这两项相等，那么两个相同的项进入到两个数组，这种处理没有向任何一遍倾斜，不会造成一头大一头小的两个数组.
			low[lowLen++] = input[i];
			high[highLen++] = input[i+1];
		}else{
			low[lowLen++] = input[i+1];
			high[highLen++] = input[i];			
		}
	}
	//在high中寻找最大值  在low中寻找最小值  由于lowLen和highLen其实是一样的，所以下面的代码（其实上面的分组代码中的变量二者也可使用一个）中两个for是可合并的，这里暂不给出合并的代码
	max = high[0];
	min = low[0];
	for(int i = 1; i < lowLen; ++i){
		if(min > low[i])
			min = low[i];
	}
	for(int i = 1; i < highLen; ++i){
		if(max < high[i])
			max = high[i];
	}
	//资源释放
	delete [] low;
	delete [] high;
}


int main(){
	//测试
	int max,min;
	int arr[10] = {3,5,2,4,4,0,2,9,1,5};

	cal1(arr,10,max,min);
	cout << max << "..........." << min << endl;

	cal2(arr,10,max,min);
	cout << max << "..........." << min << endl;
	
	return 0;
}