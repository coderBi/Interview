// 计算x+=x-=x-x--.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

/*
	1）在gcc中运行下面的代码最终的x的结果是8。GCC中对于表达式x += x-= x - x-- 不是一次考虑整个表达式的，是先考虑的子表达式x-= x - x--，而且这子表达式先执行了x--，之后x成了(x-1)，x - x--成了-1，所以这个子表达式的效果是x-=-1，结合前面的x--，所以x又成了原始的x。然后分析表达式x+=x得到结果8.
	2）但是在vs中测试最终的运行结果是7，这个7给出的运行顺序是: x-= 0, 然后 x+=x，这个时候x=8，最后执行一次x--。也就是这个逻辑就是整个表达式计算
	结束进行的x--
*/

int _tmain(int argc, _TCHAR* argv[])
{
	int x = 4;
	x += x -= x - x--;
	cout << x << endl;
	system("pause");
	return 0;
}

