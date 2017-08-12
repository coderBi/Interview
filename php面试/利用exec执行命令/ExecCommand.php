<?php
/*string exec(command,array,result_state)*/
/*exec这个命令 在php中返回值是最后一样结果  但是这个函数有两个可选参数，第二个参数是一个数组，如果提供了，程序会在运行时将结果的每一行依次加入到这个数组的后面，第三那个参数是命令执行返回的状态码，一般是0*/
// exec ls
$arr = array();
$result = exec('ls',$arr);
var_dump($result); //这里只有最后一行的结果
var_dump($arr);  //这里有所有的返回结果

echo '-------------------------------------';

//exec chmod
$result = exec('chmod 755 . -R',$arr,$state);
var_dump($result);
var_dump($arr); //由于chmod函数没有输出 所以没有向$arr中追加数据，所以结果还是原来的$arr。注意exec只是追加结果到数组后面，不会修改或者清空原来数组中的内容
var_dump($state); //0

echo '-------------------------------------';

//exec crontab
//crontab格式: 分钟  小时  天  月 星期 命令
$crontab = 'echo "*/2 * * * * ls" >> /etc/crontab';
$result = exec($crontab); //提示无权限 /etc/crontab需要管理员权限
var_dump($result);
//对于每个用户存在/usr/bin/crontab的配置
$crontab = 'echo "*/2 * * * * ls" >> /usr/bin/crontab'; //测试发现这个文件也不能直接写入，这个文件的主人也是root。一般只能通过crontab -e进行定时操作了
$result = exec($crontab);
 var_dump($result);

echo '-------------------------------------';
