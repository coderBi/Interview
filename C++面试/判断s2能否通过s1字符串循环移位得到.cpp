#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;

/*
题目描述：
	给定两个字符串s1和s2，判断是否s2可以通过s1做循环移位得到。
分析：
	给定字符串s[] = "abcd"，其循环移位之后的字符串可以有一下四个（也就是每一个元素都可能是起始的第一个字符）：
	abcd
	bcda
	cdab
	dabc
	按照一般性的分析，将在这些字符串中（利用KMP）寻找是否存在s2就可得到最终的结果。
	现在要分析的一点就是，如果一个字符串的长度比较大，如果采用事先存储所有循环移位得到的字符串那么需要使用 N*(N-1)的额外空间，在很多程序中这是不可接受的，如果保存上一个循环移位字符串的起始字符的位置，那么，可以对每一个循环移位后的字符串进行判断之后用同一个空间保存下一个移位之后的字符串，这个需要额外的空间为O(N)（可以使用O(1)直接在原来的字符串上面进行修改，不过这设计到原来输入字符串的完整性问题）。实际上,这种相邻的字符串之间的规律很统一，明显可以进行空间复杂度的优化。可以这么考虑用一个变量保存其实的位置索引，这个位置索引的范围应该是[0,length-1]，然后对于每一个其实的位置i，用另一个变量j进行保存i，再对s[j++%length]在j < (length  + i)的情况下进行分析就取得了一个完整的循环移位后的数组。
	如果使用一个额外的数组进行每一次的移位得到的字符串进行保存，那么常用的KMP算法直接对这个字符串进行处理即可。如果是通过s[j++%length]进行在原字符串上的访问，那么对于KMP算法的传入参数和内部的处理需要一些改良。值得注意的是如果使用一个额外的数组进行每一次移位字符串的保存，那么每一次移动会设计到O(n)的数据移动，这个相对于使用O(n*(n-1))的额外空间的处理在时间复杂度上没有改良。如果使用s[j++%length]进行访问呢？这个虽然不涉及到每一的元素的移动，但是又多了一个"%length"的运算。从上面的分析，可以看出，对于时间的复杂度为O(N*N + N*(N+M))(其中N为s1长度,M为s2的长度)是没有更改的改良方案的。
改良时间复杂度：
	1)上面描述的算法的时间复杂度O(M*(M+N) + M*M)(M为s1的长度，N为s2的长度)明显太高，影响了算法的实用性。考虑到以下事实：我们要寻找的是s2，由于s2是固定了，如果我们对每一个移位字符串都进行KMP，那么里面进行next数组的计算就是重复的。另外，由于对于每一个移位之后的字符串，使用KMP都会进行从前向后移动的匹配，而多个KMP之间这种尝试性匹配也是存在高度的重复的。
	2）改良复杂度的方案如下：对于abcd我们可以通过在这个字符串后面加上abc构成一个abcdabc字符串。在保证要查找的s2的长度小于容器字符串s1的长度的前提下，如果找到了s2,那么s2一定是重新构建的abcdabc的子串。通过这种转化，可以使用一个KMP算法，复杂度O(2*M - 1 + N)查找s2是否存在在s1的移位字符串中.
	3)同样，由于改良之后的算法的空间复杂度为O(2*M)，如果要进行空间复杂度的优化，可以考虑在原来的字符串上面使用s1[j++%length]这种访问方式，将空间复杂度降低到O(1)
总结：
	1）一般性算法，可得到时间复杂度为O(M*M + M*(M+N))。其实M*M是构建移位之后的字符串的指令数，而M*(M+N)是进行M次的KMP算法的时间。
	2）通过在s1字符串的后面追加字符s1[0]~s1[M-2](最后一个字符不要，因为这又进入了下一个循环)，然后在其中查找s2，可以在O(2*M - 2 + N)的时间复杂度解决问题。极大的提升算法的效率（直观上看将一个2次的复杂度降为线性）
	3)无论哪一种时间复杂度，我们可以通过保存一个起始位置i，这个起始位置的范围为[0,M-1]，使用s1[(i+j)%M]（其中0 <= j < M）访问到一个移位后的完整字符串。这样就将空间复杂度降到了O(1)
补充：
	这里给出了一个空间复杂度为O(1)很容易书写的BF算法获取s2是否存在在字符串s1的移位字符串中的判定方法。
*/

/*
	KMP算法
@param const char* s1 要寻找的容器字符串
@param const char* s2 要寻找到目标字符串
@param int M s1的长度
@param int N s2的长度
@return int 如果找到了就返回s1中首次出现s2的位置，否则返回-1
@note  一般的KMP算法中不会进行字符串的长度参数的传递，而是在算法的内部进行长度的计算，这里之所以进行传递，是因为对于每一次使用KMP算法的字符串的长度没有产生变化，如果使用外部计算长度传入那么可以减少 O(M-1) 次对这两个长度的反复计算
*/
int KMP(const char *s1, const char *s2, int M, int N){
	assert(s1 && s2);
	//int M = strlen(s1), N = strlen(s2); //改进：长度在这里直接进行传入
	if(M < N)
		return -1;
	//构建next数组
	int *next = new int[N];
	if(!next){
		std::cerr << "new memory fail" << std::endl;
		return -1;
	}
	next[0] = -1;
	int j = -1; //保存上一个合适的next 的值
	//迭代计算next[i+1]
	for(int i = 0; i < N -1;){
		if(j == -1 || s2[i] == s2[j]){
			//上一个合适的next位置上出现了匹配，这里包括j = -1的时候“s2[-1]与任意的字符匹配”的这一特殊情况
			next[++i] = ++j; 
		}else
			j = next[j]; //回溯
	}

	//在s1中寻找s2
	j = 0; //s2中的位置指针
	int i = 0; //s1中的位置指针
	while(i < M && j < N){
		while(j != -1 && s1[i] != s2[j])
			j = next[j];
		i++;
		j++;
	}

	//释放资源
	delete[] next;
	return j < N ? -1 : i - N;
}


/*
	使用一个额外的数组，空间复杂度为O(N)的算法在s1的所有移位字符串中寻找字符串s2
@param const char *s1 要寻找的容器字符串
@param const char *s2 要寻找的目标字符串
@return int 如果找到了s2那么返回在s1中的位置，如果没有找到返回-1
*/
int cal1(const char * s1, const char * s2){
	assert(s1 && s2);
	int M = strlen(s1), N = strlen(s2);
	if(M < N)
		return -1;
	char * arr = new char[M + 1]; //保存移位之后的字符串
	arr[M] = '\0';
	if(!arr){
		std::cerr << "new memory fail" << std::endl;
		return -1;
	}
	strcpy(arr,s1);
	int result = -1; //保存KMP算法的结果
	//通过KMP算法寻找所有的s1的移位字符串
	int i = 0;
	for(;i < M; ++i){
		if(-1 != (result = KMP(arr,s2,M,N)))
			break; //找到了
		//移位 这里为前移
		char first = arr[0];  //保存第一个元素
		//除了第一个元素之外 其他的元素前移
		for(int i = 0; i < M - 1; ++i){
			arr[i] = arr[i+1];
		}
		arr[M-1] = first;
	}
	//释放资源
	delete[] arr;
	return -1 == result ? -1 : i + result; //i是左移之后起始脚标(相对于原始字符串)，result是假设i=0的时候找到的s2的位置，所以i+result是在原始字符串中找到的s2的位置
}


/*
	改良之后的时间杂度为O(2*M -1 + N)，空间复杂度为O(2*M)的算法，判断s2是否存在与通过字符串s1移位得到的字符串中
@param const char *s1 要寻找的容器字符串
@param const char *s2 要寻找的目标字符串
@return int 如果找到了s2那么返回在s1中的位置，如果没有找到返回-1
@note 其实就是一个KMP，这里为了方便直接使用上面书写好的KMP算法
*/
int cal2(const char * s1, const char * s2){
	assert(s1 && s2);
	int M = strlen(s1), N = strlen(s2);
	if(M < N)
		return -1;
	//在原来的s1的后面追加 s1[0~M-2] 然后在其中利用KMP算法查找s2
	char * str = new char[2 * M  -1 + 1];
	if(!str){
		std::cerr << "new memory fail" << std::endl;
		return -1;
	}
	strcpy(str,s1);
	strncat(str,s1,M-1); //将s1[0~M-2]追加到str，strncat第三个参数指出的是追加的字符个数。
	int result = KMP(str,s2,2*M,N);
	//释放资源
	delete[] str;
	return result; //这里解释一下result为什么小于M，因为M是最后一个移位（进行左移）的起始字符的位置，下一次移位又回到了原始的s1，对于新字符串str，如果s2找到的起始匹配位置在str[M-1]之后，那么可以通过反证法得到在str[M-1]之前已经可以匹配到s2了。
}

/*
	不使用额外的数组，空间复杂度为O(1)(注意这里的空间复杂度的计算没有分析KMP中的next数组的构建)时间复杂度为O(2*M - 1 + N)的算法，判断s2是否存在在通过s1字符串移位得到的字符串中
@param const char *s1 要寻找的容器字符串
@param const char *s2 要寻找的目标字符串
@return int 如果找到了s2那么返回在s1中的位置，如果没有找到返回-1
@note 由于没有使用额外的数组空间，那么原来的KMP算法不能直接拿来使用,需要进行一些对应的访问改良
*/
int cal3(const char * s1, const char * s2){
	assert(s1 && s2);
	int M = strlen(s1), N = strlen(s2);
	if(M < N)
		return -1;
	//构建next数组
	int *next = new int[N];
	if(!next){
		std::cerr << "new memory fail" << std::endl;
		return -1;
	}
	next[0] = -1;
	//利用迭代计算next[i+1]
	int j = -1; //上一个合适的next
	for(int i = 0; i < N - 1;){
		if(-1 == j || s2[i] == s2[j]){
			//得到next[i+1]
			next[++i] = ++j; 
		}else
			j = next[j];  //回溯，继续计算next[i+1]
	}

	j = -1; //s2中的指针
	int i = 0; //s1中指针
	//说明一下这里的i<(2*M -1)的原因，这里的i的边界是cal2算法中的边界，也就是假设将s1后面添加上s1[0~M-2]构成一个长度为2*M -1的字符串数组
	for(; i < (2 * M -1) && j < N;){
		while(-1 != j && s1[i%M] != s2[j]){
			j = next[j];
		}
		i++;
		j++;
	}
	//释放next数组
	delete [] next;
	return j == N ? i - N : -1;
}


/*
	空间复杂度为O(1)是时间复杂度为O(M*N)的BF判定方法
@param const char *s1 要寻找的容器字符串
@param const char *s2 要寻找的目标字符串
@return int 如果找到了s2那么返回在s1中的位置，如果没有找到返回-1
*/
int cal4(const char *s1, const char *s2){
	assert(s1 && s2);
	int M = strlen(s1), N = strlen(s2);
	if(M < N)
		return -1;
	int i = 0; //s1中的起始位置
	for(; i < M; ++i){
		//对于每一个以i为起始位置的长度为 N 的字符串与s2进行一一匹配
		int j = 0;
		//与常规KMP相比  这里最主要的区别就是利用了s1[(i+j)%M]进行访问
		for(; j < N && s1[(i+j)%M] == s2[j]; ++j){}
		if(j == N)
			return i;
	}
	return -1;
}

int main(){
	cout << cal1("dhelloworl", "world") << endl;
	cout << cal2("dhelloworl", "world") << endl;
	cout << cal3("dhelloworl", "world") << endl;
	cout << cal4("dhelloworl", "world") << endl;
	return 0;
}