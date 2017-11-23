#include <iostream>
using namespace std;

/*
问题描述：
	用数组实现循环队列
分析：
	因为头和尾部如果一直都往后走，前面的空间就浪费了，所以队列一般是循环的。使用数组构建循环队列，使用head和tail标记队首和队尾。一开始head和tail都在数组0脚标位置，如果插入tail就会加1，如果删除head就会加1，在到达数组的末尾的时候可以将他们重新调整为0。可以通过head==tail判断队列为空，可以很容易知道如果一个数组的长度是n，那么设计的队列的最大容量是n-1，因为假设head不动tail在插入第n个元素的时候会head重合，而这种情况队列被判定为空。
*/

template<class T>
class MyQueue
{
	T *data;
	int head, tail, length; //队首、队尾、数组长度
public:
	MyQueue(int length = 10){
		this->length = length;
		head = tail = 0;
		data = new T[length];
		if(!data){
			std::cerr << "new memory error" << std::endl;
		}
	}
	//判断是否为空
	bool empty(){
		return head == tail;
	}
	//判断是否满了
	bool full(){
		return length - 1 == (tail + length - head) % length; //因为tail可能比head还小，所以这里加上一个length.
	}
	//插入元素
	bool push(T e){
		if(full())
			return false;
		data[tail++] = e;
		tail %= length;
		return true;
	}
	//删除元素
	void pop(){
		if(empty())
			return;
		head = (head + 1) % length;
	}
	//获取队首元素
	T front(){
		//note：这里有一个逻辑问题，在取元素的时候是否应该判断是否为空。实际上一般是在调用的时候判断是否为空，然后进行取。如果这里再加一个为空判断就有点多余，还有就是这种异常可以认为不是“取”这个动作引起的，而是使用这个动作不当引起的。所以这里不加上为空判断，而是直接取元素。
		return data[head];
	}
	//获取大小
	int size(){
		return (tail + length - head) % length;
	}
	~MyQueue(){
		//释放内部数组
		delete data;
	}
};

int main(){
	//测试
	MyQueue<int> mq(2); //提供的数组的长度是2，那么这个队列容量为1
	cout << boolalpha << mq.empty() << endl; //true
	cout << boolalpha << mq.full() << endl; //false
	cout << boolalpha << mq.push(1) << endl; //true
	cout << boolalpha << mq.full() << endl; //true
	cout << boolalpha << mq.push(2) << endl; //false 已经满了，插入失败
	cout << boolalpha << mq.front() << endl; //1
	mq.pop();
	cout << boolalpha << mq.empty() << endl; //true

	cout << boolalpha << mq.push(2) << endl; //true
	cout << mq.front() << endl; //2
	return 0;
}