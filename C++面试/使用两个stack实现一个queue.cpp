#include <iostream>
#include <stack>
using namespace std;

/**
* 使用两个stack实现的queue
*/
template<class T>
class MyQueue
{
private:
	stack<T> in, out; //插入栈、读取栈
public:
	bool empty(){
		return in.empty() && out.empty();
	}
	T front(){
		//如果输出栈为空，将输入栈的所有元素压入输出栈
		if(out.empty()){
			//将输入栈中的所有元素都压入输出栈
			while(!in.empty()){
				out.push(in.top());
				in.pop();
			}
		}
		//取出输出栈的栈顶元素 返回
		return out.top();
	}
	void push(T e){
		out.push(e);
	}
	void pop(){
		//如果输出栈为空，将输入栈的所有元素压入输出栈
		if(out.empty()){
			while(!in.empty()){
				out.push(in.top());
				in.pop();
			}
		}
		//弹出输出栈的栈顶元素
		if(!out.empty())
			out.pop();
	}
	int size(){
		return in.size() + out.size();
	}
};

int main(){
	//测试
	MyQueue<int> mq;
	cout << mq.size() << endl; //0
	mq.push(11);
	cout << mq.front() << endl; //11
	cout << mq.size() << endl; //1
	mq.pop();
	cout << boolalpha << mq.empty() <<endl; //true
	return 0;
}