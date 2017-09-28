// 计算x+=x-=x-x--.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

/*
	1）在gcc中运行下面的代码最终的x的结果是8。我个人的解释是在整个表达式 x+=x-=x-x--计算完毕之后立即进行了一个x--。最后将整个表达式的值也就是8赋给了x
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

