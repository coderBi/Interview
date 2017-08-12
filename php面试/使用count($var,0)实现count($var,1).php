<?php
/*
count函数介绍：
	count()函数 可以返回数组或者对象中的元素个数。对于null和空数组返回0.对于其他的数据类型count函数直接返回1.
	count($arr,$mode):返回的是某个数组的元素的个数
	count()函数的第二个参数指示的是模式，可以取值为0和1，如果是0，表示只取一级的数组元素个数。如果为1，会递归的统计子数组的元素个数。例如array(array(1,2),array(1,2,3))如果模式是0得到的是2，但是如果模式是1得到的是 2 + 2 + 3 = 7 其中的后面的额外的2和3就是子数组的元素个数。如果还有更低级的子数组，还会进行递归的计算和叠加。
实现思路：
	要用count($var,0)实现count($var,1)可以根据上面的思想进行递归的计算： 一个数组本身的count($arr,0) + 数组中每一个子数组的count($arr[i],1)，后面的子数组的count($arr[i],1)便可以直接递归实现。这个递归的base是数组中没有子数组。
*/


/*
	使用count($var,0)实现的count($var,1)效果函数
@param array $arr 要统计元素个数的数组
@return int 递归统计的数组的元素个数
*/
function count_1($arr=array()){
	$toReturn = count($arr,0);
	foreach($arr as $v){
		if(is_array($v))
			$toReturn += count_1($v);
	}
	return $toReturn;
}


//测试
$arr = array(array(1,2),array(1,2,3));
var_dump(count($arr,0)); //2
var_dump(count($arr,1));  //7
var_dump(count_1($arr));  //7