#include <iostream>
#include <queue>  //C++中有现成的泛型的queue
#include <mutex>  //C++11中加入mutex相关操作类(最常用std::mutex)，用于并发操作
using namespace std;

/*
	这里将MingW升级到了6.0，可以引入mutex，但是实际操作发现提示一个"mutex does not name a type"。通过搜索知道可能的原因是MingW版本的g++没有实现相应的线程操作。	
*/

/*
	queue默认是deque的，deque有两级数组结构，一级表示实际的容器，一级指向容器的首和尾。
	queue的主要操作：
		q.push插入到末端
		q.pop将首部的第一个元素弹出
		q.front() 返回首部元素
		q.back()  返回尾部元素 
		q.empty()
		q.size() 返回当前的元素的个数
*/

typedef int ElementType;
queue<ElementType> q;  //要操作的队列
std::mutex readMutex;  //读锁
mutex writeMutex; //写锁

/*
	写操作  不能多个同时写  写的时候不能读
*/

/*
	读操作 可以多个同时读 但是读的时候不能写
*/

int main(){

	
}