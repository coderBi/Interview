#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

/*
题目描述：
	如何判断一个字符串中是否所有的字符都是不同的。
分析：
	利用hash结构存储是否一个字符在字符串中存在，然后遍历这个输入字符串，对于当前字符对应在hash结构中不存在，就将状态设置为已经存。如果hash中给出的结果是已存在，那么这个字符就出现了2次，直接可以返回false。这如果要降低空间的要求，可以考虑使用bit-map，因为一个位已经够用来表示一个字符的是否已经出现的状态了。
后续：
	如果要进一步优化空间，由于这里用的是一个bool，可以使用bit-map进行状态保存，每一个bit位保存一个字符对应是否已经出现的状态
*/

/*
	判断一个字符串中是否所有的字符都是不同的。
@param const char * str 要查找的字符串
@return 所有的字符都不同就返回true，否则返回false
*/
bool AllDifferentInString(const char * str){
	assert(nullptr != str);
	bool hash[256] = {0}; //保存每一个assic字符是否已经出现 
	for(const char * p = str; *p; p++){
		if(hash[*p])
			return false;
		hash[*p] = true;
	}
	return true;
}

int main(){
	cout << AllDifferentInString("abcdef") << endl;
	cout << AllDifferentInString("abecdef") << endl;
	return 0;
}