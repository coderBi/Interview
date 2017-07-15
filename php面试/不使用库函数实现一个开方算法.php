<?php
/*
题目要求：
	不使用数学库函数，写一个函数求解一个数字的开方
	输入参数包括要开方的数和要保留的位数
*/


/*
计算一个数的开方
*param number num 要计算的被开方数
*parem int precision 小数点后面要求保留的位数
*return number 保留指定小数位的double结果
*V1.0 思路：如果要保留两位，那么将传入的num先左移(这里的左移指的是十进制的)4位，然后利用夹逼的方法，如果一个数mid是另一个数num的开方，那么会满足 (mid + 0.5)*(mid + 0.5) >= num,而(mid - 0.5)*(mid - 0.5) <= num。然后比较这两个乘积哪一个更靠近num，如果是下面的(mid - 0.5)*(mid - 0.5)乘积更靠近，就用mid-0.5然后转int，否则用mid+0.5转int。最后将转换之后的int的数值右移(十进制，非二进制)相应的进度位数就行
*V2.0 更改：V1.0的思路存在一个问题，因为 x*x的增长率不是线性的，那么如果直接比较 (mid - 0.5)*(mid - 0.5) 和 (mid + 0.5)*(mid + 0.5) 哪一个距离最终的数值更近去判断该向那一边取整，这就存在一个偏差，因为由于增长率问题 (mid + 0.5)*(mid + 0.5) 天然的就会趋向于距离目标值更远。这里改进的思路是如果最终的结果已经确定了在 mid - 0.5 到 mid + 0.5之间，那么直接对mid进行四舍五入（实际上上面的V1.0思路有出入，因为如果是(mid - 0.5)*(mid - 0.5)更靠近num，即使x*x是线性的，也不应该让mid 减 0.5,因为，这样会由于后面的转换int出现误差）。 
*/
function getSequire($num=0.0,$precision=0){
	if(!is_numeric($num) || $num < 0
		|| !is_int($precision) || $precision < 0)
		return false; //异常情况
	$num = shiftByDecimal($num, 2 * $precision); //左移被开方数
	$left = 0; $right = $num;

	//求出合适的mid
	while(1){
		$mid = ($left + $right) / 2;
		$powL = ($mid-0.5) * ($mid-0.5);
		$powR = ($mid+0.5) * ($mid+0.5);
		if($powL <= $num && $powR >= $num)
			break;
		if($powL > $num)
			$right = $mid;
		else
			$left = $mid;
	}

	/*
	V1.0（历史代码，暂时注释） 判断是向下还是向上取整
	if($num - $powL < $powR - $num){
		//向下取整
		$mid -= 0.5;
	}else{
		//向上取整
		$mid += 0.5;
	}
	*/

	//V2.0正确的做法是直接让mid + 0.5 然后转int
	$mid += 0.5;
	$mid = (int)$mid;
	$mid = shiftByDecimal($mid, -1 * $precision); //右移获得最终结果
	return $mid;
}

/*
	对一个数进行十进制的左移或者右移
@param number $num 要左移或者右移的数
@param int $decimal 要移动的位数，整数表示向左移 负数表示向右移
@return number 移动之后的数字
*/
function shiftByDecimal($num=0,$decimal=0){
	if($decimal < 0){
		//右移
		while($decimal++ < 0){
			$num /= 10;
		}
	}else{
		//左移
		while($decimal-- > 0){
			$num *= 10;
		}
	}
	return $num;
}

//测试
echo getSequire(0.81, 2);