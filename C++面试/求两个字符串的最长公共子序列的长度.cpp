#include <iostream>
#include <cstring>
#include <assert.h>
using namespace std;


/*
问题描述：
	编写一个函数，输入两个字符串，求它们的最长公共子序列的长度。例如：输入两个字符串ABCBDAB和BDCABA,字符串DBBA和BDAB都是它们的最长公共子序列，则输出它们的长度4。（注：最长公共子序列不要求这个公共的序列中的字符是连续出现的）
分析：
	1）先使用分治思想，考虑两个字符串的最后一位，如果相同，那么最终的长度就是f(m,n) = f(m-1,n-1) + 1。其中f(m,n)表示字符串长度分别是m和n的情况下计算这两子串的最长公共子序列的长度. 如果两个字符串最后一位不相同，那么 f(m,n) = max{f(m-1,n),f(m,n-1)}，也即是其中的一个字符串的末尾进行舍弃然后与另一个字符串向比较计算，取这两个可能的计算结果中的较大者为最终的f(m,n)。可以看到最后一位无论是相同的还是不相同的都符合最优子结构的特性（也就是每一个子结构的解也是好最优的，这一点是与贪婪的不同）
	2）上述的递归表述中，如果使用自顶向下，那么公式max{f(m-1,n),f(m,n-1)}可能会产生大量的重复计算，主要的问题是如果很多的末尾不匹配在计算f(m-1,n)和f(m,n-1)的时候会出现重叠。
	3）实际上，形如f(m-1,n-1)和 f(m,n-1) f(m-1,n)这样的形式，明显就是填表中的矩形的三个角，在自底向上的两种循环中，在计算f(m,n)之前已经计算了f(m-1,*)也就是前一行的数据，而在本次列的循环中在计算 f(m,n)之前已经计算过了f(m,n-1)。这样是可以通过已经计算过的3个角来获取到要求解的 f(m,n)的。这是一种常用的模式化填表。
	4）公式的base为如果其中的一个字符串为空，也就是f(0,*) = 0 和 f(*,0) = 0
扩展分析：
	如果是要求得最长子序列的字符串的内容呢。一个思路是将每一个节点额外保留一个字符串用来保存这个节点最长子序列的内容，然后在下一个节点的计算中如果末尾相同那么直接在子序列的末尾加上这个字符进行存储。但是这里如果对每一个节点的情况进行存储会造成空间的浪费，还有就是实际上最后影响f(m,n)填表的只有三个其他节点，而每一行进行填表的时候会依赖于上一行的结果，所以额外的保存字符串数量为上一行n+1个结果和这里行的当前元素左边的节点的结果.
*/

/*
	利用dp求解 longest common subsequence
@param char *str1 待求解的字符串1
@param char *str2 待求解的字符串2
@param string *result = nullptr 用于获取求解到的最长子序列的内容，如果没有传入，默认是nullptr表示不进行内容的获取
@return int 两个字符串的最长公共秩子序列的长度
@version 1.0 基本实现功能，能够求解答到最长的子序列的长度。但是不能获取到子序列的内容
@version 2.0 添加一个用于返回获取到的最长子序列的内容的形参，如果这个参数没有传入，默认是null，表示不会进行内容的获取
*/
int LCS(const char *str1, const char *str2, string * result = nullptr){
	assert(str1 && str2);
	if(nullptr == str1 || nullptr == str2){
		if(result)
			*result = "";
		return 0;
	}
	int m = strlen(str1), n = strlen(str2);
	if(!m || !n){
		if(result)
			*result = "";
		return 0; //其中至少有一个为空字符串
	}
	int **c = new int*[m+1];
	if(!c){
		//严格意义上这里应该抛异常
		std::cerr << "new memory fail" << endl;
		if(result)
			*result = "";
		return 0;
	}
	for(int i = 0; i <= m; ++i){
		c[i] = new int[n+1]();
		if(!c[i]){
			std::cerr << "new memory fail" << endl;
			if(result)
				*result = "";
			return 0;
		}
	}

	//计算填表
	if(!result){
		//不需要保存结果字符串 直接计算长度的数值
		for(int i = 1; i <=m; ++i){
			for(int j = 1; j <= n; ++j){
				if(str1[i-1] == str2[j-1])
					c[i][j] = c[i-1][j-1] + 1; //末尾相同
				else
					c[i][j] = max(c[i-1][j],c[i][j-1]);
			}
		}
	}else{
		string * resultInPreLine = new string[n+1](); //用来存储循环上一行结果
		if(!resultInPreLine){
			cerr << "new memory fail" << endl;
			*result = "";
			return 0;
		}
		string left; //用来存放左边的节点的结果
		string calc; //用来存放当前节点的最长子序列的结果	
		for(int i = 1; i <=m; ++i){
			for(int j = 1; j <= n; ++j){
				if(str1[i-1] == str2[j-1]){
					c[i][j] = c[i-1][j-1] + 1; //末尾相同
					calc = resultInPreLine[j-1] + str1[i-1];
				}
				else{
					if(c[i-1][j] < c[i][j-1]){
						c[i][j] = c[i][j-1];
						calc = resultInPreLine[j];
					}else{
						c[i][j] = c[i-1][j];
						calc = left;
					}
				}
				//更新本行左侧数据 更新left
				resultInPreLine[j-1] = left;
				left = calc;
			}
			//重置left，更新最后一列上的resultInPreLine
			left = "";
			resultInPreLine[n] = calc;
		}
		//释放额外空间
		delete[] resultInPreLine;
		*result = resultInPreLine[n];
	}

	//释放内存
	for(int i = 0; i <= m; ++i)
		delete[] c[i];
	delete[] c;
	return c[m][n];
}

int main(){
	const char * str1 = "ABCBDAB", *str2 = "BDCABA";
	cout << LCS(str1, str2) << endl;
	cout << LCS("ab", "ba") << endl;

	//获取结果子串
	string s;
	cout << LCS(str1, str2, &s) << endl;
	cout << s << endl;
	return 0;
}