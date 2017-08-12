<?php
/*
题目描述：
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
思路分析：
从这个二维数组的左下角或者右上角开始分析，其实这就是一个查找树。
*/


/*
判断一个按照从左到右递增从上到下递增的数组中是否包含指定的整数
@param array $arr 要查找的特定数组
@param int $num 待查找的整数
@return bool 数组中有指定整数返回true  否则返回false
*/
function check_in_array($arr=array(),$num=0){
	$X = count($arr);
	if(!$X)
		return false;
	$Y = count($arr[0]);
	for($x = $X -1, $y = 0; $x >= 0 && $y < $Y;){
		if($arr[$x][$y] == $num)
			return true;
		if($arr[$x][$y] > $num)
			$x--;
		else
			$y++;
	}
	return false;
}

//测试
$arr = array(
	0=>array(1,2,3),
	1=>array(4,5,6),
	2=>array(7,8,9),
);
var_dump(check_in_array($arr,6));
var_dump(check_in_array($arr,100));