#include <iostream>
#include <algorithm>
using namespace std;

/*
问题描述：
	在一个数组中，存在一个元素出现的次数超过了数组长度的1/2，找出这个元素。
	--问题延伸： 如果是在一个数组中，已知一个元素出现的次数超过了1/3，又如何找出这个元素
分析：
	1)一个一般性的想法：将数组进行排序，那么arr[n/2]就是目标元素，原因很简单这个元素个数超过数组长度一半的元素无论是从数组左边开始都是较小值还是从数组最后面往前排都是较大值，由于其个数超过了总长度的一般，所以中间位置一定是这个元素。如果用快排之类的排序这个直观算法的复杂度是O(nlog(n))
	2）如果一个元素已知出现的次数超过了1/2，那么也就是这个元素的个数超过了其他所有元素的总和。假设使用一个计数，初始为0，这个计数在出现的元素的要找的出现次数超过1/2的元素的时候就进行计数加一，在出现的元素不是要找的出现次数超过1/2的元素的时候就进行减一，那么遍历这个数组之后的结果这个计数一定是大于0的。
	上面的思路，仅仅是根据条件是如果已知有这么一个元素的个数超过了1/2，是通过这个已经的性质进行求解输出的。但是如果前提并不知道是否存在次数超过1/2的元素的时候，这个求解就可能是失效的。也即是这种思路只能在确定存在这个元素的前提下找到它而没有办法证明超过1/2的元素一定存在。给定一个简单的例子，一个数组中每个元素都不一样，并且数组长度为奇数(>=3)，通过上面的思想会找到最后一个元素，然后这种情况下是不存在某一个元素的个数超过总的元素个数的一半的。对于可能并不存在次数超过1/2的情况，可以再次遍历一次这个数组进行出现次数的验证。通过反证法可以很容易的得到如果确实存在次数超过了数组长度的一半的元素那么最后的标记元素一定是这个目标元素，那么上面的一次遍历验证也就是有效的。
分析扩展：如果一个元素个数超过了1/3，找出它。
*/


/*
	算法1）：获取一个数组中出现次数超过1/2的元素，复杂度O(nlog(n))
@param int input[] 要进行计算的输入数组。
@param int length 输入的数组的长度
@param bool validate=false  是否进行验证，如果确定真的存在出现次数超过数组长度一半的元素，就不用进行验证，参数设置为默认的false，不验证。否则需要遍历数组进行验证，参数需要传入true
@return int 如果没有进行验证直接返回目标元素。如果设置了验证，只有在确实存在相应的元素个数超过了数组长度的一半的情况下才返回目标元素，在不存在的目标元素超过数组长度一半并且进行了验证的情况下返回0x7fffffff
@note  注意，这个算法对原输入的数组进行了排序，破坏了原来的结构，这在有些地方是不允许的。
*/
int GetPercentageOutOfHalf1(int input[], int length, bool validate=false){
	if(!input || length <= 0){
		std::cerr << "the input array is null or the length is invalidate" << std::endl;
		return 0x7fffffff; //实际操作的中应该进行错误异常处理，这里返回一个最大的int类型的整数，仅仅是一个标志。
	}

	//排序
	sort(input,input + length);
	
	//获取结果
	int result = input[length / 2];

	//根据输入判断是否进行验证
	if(validate){
		//进行验证  遍历数组统计最后保留下来的result是否出现到次数真的超过了1/2
		int count = 0;
		for(int i = 0; i < length; ++i){
			if(input[i] == result)
				count++;
		}
		if(count <= length/2){
			//并没有这样的出现次数超过数组长度一半的元素，异常处理
			std::cerr << "there is no element in the array whose percentage is more than 50 percent" << std::endl;
			return 0x7fffffff;
		}
	}
	return result;
}


/*
	算法2）：获取一个数组中出现次数超过1/2的元素，复杂度O(n)
@param int input[] 要进行计算的输入数组。
@param int length 输入的数组的长度
@param bool validate=false  是否进行验证，如果确定真的存在出现次数超过数组长度一半的元素，就不用进行验证，参数设置为默认的false，不验证。否则需要遍历数组进行验证，参数需要传入true
@return int 如果没有进行验证直接返回目标元素。如果设置了验证，只有在确实存在相应的元素个数超过了数组长度的一半的情况下才返回目标元素，在不存在的目标元素超过数组长度一半并且进行了验证的情况下返回0x7fffffff
*/
int GetPercentageOutOfHalf2(int input[], int length, bool validate=false){
	if(!input || length <= 0){
		std::cerr << "the input array is null or the length is invalidate" << std::endl;
		return 0x7fffffff; //实际操作的中应该进行错误异常处理，这里返回一个最大的int类型的整数，仅仅是一个标志。
	}
	int result, num = 0;
	for(int i = 0; i < length; ++i){
		if(!num){
			result = input[i];
			num++;
		}else if(result == input[i]){
			num++;
		}else{
			num--;
		}
	}
	//根据输入判断是否进行验证
	if(validate){
		//进行验证  遍历数组统计最后保留下来的result是否出现到次数真的超过了1/2
		int count = 0;
		for(int i = 0; i < length; ++i){
			if(input[i] == result)
				count++;
		}
		if(count <= length/2){
			//并没有这样的出现次数超过数组长度一半的元素，异常处理
			std::cerr << "there is no element in the array whose percentage is more than 50 percent" << std::endl;
			return 0x7fffffff;
		}
	}
	return result;
}



int main(){
	//GetPercentageOutOfHalf1  存在目标元素的情况下进行验证
	int arr1[10] = {2,1,1,2,1,3,1,1,1,6};
	cout << GetPercentageOutOfHalf1(arr1,10) << endl;
	cout << GetPercentageOutOfHalf1(arr1,10,true) << endl;
	
	cout << "---------------分割线---------------" << endl;
	
	//GetPercentageOutOfHalf1  不存在目标元素的情况下进行验证
	int arr2[10] = {1,2,3,4,5,6,7,8,9,10};
	cout << GetPercentageOutOfHalf1(arr2,10) << endl; //没有经过验证，输出了错误的结果9 
	cout << GetPercentageOutOfHalf1(arr2,10,true) << endl;

	cout << "---------------分割线---------------" << endl;

	//GetPercentageOutOfHalf2  存在目标元素的情况下进行验证
	int arr3[10] = {2,1,1,2,1,3,1,1,1,6};
	cout << GetPercentageOutOfHalf2(arr3,10) << endl;  //1
	cout << GetPercentageOutOfHalf2(arr3,10,true) << endl; //1

	cout << "---------------分割线---------------" << endl;

	//GetPercentageOutOfHalf2  不存在目标元素的情况下进行验证
	int arr4[10] = {1,2,3,4,5,6,7,8,9,10};
	cout << GetPercentageOutOfHalf2(arr4,10) << endl; //没有经过验证，输出了错误的结果6 
	cout << GetPercentageOutOfHalf2(arr4,10,true) << endl;
	return 0;
}