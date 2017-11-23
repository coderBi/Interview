#include <iostream>
#include <assert.h>
#include <memory.h>
#include <algorithm>
using namespace std;

/*
问题描述：
	过桥问题：a、b、c、d四个人过桥的时间分别为1、2、5、10，现在只要一个手电筒，如果两个人同时过桥那么过桥时间是较慢的那个。应该如何安排过桥使得整体的过河时间为最短。
分析：
	在经典的过桥问题中，是只有两个人可以同时过河。因为只有一个手电筒，那么必须有一个过了河的人回来送手电筒。考虑到松手电筒的一定是过了河的速度较快的，那么问题可以转变为先将最慢的两个人送过河，然后将余下的人送过河(同样的子问题)，之所以是送两个人过河为一个步骤，因为两个最慢的如果和集体中其他的人时间相差很大，那么这两个人同时过河可以明显的缩短整体的时间，可是如果他们和其他的成员的过河时间相差不是很大，那么有可能一直用最快的送两者过河的时间会出现更优(因为缩减了两次的返回时间，两次返回的都是第一快)。例如设最快的时间依次为x,y，而最慢的依次为m,n，其中x < y < m < n。那么上面的描述的两种的用时在最慢的两个同时过桥的时候是y + x + n + y，在一直用最快的送二者过桥的时候是 m + x + n + x。两个时间相减为2y - x -m。上面的的描述是一个贪婪的过程，也就是每一次都送最慢的两个人过河。
*/

/**
* 获取过桥问题的最小时间。这里的过桥每次最多两人，只有一个手电筒。
*
* @parem int times[] 所有人的过桥时间数组
* @param int number 人数
* @param bool sorted = false 是否传入的时间数组已经排好序，默认是false
* @exception string 内部分配空间出错
* @return int 返回过桥的最短时间
*/
int MinTimeCrossTheBridge(int times[], int number, bool sorted = false){
	assert(times && number > 0);
	int *_times = times; 
	//如果传入需要进行排序，那么在内部进行数组拷贝，不去直接操作原数组
	if(!sorted){
		_times = new int[number];
		if(!times)
			throw "内部空间分配出错";
		memcpy(_times, times, number * sizeof(int)); //是C函数，C中没有命名空间，所有函数都在全局空间中
		//排序_times
		std::sort(_times, _times + number);
	}
	if(number < 3)
		//只需要一趟就过完了，所以返回最慢的时间就行
		return _times[number - 1];
	if(number == 3){
		//只要三个人，那么只要一种情况就是使用最快的松另外两个过桥
		return _times[2] + _times[0] + _times[1];
	}
	int result = std::min(_times[1] + _times[0] + _times[number - 1] + _times[1],
							_times[number - 1] + _times[0] + _times[number - 2] + _times[0]
						) +
						MinTimeCrossTheBridge(_times, number - 2, true);
	//内部空间释放
	if(!sorted)
		delete[] _times;
	return result;
}

int main(){
	//测试
	int times[] = {1,2,5,10};
	cout << MinTimeCrossTheBridge(times, 4) << endl; //17 = 2 + 1 + 10 + 2 + 2
	return 0;
}