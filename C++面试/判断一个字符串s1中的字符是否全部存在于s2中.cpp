#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

/*
题目描述:
	如何判断一个字符串s1中的字符是否在s2中全部存在。
答案与分析：
	1）这里的全部存在应该包括存在的次数，也就是说在s1中一个字符出现了n次那么在s2中出现的次数不能少于n。一般性的思路是构建一个256长度的hash数组，这个数组中的值保存的是每个assic字符出现的次数，先扫描s2，一个字符出现了一次就将对应的值加一，然后扫描s1，每一个字符如果出现就将对应的hash数组中的字符计数减一。最后扫描这个hash数组，如果存在某一个字符出现的次数是负数，那么就说明s1存在某个字符出现的次数比s2中多，结果返回false。如果这个hash数组中的所有的值都是非负，那么返回true。
	2）其他的思路：
		可以给每一个字符分配一个素数，一共有256个素数，然后遍历s2，将每一个出现的字符对一个的素数进行相乘，得到一个很大的数。然后在扫描s1，用每一个出现的字符对应的素数去除这个“很大的数”，如果不能整除，那么结果就是false，如果能够整除，那么就将这个“很大的数”重置为除法的结果，然后接着遍历s2进行上述的操作一直到s2的末尾返回true。
		另一种思路是将s1，s2都进行排序，然后遍历s1，s2，如果s2中的字符没有匹配到s1中的就直接后移，如果s2中和s1中字符匹配了，就将s1和s2都进行后移。最后判断s1中的位置是否已经移动到末尾就可以得到最终的结果。对于这一种思路，我曾经分析过是否可以在s1和s2遍历都没有到最后的时候就可以判断到不匹配的情况返回false。实际上可以考虑这么个情况s1="ac" s2="abbbbbbbc"可以看到在遍历到 c > b的时候，只能按照上面的描述一直移动s2的位置指针，一直到最后才能匹配到c字符。目前没有分析到可以在遍历结束前判断出最终的结果的方案。
*/

/*
	判断一个字符串dest中的字符是否在src中可以全部找到
@param const char *src 要在其中寻找的字符串
@param const char *dest 要寻找的字符集合
@return bool 如果dest中的之字符在src中全部存在就返回true  否则返回false
*/
bool AllCharsInString(const char * src, const char * dest){
	assert(src && dest);
	int nums[256] = {0}; //保存每一个字符出现的次数
	int M = strlen(src), N = strlen(dest);
	//遍历src 增加相应字符出现次数的计数
	for(int i = 0; i < M; ++i){
		nums[src[i]]++;
	}
	//遍历dest 减少相应字符出现的次数计数
	for(int i = 0; i < N; ++i){
		nums[dest[i]]--;
	}
	//遍历nums数组  如果出现了一个字符的次数小于0那么直接返回false  表示这个字符在src中出现的次数少于dest中的
	for(int i = 0; i < 256; ++i){
		if(nums[i] < 0)
			return false;
	}
	return true;
}


int main(){
	cout << AllCharsInString("abccd","acd") << endl;
	cout << AllCharsInString("abccd","acde") << endl;
	cout << AllCharsInString("abccd","accccd") << endl;
}