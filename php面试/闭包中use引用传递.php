<?php
//在闭包函数上使用use指定引入传递的方式引入一个父级变量。效果和参数的引用传递类似
$va = 1;
$func = function() use(&$va){
	echo "va: $va\n";
	$va = 100;
};
$func();
echo "the new va is : $va\n";  //100，也即是由于是引用传递，所以在func的内部进行了va的修改