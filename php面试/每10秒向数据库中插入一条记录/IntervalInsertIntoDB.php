<?php
/*这是一道公司的面试题 说是要执行一个php  实现每10s插入一个记录 数据库表可以自定义*/
//因为要定时执行，这里设置脚本永久执行
set_time_limit(0);

//连接数据库
function connectDB(){
	//配置  
	$host = 'localhost';        
	$port = 3306;
	$user = 'root';
	$password = '123';
	//$database = 'learn_mysql';
 
        //连接
	$mysqli = new mysqli($host.':'.$port,$user,$password);
	return $mysqli;
}

//连接数据库
$mysqli = connectDB();
if(!$mysqli)
 die('connect db failed, please check the config about the db connect and make sure the DBMS is running correctly');

$mysqli->query('set names utf8');

/*配置本次脚本要创建的数据库和数据库表*/
//创建一个新的测试数据库和一张测试表
$company = 'company1'; //应聘公司名
$person_name = 'bww'; //应聘这名字
$dbname = $company.'_'.$person_name;
//检测数据库是否存在
$sql = "select * from information_schema where schma_name='$dbname'";
$result = $mysqli->query();
while(!empty($result)){
	$dbname .= rand();
	$result = $mysqli->query();
}
//创建数据库
$mysqli->query("create database $dbname");
$mysqli->query("use $dbname");
//创建表
$tablename = 'test';
$mysqli->query("create table $tablename(
id int unsigned auto_increment not null,
username varchar(20) not null,
password varchar(50) not null,
primary key(id),
unique key(username)
)engine=myisam charset=utf8;");

//每10s执行一次插入sql
while(1){
	//因为设计的时候username是唯一的  所以这里加上一个time()
	$username = 'username'.time();
	$sql = "insert into $tablename values(null,'$username','testpassword')";
	if(false === $mysqli->query($sql))
		echo 'insert into db failed\n';
	else
		echo 'insert into db successfully\n';
	sleep(10);
}
