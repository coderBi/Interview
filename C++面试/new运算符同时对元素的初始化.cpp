#include <iostream>
using namespace std;

class Test{
public:
	int x = 1;
	Test(int x){
		this->x = x;
	}
};

int main(){
	//new单个基本类型
	int *i1 = new int(10);	
	cout << *i1 << endl;
	delete i1;

	//new基本类型数组
	//int *i2 = new int[2](10);	//报错，只能使用没有参数的初始化
	int *i2 = new int[2]();	
	cout << *(i2+1) << endl;
	delete[] i2;

	//new单个对象
	Test *t1 = new Test(10);	
	cout << t1->x << endl;
	delete t1;

	//new对象数组
	//Test *t2 = new Test[2](10);//报错，只能使用无参数的构造	
	Test *t2 = new Test[2](); //报错，因为没有提供无参的
	cout << (t2+1)->x << endl;
	delete [] t2;

	//最后测试初始化效果
	int *p1 = new int; //垃圾值
	int *p2 = new int(100); //初始化为100
	cout << *p1 << "-----------" << *p2 << endl;
	return 0;
}