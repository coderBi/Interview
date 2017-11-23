<?php
/*
问题描述：
	在php中可以直接使用一个变量后面带上括号表示要进行一个相应的函数的调用。但是通过实际测试php中不能连续书写两个括号进行连续的两次这种类型的调用。另一方面，在php中没有如果直接书写向js中那样的匿名函数立即执行也通不过，表示括号是“unexpected”
*/

/*匿名函数直接执行，编译通不过
(function(){
	echo "\nthe text in the nonamed function\n";
})(); //error：unexpected "("。其实php中匿名函数只能通过闭包，而闭包只能是函数表达式。所以不能直接像js中那么样进行匿名函数的直接执行
*/

$func = function(){
	echo "\nthe text in the express function\n";
	return "another";
};
$another = function(){
	global $func;
	echo "\nthe text in another function\n";
	return $func;
};

$func();
//$func()(); //编译通不过，因为第二个"("是不合法的。
$a = $func();
//$a(); //error: 提示调用的名称为another的函数没定义。因为上面只是用$another进行了一个函数的引用保存，实际上这个函数是一个匿名
$b = $another();
$b(); //利用返回的函数的引用直接调用，和上面的利用名称调用不同。这里可以得到正确结果

//$another()(); //编译错误，因为无论第一个$func()返回的是任何数据类型，都不能直接链式调用
