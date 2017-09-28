#include <iostream>
#include <vector>
using namespace std;

/*
问题：
	看到一个描述：对于一个装类类型的容器中元素的初始化，是先利用类的默认构造函数（也只能使用默认类型的构造函数，因为没有指定构造函数的接口，例如vector<Test> test(100), 后面括号中的参数指定的是这个容器中元素的个数）构造一个临时对象，然后利用这个临时对象调用拷贝构造函数对容器中的一个个对象空间进行填充
分析：
	这里通过重载默认的构造函数和拷贝构造函数，在其中打印相应的结果，进行验证判断
结果：
	1）书上的这个说法存在问题，这里发现结果是容器中有多少个元素就调用多少次的默认构造函数。
	2）为了验证不同的编译器是是否存在差别，又去VS下面进行了测试，与这里gcc的结果一样。
	3）通过多番测试说明，一个放了n个对象元素的容器的初始化是调用n次默认构造函数进行的。
*/

class Test
{
public:
	int i;
	Test(){
		cout << "default create constructor" << endl;
		this->i = 100;
	}
	Test(Test & other){
		cout << "copy constructor" << endl;
		this->i = 99;
	}
};

int main(){
	vector<Test> test(3); //打印的结果是调用了3次默认构造函数，没有调用拷贝构造函数
	for(Test & t : test){
		cout << t.i << endl; //可以看到三个值都是100，再次证明了没有调用拷贝构造函数
	}

	//调用了拷贝构造函数，可以看到拷贝构造函数是正常工作的
	Test t = test[0];
	cout << t.i << endl; //99
	return 0;
}