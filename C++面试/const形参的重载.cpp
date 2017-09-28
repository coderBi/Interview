#include <iostream>
using namespace std;

/***********普通函数中的const参数的重载	START ***************/
/*
note:
	下面的两个函数的形参如果是int i和const int i。那么是不能构成重载的，因为这样书写进行值传递，解释一样的，都是传递一个int。
	而书写成int* 和 const int * 二者传递的指针的类型不同，一个指向const int，一个指向int。同样的解释适合引用
*/

/*引用的参数const与非const重载*/
void print(int& i){
	cout << "print i :" << i << endl;
}

void print(const int& i){
	cout << "print const i :" << i << endl;
}

/*指针的参数的const与非const的重载*/
void print(int* i){
	cout << "print i :" << i << endl;
}

void print(const int* i){
	cout << "print const i :" << i << endl;
}
/***********普通函数中的const参数的重载	END ***************/

/***********类中方法的const参数的重载	START ***************/
/*
note:
	类中方法的const修饰在了隐式传递的this指针上面，表示不能通过this进行相应对象属性的修改。也就是将一个指针参数的指向修饰为了const的。所以构成了重载
*/
class Test
{
public:
	void print(){
		cout << "no const method" << endl;
	}
	void print() const{
		cout << "const method" << endl;
	}
};
/***********类中方法的const参数的重载	END ***************/

int main(){
	print(1); //打印print const i。原因是1是一个临时变量，类型是const int
	const Test t;
	t.print(); //const method
	return 0;
}