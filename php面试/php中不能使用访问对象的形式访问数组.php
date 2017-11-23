<?php
//php中不能使用访问对象的形式访问数组，但是js中二者没有区别，都是接受的

$arr = array(
	'name' => 'coder',
	'age' => 11
);

echo $arr->name; //抛出的一个notice：trying to get property of non-object