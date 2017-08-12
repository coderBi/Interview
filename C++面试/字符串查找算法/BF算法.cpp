#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;

/*
BF算法分析：
	在字符串s1中查找s2首次出现的位置.
	作为字符串查找算法，BF算法是一种显而易见的算法，也就是从s1[0],s1[1]......s1[M-N](M为s1的长度,N为s2的长度)为开头查找s1中的对应的子字符串看是否与s1完全匹配。这个算法的复杂度是O((M-N)*N)
测试过程的小细节：
	在测试用发现一个问题，如果第一个函数BF(const char* s1, const char* s2)的前面改成了BF(char*,char*)，那么第二个BF(string,string)函数在调用的时候会出问题（进入死循环）。原因是：string.c_str()返回的是const char* ,这个类型不能传递给char*，但是可以传递给string进行string的初始化，所以BF(string,string)内部调用BF(s1.c_str(),s2.c_str())会匹配到BF(string,string)这一个重载形式.
后续发现的一个小点：
	对于 s1 = s2 = "" 这样的情况，下面的BF函数会返回0，而实际上对于原来的数组，使用0脚标进行访问得到的是‘\0’字符，没有越界，返回0好像是合理的。进一步从常识的角度进行分析，这个结果也是可以接受的。
*/

/*
	使用BF算法在一个字符串中查找另一个字符串首次出现的位置
@param const char * s1 容器字符串
@param const char * s2 要查找的目标子字符串
@return int 如果找到了相应的子字符串就返回首次出现的位置，如果没有找到返回-1
*/
int BF(const char * s1, const char * s2){
	assert(s1 && s1);  //assert宏用于在debug的模式下进行检测，如果是release的模式会自动删除这个宏
	int M = strlen(s1), N = strlen(s2);
	if(M < N)
		return -1;
	for(int i = 0; i <= M - N; ++i){
		int j = i,k = 0; //j为s1中位置的移动脚标  k为s2中位置的移动脚标
		for(; k < N; ++j,++k){
			if(s1[j] != s2[k])
				break;
		}
		if(k == N)
			//找到了
			return i;
	}
	return -1;
}


int main(){
	//char * s1 = "elloworldhello", *s2 = "dhello"; //报一个错误，原因是C++中字符串常量(存储在常量区)不允许赋值给char*，因为常量区的内容是不允许进行更改的（注意C语言中尽管可直接进行char*的赋值，但是也不能利用这个指针进行常量区的更改）。不过为了兼容C，是可以使用string去初始化一个字符串数组的。另外，由于const char* 保证了内容的不会被更改，所以可以使用常量区的字符串直接对const char*进行赋值.
	char s1[] = "elloworldhello", s2[] = "dhello";
	cout << BF(s1, s2) << endl;

	cout << BF("hello world", "world") << endl;

	cout << BF("", "") << endl;
	return 0;
}