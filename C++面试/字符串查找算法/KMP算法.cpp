#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;

/*
KMP算法分析：
	BF算法的一个最大的问题是，每一次如果没有找到就将s1中的比较的起始位置向前移动1.而KMP算法是在每一次如果不出现了不匹配，s2中的位置指针并不会进行回溯，而是通过调整s2中的要比较的下一个位置进行新的比较，这个位置的确定依赖于一个next数组，next[i]表示s2[i]与s1中的字符不匹配的时候的时候下一个s2中的直接用来与s1中现在的位置上的字符进行比对的位置。KMP算法中的next数组的构建分析如下：对于s2="aaacXbbb"如果在X字符处不匹配，那么由于前面的aaac已经匹配了，就分析这个aaac的前缀aaa与后缀aac他们重合的部分是aa，那么由于前面已经有两个重合的了next数组应该执行2也就是从第三个元素进行匹配。上面对next[i]只是从理论上给出一个描述，实际操作计算的时候这个复杂度还是太高，可以进行进一步的优化。这个优化基于以下事实：为了计算next[i+1],首先考虑next[i]，如果数组中s2[i] = s2[next[i]]那么就可直接设置next[i+1] = next[i] + 1;如果数组s2[i] != s2[next[i]]，那么问题转换为将s2[next[i]]"替换"（并不是真实的内存替换，可以想象为替换效果）为s2[i]之后重新计算next[next[i]]，这个值就是最后的要求的next[i+1]。上面的问题为一个递归问题，现在只需要找到这个问题的base。可以观察到当i=0的时候，如果出现了不匹配，那么s1中的指针应该向前一定一位，从s2的开头重新进行匹配，所以这里形象的理解为next[0]=-1,也就是使用s2中一个越界的位置与当期不符合的s1的位置进行重新匹配（并且认为是匹配成功的）。
在书写的过程中发现的一个小的点：
	可以发现无论是BF函数还是KMP函数，都没有进行s1为空字符串的判定，两个算法在这种情况下返回的是0,这个结果从常识的角度来看是可以接受的。
*/


/*
	使用KMP算法在一个字符串中查找另一个字符串首次出现的位置
@param const char * s1 容器字符串
@param const char * s2 要查找的目标子字符串
@return int 如果找到了相应的子字符串就返回首次出现的位置，如果没有找到返回-1
*/
int KMP(const char *s1, const char * s2){
	assert(s1 && s2);
	int M = strlen(s1), N = strlen(s2);
	if(M < N)
		return -1;
	//构建next数组
	int *next = new int[N];
	if(!next){
		std::cerr << "new memory fail" << std::endl;
		return -1; //异常处理，这里本来应该是抛出异常的，这里暂时写作返回-1
	}
	next[0] = -1; //base
	for(int i = 1; i < N; ++i){
		int j = next[i-1];
		while(j != -1 && s2[j] != s2[i-1]){
			//回溯
			j = next[j];
		}
		//注意：当next[i-1]为-1的时候。需要直接将s1中的指针向前移动，也就是“s2[-1]与s1中的目前的位置相对齐进行比较并且认为是符合要求的(符合要求也就是next[i] = next[i-1] + 1)”
		next[i] = next[i-1] + 1;
	}

	/*上面我个人书写的寻找next[i]的代码，网络上其他的寻找next数组的代码如下	---START*/
	/*写法1：严格迭代，使用next[i]与之前的其他已知的next，迭代出next[i+1]*/
	int j = next[0] = -1; //记录上一个的next[i]
	//递推next[i+1]
	for(int i = 0; i < N -1;){
		if(j == -1 || s2[i] == s2[j]){
			//s2[i]与上一个next位置的元素匹配（包括next 为 -1的时候的默认与当前元素的匹配）
			next[++i] = ++j;
		}else{
			//调整j  接着寻找next[i+1]
			j = next[j];
		}
	}
	/*上面我个人书写的寻找next[i]的代码，网络上其他的寻找next数组的代码如下	---END*/

	//查找子字符串的位置
	int i = 0; j = 0;
	while(i < M && j < N){
		if(j == -1 || s1[i] == s2[j]){
			//这里包含了next[i] = -1这一特殊情况
			i++;
			j++;
		}else
			j = next[j];  //不匹配，下一次s1中的指针不动，s2中的下一个比对位置移动到next[j]
	}
	
	//释放资源
	delete[] next;
	return j < N ? -1 : i - N;
}

int main(){
	char s1[] = "elloworldhello", s2[] = "dhello";
	cout << KMP(s1, s2) << endl;

	cout << KMP("hello world", "world") << endl;

	cout << KMP("", "") << endl;
	return 0;
}