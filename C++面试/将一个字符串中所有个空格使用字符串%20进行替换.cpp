#include <iostream>
#include <assert.h>
#include <string.h>
#include <vector>
using namespace std;

/*
题目描述：
	将字符串中所有的空格替换成"%20"。函数的签名形式为 void ReplaceFunc(char str[], int length)
分析：
	通过函数的签名，可发现对于空间的保证是由调用者去实现的。对于空格的替换，如果是从前往后进行，那么由于替换之后的字符串比空格更长，会导致对后面还没有替换和拷贝的原来的内容进行了覆盖。所以这个函数的逻辑应该是从后往前进行覆盖。
延伸：
	1）这个函数的经过简单的修改，可以实现对于任意的字符用某一个字符串进行替换
	2）更一般的，对一个字符串中的某一个子串进行匹配替换，可以考虑使用KMP（为了避免重复的运算，需要适应的改良）从前往后查找，用一个新的空间保存替换之后的结果返回。这个就有些像正则里面的repacleAll了，当然也可以设定一种只替换第一个匹配的子串。这里对于KMP的运用更多的是一种思想，对于不同的子串，由于匹配模式一样，所以next属猪只需要构建一次；还有要计算需要存储的结果字符串的空间开销的时候遍历了一次字符串，这个时候，可以把KMP查询到的一系列的子串的位置保存下来，这样接下来的替换就不用再进行查找了。
	3）和2）相似的问题是提供一个模式字符串，要求对输入字符串与模式串中的所有匹配的字符替换某一个字符串
*/


/*
	将一个字符串中的所有空格替换为"%20"
@param char str[] 要处理的字符串
@param int length 要处理的字符串的长度
*/
void ReplaceFunc(char str[], int length){
	int newLen = length; //新的替换后的字符串的长度
	for(int i = 0; i < length; ++i){
		if(str[i] == ' ')
			newLen += 2;
	}
	str[newLen] = '\0';  //添加新的结束符
	//从后往前遍历str 保存替换结果
	for(int i = length - 1, j = newLen -1; i >= 0; --i){
		if(str[i] == ' '){
			str[j--] = '0';
			str[j--] = '2';
			str[j--] = '%';
		}else
			str[j--] = str[i];
	}
}

/*
	延伸： 将一个字符串中的所有与模式串中字符匹配的元素都替换为某一个字符串
@note: 这里不在原来的字符串上面进行操作，而是将结果返回一个新的字符串，资源需要调用者进行释放
*/
char * ReplaceByMode(const char * str, const char * mode, const char * replace){
	assert(str && mode && replace);
	int length = strlen(str), newLen = length, replaceLen = strlen(replace);
	//利用模式串 构造hash
	bool hash[256] = {0};
	while(*mode){
		hash[*mode] = true;
		mode++;
	}
	//计算新的数据空间
	for(int i = 0; i < length; ++i){
		if(hash[str[i]])
			newLen += replaceLen - 1;
	}
	char * result = new char[newLen + 1];
	if(!result){
		std::cerr << "new memory fail" << std::endl;
		return nullptr;
	}
	result[newLen] = '\0';
	//遍历原字符串  填充结果字符串
	for(int i = 0, j = 0; i < length; ++i){
		if(hash[str[i]]){
			//进行替换
			for(int k = 0; k < replaceLen; ++k)
				result[j++] = replace[k];
		}else{
			//直接复制原来的字符
			result[j++] = str[i];
		}
	}
	return result;
}


/*
	延伸： 将一个字符串中的所有某个子字符串替换为另一个字符串
@note: 这里不在原来的字符串上面进行操作，而是将结果返回一个新的字符串，资源需要调用者进行释放
*/
char * ReplaceSubStr(const char * str, const char * substr, const char * replace){
	assert(str && substr && replace);
	int length = strlen(str), newLen = length, subLen = strlen(substr), replaceLen = strlen(replace);
	if(!subLen){
		std:: cerr << "the substring is null" << std::endl;
		return nullptr;
	}
	//构建next数组
	int *next = new int[subLen];
	if(!next){
		std::cerr << "new memory fail" << std::endl;
		return nullptr;
	}
	next[0] = -1;
	//迭代计算next[i+1]
	for(int i = 0, j = -1; i < subLen -1;){
		if(j == -1 || substr[i] == substr[j]){
			next[++i] = ++j;
		}else{
			j = next[j]; //回溯
		}
	}

	//在原字符串中查询目标子字符串出现的位置
	std::vector<int> pos; //保存查找到的子串的位置
	int sub = replaceLen -  subLen; //用于替换的字符串与原子字符串的长度差

	for(int i = 0, j = 0; i < length;){
		if(j == -1 || str[i] == substr[j]){
			i++;
			j++;
			//如果匹配完成  就将位置添加到容器
			if(j == subLen){
				pos.push_back(i - subLen);
				//修正返回结果字符串的长度
				newLen += sub;
				//重置j 表示开始下一个位置的查询
				j = 0;
			}
		}else
			j = next[j];
	}
	//开辟返回结果的字符串空间
	char * result = new char[newLen + 1];
	if(!result){
		std::cerr << "new memory fail" << std::endl;
		return nullptr;
	}
	result[newLen] = '\0';
	//遍历原字符串到最后一个找到的子串  填充结果字符串
	int size = pos.size();
	int i = 0, j = 0;
	for(int k = 0; k < size; ++k){
		//复制查询到子串之前的部分
		for(; i < pos[k]; ++i)
			result[j++] = str[i];
		//将查询到的子串替换为目标字符串
		for(int t = 0; t < replaceLen; ++t)
			result[j++] = replace[t];
		i = pos[k] + subLen;
	}
	//复制最后查询到的子串之后的其他部分
	for(; i < length; ++i)
		result[j++] = str[i];
	//释放资源
	delete [] next;
	return result;
}


int main(){
	char str[100] = " hello wor  ld  ";
	ReplaceFunc(str, strlen(str));
	cout << str << endl;
	
	char * s = ReplaceByMode("hello world this is kk", " k", "!!");
	cout << s << endl;
	delete [] s;

	char * s1 = ReplaceSubStr("hello world this is kk world", "world", "!!");
	cout << s1 << endl;
	delete [] s1;
	return 0;
}