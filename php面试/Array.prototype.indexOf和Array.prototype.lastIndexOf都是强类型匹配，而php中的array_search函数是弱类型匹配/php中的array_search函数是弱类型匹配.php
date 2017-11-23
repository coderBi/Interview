<?php
/*
关于indexOf lastIndexOf和php中的array_search:
	Array.indexOf()和Array.lastIndexOf()：这两个函数是获取某一个值第一次出现和最后一次出现的位置。注意这两个函数的传入参数在内部是进行强类型匹配的。也就是说Array.indexOf(1)和Array.indexOf('1')的结果可能是不同的。这也是php中的array_search()函数不同的地方。
*/
$arr = array(
	1,
	'1',
	2,
	'2'
);

//php中是弱类型匹配。
echo array_search('1',$arr) . "\n"; //0
echo array_search('2',$arr) . "\n"; //2