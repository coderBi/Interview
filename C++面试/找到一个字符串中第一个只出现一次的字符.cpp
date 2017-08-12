#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

/*
题目描述：
	找出一个字符串中第一个只出现一次的字符。例如abaccdeff，会输出b。假设所有的字符都是assic的。
分析：
	利用一个hash结构存储每一个字符出现的次数，遍历输入的字符串，填充这个hash。由于要找到“第一个”，那么再遍历一次输入的字符串，如果找到某一个字符刚好出现次数是1的就返回。
*/

/*
	获取一个字符串中第一个只出现一次的字符
@param const char * str 要查找的字符串
@return 如果找到了就返回这个字符串中第一个只出现一次的字符。如果没有这样的字符存在就返回 '\0'
*/
char GetOnlyOnce(const char * str){
	assert(nullptr != str);
	int hash[256] = {0}; //保存每一个assic字符出现的次数
	//遍历字符串  填充hash
	const char * p = str;
	for(;*p;p++)
		hash[*p]++;
	//遍历字符串，判断字符出现的次数
	for(p = str; *p; p++){
		if(1 == hash[*p])
			break;
	}
	return *p;
}

int main(){
	cout << GetOnlyOnce("abbaccdeff") << endl;
	return 0;
}