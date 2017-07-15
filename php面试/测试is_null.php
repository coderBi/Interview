<?php
//测试is_null函数 

$a; //未赋值
$b = null; //赋值为null
$c = 0; 

var_dump(is_null($a)); //true
var_dump(is_null($b)); //true
var_dump(is_null($c)); //false
unset($c);
var_dump(is_null($c)); //true 注意由于前面已经unset了，这里显示会抛出一个错误提示。使用了undefined的变量

/*
小结：
	isset是只有没有赋值或者赋值为null 或者被unset了才返回false。而is_null只有这三种情况才返回true。所以isset与is_null返回情况相反。
*/