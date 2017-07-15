<?php
//测试php对于未赋值  赋值为null  赋值为false 等 判断结果
$a; //只申明变量，没有进行赋值
$b = null; //赋值为null
$c = false; //赋值为false
$d = 0;
var_dump(isset($a)); //false 
var_dump(isset($b)); //false
var_dump(isset($c)); //true
var_dump(isset($d)); //true
unset($d); //变量unset
var_dump(isset($d)); //false


/*
小结：
	isset只对于变量没有赋值，或者是变量赋值为null，或者是变量被unset了，会返回false。其他情况返回的都是true
*/