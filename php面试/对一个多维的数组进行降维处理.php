<?php
/*
题目要求：
	1，数组的维度可能超过三层
	2，原来的 ['key1'=>['key2'=>'value']] 转换为 ['key1.key2'=>'value']
*/

/*
	进行数组的降维
@param array $arr 要降维的数组
@return array result 处理后数组
*/
function decreaseArray($arr=array()){
	return _decreaseArray($arr,'');
}

/*
	带key表示前缀的数组降维
@param array $arr 要降维的数组
@param string $prefix key前缀
@return array 处理好的数组
*/
function _decreaseArray($arr=array(),$prefix=''){
	$toReturn = array();
	foreach($arr as $key=>$value){
		$newPrefix = $prefix ? "$prefix.$key" : $key;
		if(is_array($value)){
			$subArr = _decreaseArray($value,$newPrefix);
			foreach($subArr as $_key=>$_value){
				$toReturn[$_key] = $_value;
			}
		}else{
			$toReturn[$newPrefix] = $value;
		}
	}
	return $toReturn;
}

// 测试
$arr = array(
	'key1'=>'value1',
	'key2'=>'value2',
	'key3'=>array(
		'key4'=>'value4',
		'key5'=>'value5',
	),
	'key6'=>'value6',
	'key7'=>array(
		'key8'=>'value8',
		'key9'=>array(
			'key10'=>'value10',
			'key11'=>'value11',
		),
	),
);
$result = decreaseArray($arr);
var_dump($result);