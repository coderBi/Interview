<?php
/*
题目描述：
	$input = "2,4,8,16,32,64",如何计算这个字符串中数字的和
分析：
	这个题目给的很有规律，如果考虑到是等比数列，可能会有更好的优化。但是这里我给出一个一般性的解法，就是利用explode()函数，先将这个字符串转换为数组，然后对数组的各项进行累加
*/

function sum($str=""){
	$arr = explode(',',$str);
	$toReturn = 0;
	foreach($arr as $v){
		$toReturn += $v;
	}
	/*
		如果考虑到是等比数列的话，这里可以进行一次优化，具体如下
		$toReturn = $arr[count($arr) -1] * 2 -1;
	*/
	return $toReturn;
}

//测试
$input = "2,4,8,16,32,64";
print_r(sum($input));