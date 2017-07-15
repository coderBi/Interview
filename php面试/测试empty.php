<?php
//测试empty为false的情况

//所有的0
var_dump(empty(0));
var_dump(empty(''));
var_dump(empty('0'));
var_dump(empty(null));
var_dump(empty(0.0));
var_dump(empty(false));

echo "===================================\n";

//空数组
var_dump(empty(array()));

echo "===================================\n";

//空对象  网上说没有任何属性的对象是空的，但是这里测试的结果说明并非如此。
class Test{}
$t = new Test;
var_dump(empty($t)); //这结果是false，也就是没有任何属性的对象判断不是空的
var_dump($t);  //空对象

/*
小结：

*/