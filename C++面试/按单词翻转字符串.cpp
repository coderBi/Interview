#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

/*
题目描述：
	如果进行一个字符串中的按照单词进行逆转，例如"Today is Friday!"进过逆转之后成为"Friday! is Today"
分析：
	1) 一种思路是先将整个字符串进行按字符翻转，例如上面的"Today is Friday!"翻转之后就成为"!yadirF si yadoT"，然后在对这个翻转之后的字符串中的每一个单词进行翻转。这种翻转思路是直接在原来的字符串上面进行操作。
	2) 另一种思路是从后向前，获取到最后一个单词（如果是多个连续的空格，我个人采取将多个空格保留也认为是一个单词）然后在递归的翻转前面的部分，并且将结果追加到最后的那个单词的后面。这一种思路不会对原来的字符串进行修改（不过也可以将最终的结果再拷贝回原来的字符串中）,如果使用char*类型的返回那么返回的新的字符串的空间需要调用者进行释放，在这里为了编码方便可以使用C++中string类型进行操作(编码方便，内存也更好管理)。

*/

/*
	按照字符翻转一个字符串
@param char * str 要翻转的字符串
@param int num 要翻转的字符个数，默认为-1表翻转整个字符串
*/
void Reverse(char * str, int num = -1){
	assert(nullptr != str);
	if(num < 0)
		num = strlen(str);
	for(char * p = str, *q = str + num - 1, tmp; p < q;p++,q--){
		tmp = *p;
		*p = *q;
		*q = tmp;
	}
}


/*
	按单词进行一个字符串的翻转，这里直接在原字符串上面进行操作	
*/
void ReverseByWord(char * str){
	assert(nullptr != str);
	//先翻转整个字符串
	Reverse(str);
	//遍历翻转之后的字符串，对于非空格的单词进行翻转
	int length = strlen(str);
	for(int i = 0, j = 0; i < length; i = j){
		//将i移动到第一个不是空格的字符上
		while(str[i] == ' '){i++;}
		//将j移动到i后面的第一个空格
		for(j = i; j < length && str[j] != ' '; j++){}
		if(i < j){
			//翻转单词
			Reverse(str + i, j - i);
		}
	}
}

/*
	使用递归的思想，进行字符串按单词的翻转
@param std::string str 要操作的字符串
@param int num 要翻转的字符数量, 如果提供的是负数表示翻转整个字符串
@param 翻转之后得到的字符串
@note： 这里提供一个num参数，是因为考虑到递归中如果全部使用string.substr来获取前面的子串,那么对于单词很短，整个字符串很长的情况会造成很大的额外内存开销。所以保存一个变量表示当前要翻转的范围
*/
std::string ReverseByWord(std::string & str, int num = -1){
	if(num < 0)
		num = str.length();
	if(!num){
		//递归的base
		return "";
	}
	std::string toReturn = "";
	int i = num - 1, j = i;
	while(i >= 0 && str[i] == ' '){
		//空格直接追加到结果集中，因为空格即使进行翻转，结果也是一样的。
		toReturn += ' ';
		i--;
	}
	for(j = i; j >= 0 && str[j] != ' '; --j){};
	if(j < i){
		//将单词追加到结果中
		toReturn += str.substr(j + 1, i - j);
	}
	return toReturn + ReverseByWord(str, j + 1); 
}

int main(){
	char str[] = "Today is Friday!";
	ReverseByWord(str);
	cout << str << endl;

	string s = "Today is Friday!";
	cout << ReverseByWord(s) << endl;
	return 0;
}