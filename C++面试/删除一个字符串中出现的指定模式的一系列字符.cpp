#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
using namespace std;
/*
题目描述：
	删除一个字符串中出现的指定的模式串的字符。例如"abccdd" 删除指定的模式"cd"之后就成为了"ab"
分析：
	1）正常思路，是遍历查询的s1，然后用其中的每一个字符与模式串s2中的字符一一比对。设s1、s2的长度是M、N，那么这个算法的复杂度是O(M*N)。更一般的算法是，利用一个hash表（一般这个hash表的长度是256，但是特定情况下可能会更小，例如如果假设都是小写字母，那么只需要26就行了，不过这个对于空间复杂度的优化很不明显而且要进行char - 'a'这样的计算，增加了计算指令），先遍历s2，将s2中存在的字符对应的hash表中的值设置为true，然后遍历s1，对于每一个字符去查询hash表，如果存在就删除（如果重新构建一个新的字符串，这里的删除是一次忽略）.
	2) 另一个依赖于高级数据结构的算法是，将所有的字符分配一个不同的素数，然后遍历s2，将s2中这些对应的素数相乘，得到一个很大的数，然后遍历s1，用每一字符对应的素数去除得到的那个“很大的数”，如果可以整除，就将这个字符删除.
*/

/*
	删除一个字符串中的可能出现的一系列字符
@param char * str 要处理的字符串
@param char * mode 包含要被删除的字符的模式字符串
@return char * 删除之后的字符串 如果内部运行异常会返回null
@note: 这个函数内部申请的资源需要调用者释放
*/
char * DeleteCharsInMode(const char * str, const char * mode){
	assert(str && mode);
	bool hash[256] = {0};
	int M = strlen(str), N = strlen(mode);
	char * toReturn = (char*)malloc((M + 1) * sizeof(char));
	if(!toReturn)
		return nullptr;
	//遍历mode 设置hash
	for(int i = 0; i < N; ++i){
		hash[mode[i]] = true;
	}
	//遍历str 构建返回值
	int lenReturn = 0;
	for(int i = 0; i < M; ++i){
		if(!hash[str[i]])
			toReturn[lenReturn++] = str[i];
	}
	toReturn[lenReturn++] = '\0';
	//重新开辟空间
	toReturn = (char*)realloc(toReturn, lenReturn);
	if(!toReturn)
		return nullptr;
	return toReturn;
}


int main(){
	char * str1 = DeleteCharsInMode("abcdde","bcd");
	cout << str1 << endl;
	free(str1);

	char * str2 = DeleteCharsInMode("abcdde","x");
	cout << str2 << endl;
	free(str2);
	return 0;
}