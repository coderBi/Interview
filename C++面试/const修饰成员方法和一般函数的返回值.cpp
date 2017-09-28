#include <iostream>
using namespace std;

/*-------------一般函数：const修饰返回值  START--------------------*/
const int f1(){
	cout << "f1" << endl;
	return 110;
}
/*-------------一般函数：const修饰返回值  END--------------------*/

/*-------------成员函数：const修饰this指针  START--------------------*/
class Test
{
public:
	int f2() const{
		cout << "f2" << endl;
		return 888;
	}
};
/*-------------成员函数：const修饰this指针  END--------------------*/

/*-------------一般函数：const不合法用法  START--------------------*/
/*
	下面的函数出现编译错误：non-member function cannot have cv-qualifier（非成员函数不能有cv 限定符），cv限定符指的是const 和 volatile修饰。也就是说一般的函数不能用这两个关键词修饰
*/
int f3() const{
	cout << "f3" << endl;
	return 999;
}
/*-------------一般函数：const不合法用法  END--------------------*/

int main(int argc, char* argv[]){

	return 0;
}