#include <iostream>
using namespace std;

/*
题目描述：
	考虑这么一个问题，一个数组int arr[] = {2,3,4,5}，定义一种运算，f[i]为数组上除了arr[i]其他所有的其他数据元素的乘积。要求复杂度尽可能的低
	函数签名格式为： int * cal(int * input, int n)
分析：
	1）显而易见的思路：分别计算每一个f[i] = arr[0] * .... * arr[i-1] * arr[i+1] * .... * arrp[n-1]。这个实现算法的时间复杂度是 O(n*n)。空间复杂度可以达到O(0),因为直接将要计算的结果保存在要返回的数组中。
	2）稍微有点经验的判断，就会发现上面的乘法进行了重复的计算，而且这个重复的量是很大的。一个利用空间换取时间的策略是：用O(n)从左到右扫描数组将前0~i-1项的乘积的结果保存为一个数组left[i]，同样用O(n)从右往左进行扫描，可以构建一个后i+1~n-1的乘积的结果数组right[i](两个结果数组中的边界情况的乘积设置为1)。最后利用这两个中间存储的状态数组计算result[i] = left[i] * right[i]。整个算法的复杂度大致为O(3n)，空间复杂度是两个中间状态的保存数组为O(2n)
	3）对于上面第二种算法，可进一步的优化其空间复杂度，利用经验可以知道这样的相邻的状态的值可简单递推的一般都存在空间复杂度的可能优化。可以这样考虑，先将left数组的值直接保存到result数组中，然后用一个中间变量存储i+1~n-1之间的元素的乘积，每一次向这个中间值上追加上新的因子的同时也就可以将这个乘积直接乘到原来的对应的result[i]上。这个改良后的算法时间复杂度依然是O(3n)(指的注意的是从右往左进行遍历的时候出列计算右边的乘积，还将左右两部分的乘积相乘计算出result[i]这一动作至于其中),这个算法的空间复杂度为O(1)，只用到了一个中间变量.
注意：
	下面的算法由于要返回一个数组，而这个数组只能值在函数内部进行new，所以这个空间应该由调用者进行释放。
*/

/*
	算法1）实现：复杂度O(n*n)
*/
int * cal1(int * input, int n){
	int * result = new int[n];
	if(!result){
		cout << "new memory fail" << endl;
		return nullptr;
	}
	//计算result
	for(int i = 0; i < n; ++i){
		result[i] = 1;
		for(int j = 0; j < n; ++j){
			if(j == i)
				continue;
			result[i] *= input[j];
		}
	}
	return result;
}

/*
	算法2) 实现: 复杂度O(n)
*/
int * cal2(int * input, int n){
	int * left = new int[n];
	if(!left){
		cout << "new memory fail" << endl;
		return nullptr;
	}
	int * right = new int[n];
	if(!right){
		cout << "new memory fail" << endl;
		//释放之前的left
		delete [] left;
		return nullptr;
	}
	int * result = new int[n];
	if(!result){
		cout << "new memory fail" << endl;
		//释放之前的left和right
		delete [] left;
		delete [] right;
		return nullptr;
	}
	//初始化left和right数组
	left[0] = right[n-1] = 1;

	//计算left数组
	for(int i = 1; i < n; ++i){
		left[i] = left[i-1] * input[i - 1];
	}
	//计算right数组
	for(int i = n-2; i >= 0; --i){
		right[i] = right[i+1] * input[i + 1];
	}
	//计算result数组
	for(int i = 0; i < n; ++i){
		result[i] = left[i] * right[i];
	}
	//释放left 和 right 空间
	delete[] left;
	delete[] right;
	//返回result数组
	return result;
}

/*
	算法3）：修改空间复杂度。时间复杂度为O(n)，空间复杂度为O(1)
*/
int * cal3(int * input,int n){
	int * result = new int[n];
	if(!result){
		std::cout << "new memory fail" << std::endl;
		return nullptr;
	}
	int right = 1;
	//计算左边的0~i-1的乘积
	result[0] = 1;
	for(int i = 1; i < n-1; ++i){
		result[i] = result[i-1] * input[i-1];
	}
	//从右往左进行遍历 计算right 计算result
	for(int i = n - 2; i >= 0; --i){
		right *= input[i+1];
		result[i] *= right;
	}
	return result;
}

/*
	遍历输出一个int数组
*/
void printArr(int arr[], int length){
	if(!arr){
		std::cout << "the array is null" << std::endl;
		return;
	}
	if(length <= 0){
		std::cout << "empty array" << std::endl;
		return;
	}
	for(int i = 0; i < length -1; ++i)
		//注意，之所以上面使用了using namespace std，但是这里依然使用std::cout，这是api设计风格，因为这个接口可能供给其他使用
		std::cout << arr[i] << " ";
	std::cout << arr[length -1] << std::endl;
}

int main(){
	//测试
	int test[] = {2,3,4,5};
	int * res1 = cal1(test,4);
	printArr(res1,4);
	int * res2 = cal2(test,4);
	printArr(res2,4);
	int * res3 = cal3(test,4);
	printArr(res3,4);
	
	//释放结果集
	delete[] res1;
	delete[] res2;
	delete[] res3;
	return 0;
}