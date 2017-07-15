<?php
/*题目要求:
	使用非递归的方式实现求解第 N 个斐波那契数
*/

/*
	获取第N个斐波那契数
*@param int $N 要获取第N个
*@return false | int 如果调用异常返回false  否则返回第N个斐波那契数
*/
function getFibonaci($N=0){
	if($N <= 0)
		return false;
	$a = $b = 1;
	for($i = 3; $i <= $N; ++$i){
		$next = $a + $b;
		$a = $b;
		$b = $next;
	}
	return $b;
}

//测试 注意这里单引号不会只会解析 \\ \'这两个转义字符
echo getFibonaci(1)."\n";
echo getFibonaci(2)."\n";
echo getFibonaci(3)."\n";
echo getFibonaci(8)."\n";
echo getFibonaci(10)."\n";