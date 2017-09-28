<?php
/*
题目描述：
	js和php中对于全局变量的访问有什么不同
分析：
	php中默认是不能函数外部变量的，也即是不能直接访问全局变量，默认情况下也不能直接访问闭包环境中的外部函数中的变量。如果要使用全局变量可以是用global $a。如果要使用父级环境中的变量可以使用use $var。而在js中对于闭包环境中的变量（包括全局变量）可以直接访问。
*/
$g = 1;
$func = function(){
	$c = 2;
	//如果要使用父级函数中的变量需要在闭包函数上使用use
	$sum = function() use($c){
		//要使用全局的变量需要使用global关键字，注意全局变量都保存在$GLOBALS中，和闭包解析不一致，这里如果不是用global引入，而是在上面的use中追加一个$g，那么会因为找不到$g的定义而引入了一个为null的变量$g
		global $g;
		return $g + $c;
	};
	$c = 100; //由于闭包中是值传递，所以这里更改不会影响sum函数的结果了
	return $sum;
};
$result = $func();
var_dump($result); //输出结果是class Closure#2(1){public $static => array(array(1){'c' => int(2)});}。通过这个结果可以发现use其实是向内部的函数(其实这是一个闭包类，已经不是简单的函数了)加上了一个$static的属性，这个属性是一个数组，数组中每一项就对应一个use的内容.
var_dump($result()); //3