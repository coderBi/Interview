#include <iostream>
#include <assert.h>
using namespace std;

/*
题目描述：
	设计一个strcpy函数
分析：
	主要的细节点有：对于字符串为null的断言  源字符串需要用const修饰，这样更严谨  返回原来的目标字符串，方便链式操作

*/

char * strcpy(char * dest, const char * src){
	assert(dest && src);
	char * toReturn = dest;
	while(*dest++ = *src++){}
	return toReturn;
}
int main(){
	char str[10];
	cout << strcpy(str, "hellow") << endl;
	return 0;
}