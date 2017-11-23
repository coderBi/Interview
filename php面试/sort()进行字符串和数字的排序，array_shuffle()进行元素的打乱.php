<?php
/*
问题描述：
	利用php中的sort()函数，如何实现对整数数组的排序，如何实现对字符串的自然排序。如何实现一个数组中元素的打乱排序。
分析：
	sort()函数默认是自然排序的，其中第二个参数是可以指定排序的方式的。sort($arr, SORT_STRING)指示进行自然排序。sort($arr, SORT_NUMERIC)指示进行数字大小的排序。
	php中存在一个函数shuffle()，内部使用随机数，进行元素的打乱重排序。
*/

//sort进行字符串数组的自然排序(默认模式)
$strings = array(
	'c',
	'b',
	'a'
);
sort($strings);  //也可以明确的书写为sort($strings, SORT_STRING)
var_dump($strings);  //a b c


//sort()进行数字序列的排序
$numbers= array(
	11,2,1
);
sort($numbers, SORT_NUMERIC);
var_dump($numbers); //1 2 11

//使用shuffle()进行打乱
$merge = array_merge($strings, $numbers);
shuffle($merge);  //打乱
var_dump($merge);