<?php
/*
	php与js一样，只分析函数内部的变量与全局变量，但是php中没有单独的定义局部变量的表示var。而且在php中使用全局变量之前需要使用global申明。基于以上两点，在php中如果使用了global申明，那么申明下面的部分使用的是全局变量，而申明上面的使用的是局部变量（如果有定义）(而js中如果函数内部有申明，无论这个申明在哪里，都会认为进行了屏蔽)
*/

$g1 = 'hello';
$g2 = 'world';

function test(){
	global $g1;
	var_dump($g1); //引入了全局的hello
	var_dump($g2); //没有申明使用全局的变量，也没有定义局部的变量，所以这里会有一个notice，输出的结果为null
	$g2 = 100;
	var_dump($g2); //int 100

	//申明要使用全局的g2
	global $g2;
	var_dump($g2); //输出的是全局的g2 world
}
test();