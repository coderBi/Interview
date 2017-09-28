#include <iostream>
using namespace std;

/*
	这里的思路是将结构体的首地址放到0，然后在这个基础上只需要得到相应的字段的地址就可
---note:
	1) & (((type*)0)->field) 并没有涉及到取值运算，所以这里不会出现崩溃的现象
	2) 这一种思路，巧妙的在不创建任何的实际对象的前提下，计算出来了一个类型中各地段的偏移
*/

#define OFFSET(type,field) ((int) & (((type*)0)->field))

struct S
{
	int a;
	char b;
	int c;
};

int main(){
	cout << OFFSET(S,c) << endl; //却只这里没有崩，因为只是涉及到位置的偏移，并没有进行取值。“->field”只是得到了一个地址
	S *s = (S*)0;
	cout << s->c << endl; //这里会崩，是因为这需要进行取值运算，遇到了非法访问
	return 0;
}