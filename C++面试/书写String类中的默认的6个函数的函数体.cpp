#include <iostream>
#include <cstring>
using namespace std;

/*
问题：
	1）对于每一个类都存在6个默认的函数：默认构造函数  拷贝构造函数  赋值运算符  取值运算符  const取值运算符
	2) 对于string类的这6个默认的函数给出函数体
编码要点：
	1）构造函数中需要对string里面的char*构建所指向的空间，析构中需要释放内部的char*所执行的空间
	2) 拷贝构造函数的形参应该是引用而不是对象类型，因为如果是对象类型会在实参到形参的初始化过程中再用拷贝构造函数本身
	3) 拷贝构造函数，应该处理一个特殊情况，就是如果传入的参数是调用对象本身，那么应该直接返回，否则可能对同一片的空间出现先释放后引用的问题
	4）对于const的取址函数的返回值应该是const指向的，因为取址返回的是调用对象的本身地址（也就是this），而const的约束指明当前的this指向是const的。所以返回值应该是const指向的。

*/

class MyString
{
private:
		char * m_data;
public:
	/*默认构造函数*/
	MyString(const char* pData = nullptr){
		if(!pData){
			//构建空的字符串
			this->m_data = new char[1]();
			return;
		}
		//分配内存 拷贝数据
		strcpy(this->m_data = new char[strlen(pData) + 1](), pData);
	}
	/*拷贝构造函数*/
	MyString(const MyString & other){
		this->m_data = new char[strlen(other.m_data) + 1]();
		strcpy(this->m_data, other.m_data);
	}
	MyString * operator &(){
		return this;
	}
	const MyString* operator &() const{
		return this;  //同样是this，但是这里传入的this是指向的const对象的	
	}
	/*赋值运算符  这里返回当前对象，是为了可能的链式操作*/
	MyString& operator =(const MyString & other){
		//判断是否是同一个对象
		if(this == &other)
			return *this; //返回当前对象
		//先释放当前对象的资源
		delete [] this->m_data;
		//复制另一个对象的内容  这里要进行深拷贝
		this->m_data = new char[strlen(other.m_data) + 1]();
		strcpy(this->m_data, other.m_data);
	}
	/*析构*/
	~MyString(){
		//释放内部资源
		delete[] this->m_data;
	}

	/*为了方便测试，这里重载 << 运算符*/
	//使用成员函数重载的形式 不过只能使用成员函数调用 
	std::ostream& operator <<(std::ostream& stream){
		return (stream << this->m_data);  
	}
	//使用友元函数定义，这样可以使用二元运算符 << 的形式在代码中直接使用
	friend std::ostream& operator <<(std::ostream& stream, const MyString & obj){
		return (stream << obj.m_data);  
	} 
};

int main(){
	MyString s1 = "hello world"; //调用构造函数
	s1.operator <<(cout); //使用成员函数调用输出，参数指定一个流
	cout << endl << s1 << endl; //友元,<<的两边分别传给第一个和第二个参数
	return 0;
}