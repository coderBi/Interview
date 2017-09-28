#include <iostream>
using namespace std;

int main(){
	//逗号表达式的结合方向是从左到右，其优先级比赋值表达式低，是所有表达式中最低的。整个表达式的值是最后一个子表达式的值.
	cout << (21,222,111) << endl;
}