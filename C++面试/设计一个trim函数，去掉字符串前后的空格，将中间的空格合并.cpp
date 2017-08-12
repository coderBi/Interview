#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
using namespace std;

/*
题目描述：
	设计一个trim函数，去掉一个字符串前后的空格，将中间的空格多个连续的空格转换为一个
分析：
	常见api中的trim有trim_left trim_right trim，但是他们一般的不会合并中间的空格.这里的实现策略是从左往右进行扫描，首先跳过最前面的空格，然后添加第一个单词(到下一个空格部分之前)。接下来的处理就很统一，如果一直是空格就往后移动，如果遇到非空格就记录下紧邻上一个连续空格的非空格的位置，然后一直向后移动到空格，在这个单词添加到最终的结果之前向结果中添加一个空格，循环上面的过程一直到遍历结束，就得到最终的trim之后的字符串。
note：
	由于并不会在原来的字符串上面进行修改，trim之后的结果保存在新开辟的空间中，对于资源的释放交给了调用者.
*/

char * trim(const char * s){
	assert(s);
	int length = strlen(s);
	char * toReturn = (char*)malloc((length + 1) * sizeof(char));
	if(!toReturn)
		return nullptr;
	int i = 0, j = 0, k = 0;
	//处理最前面的空格
	while(i < length && s[i] == ' '){ i++;}
	//处理第一个单词
	for(j = i; j < length && s[j] != ' '; ++j){
		toReturn[k++] = s[j];
	}
	//处理中间和最后的空格和单词
	while(i < length){
		//略过空格
		for(i = j; i < length && s[i] == ' '; ++i){}
		//获取单词结束位置
		for(j = i; j < length && s[j] != ' '; ++j){}
		//如果i < j也就是存在单词 那么将一个空格和单词添加到结果中
		if(i < j){
			toReturn[k++] = ' ';
			for(int x = i; x < j; ++x)
				toReturn[k++] = s[x];
		}
	}
	toReturn[k++] = '\0';
	//重新分配合适空间
	toReturn = (char*)realloc(toReturn, k * sizeof(char));
	if(!toReturn)
		return nullptr; //注意，这里完全可以不去判断是否为null，因为toReturn为null的时候直接返回toReturn对于最终的结果是一样的，但是这里这么写可以让逻辑更清晰
	return toReturn;
}

int main(){
	char str[] = "hello    world welcome to C++   ";
	char * result = trim(str);
	cout << result << endl;
	//检测最后一个字符是不是正确
	cout << "the last char of result is: " << result[strlen(result) - 1] << endl;
	free(result);
	return 0;
}