#include <iostream>
#include <assert.h>
using namespace std;

/*
题目描述：
	一个整数的序列中，除了两个数字只出现1次之外，其他的数字都成对的出现。要求在时间复杂度为O(n)空间复杂度O(1)的条件下找出这两个数字.
分析：
	将整个的序列进行异或的运算，最后留存下来的结果某一位为1表示这两个数字只有一个在这一位是1（由于这两个数字并不完全相同，所以最后的结果一定不会完全抵消）。可以将最后留下来的这个结果的最低位的1当做区分这两个元素的标志。利用这一位可以将原来的整个序列分为两个部分，并且要寻找的两个数字各属于不同的部分。由于其他的元素都是成对的出现的，所以在分成的这两个部分中，它们依然是成对出现的，然后再在这两个子序列中执行前面说的异或运算就可以分别得到这两个数字了.
进一步的补充分析：
	1）对于如果只有一个没有成对出现的整数序列，只需要进行所有的数字的异或就可以取出来这个独特的数字，这个分析是基于两个完全相同的数进行异或得到的是0，任何数与0进行异或得到的还是其本身（隐含一个条件，异或运算是满足交换律的）。
	2）上面的进一步分析实现了寻找一个整数序列中有两个元素不成对出现的情况，这个分析是基于如果将这个序列所有的数字进行异或那么最终得到的那个结果中为1的位表示要寻找的那两个数字在这一位只有一个是1，另一个一定是0，这是由于异或的性质决定的，基于这判断，可以这个结果中某一位的1进行区分最终要寻找的两个数（具体的可以利用这一位取出两个部分，一部分是这一位为1的，另一部分是这一位为0的，然后就可以在两个部分中分别取出两个要寻找的结果）。
	3）通过上面的分析，我们知道是可以找到只有一个没有配对的元素的，也可以找到只有两个没有配对的元素。接下来的分析有两个部分：一是是否可以找有3个或者更多的没有配对的元素，前提也是时间复杂度为线性而空间复杂度为常量。另一个问题是是否可以在没有给定的到底有多少个没有配对的元素的前提下，找出究竟有多少个没有配对的元素并且找到它（们），如果这个查找没有普适性那么是否可以对某些特例适用（例如，对于如果只有一个元素重复，我们通过异或得到一个结果，然后再遍历一次序列查找在其中是否真的存在这个结果，如果存在这个数字是否可以意味着就是只有一个元素只出现了一次???），对于这个问题的描述，直观上看时间复杂度达不到线性，原因是存在所有的元素各不相同的可能，这个时候如果空间复杂度为O(1)（也就是不适用hash映射）能想到的算法基本都是二次的了。
*/

/*
	找出一个整型序列中只有两个没有成对出现的元素
@param int arr[] 输入的整型序列
@param int length 序列的长度
@param int &res1 用于接受要返回的结果数字1
@param int &res2 用于接受要返回的结果数字2
*/
void Get2NoMatchInArray(int arr[], int length, int &res1, int &res2){
	assert(arr && length >= 2); //length如果为1下面的结果会出现一个是为这个元素本身，另一个是0.
	int result = 0;
	//获取整个序列中所有的数字进行异或运算的结果
	for(int i = 0; i < length; ++i)
		result ^= arr[i];
	int unique = 1;
	//获取可区分最终两个数字的从低位到高位的第一个1
	while(unique && !(unique & result)){
		unique <<= 1;
	}
	if(!unique){
		//没有找到可区分两个数字的某一位1，说明整个序列进行异或运算的结果result是0。判断为给定序列错误.这里考虑打印错误日志，但是对于api调用来说这里合理的做法应该给出一个调用异常(C++异常个人使用不习惯)
		std::cerr << "the sequence given does not contains two different numbers that do not equal to others" << std::endl;
		return;
	}
	//找出区分位为1的结果和区分位为0的结果
	res1 = 0;
	res2 = 0;
	for(int i = 0; i < length; ++i){
		if(unique & arr[i])
			res1 ^= arr[i];
		else
			res2 ^= arr[i];
	}
}



int main(int argc, char* argv[]){
	int arr[10] = {1,1,3,4,3,5,6,6,5,9};
	int res1, res2;
	Get2NoMatchInArray(arr, 10, res1, res2);
	cout << res1 << "------" << res2 << endl;
	return 0;
}