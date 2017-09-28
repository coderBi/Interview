package test.operator.three;
import java.io.*;

class Main
{
	public static void main(String args[]){
		int result = true ? 1 : 2;
		System.out.println(result); //1
		
		//编译错误，说是2的位置需要bool但是提供了int。也即是说这里解释为(true ? 1) : (2 ? 3 : 4)，是计算第一个: 后面的整体作为一个表达式进行赋值的。相对而言，Java的这种解析是合理的，而已一般的程序中大家都手动给第一个: 后面的部分加上括号便于阅读
		//result = true ? 1 : 2 ? 3 : 4;

		result = true ? 1 : false ? 3 : 4; //1
		System.out.println(result);

		result = false ? 1 : false ? 3 : 4; //4
		System.out.println(result);
	}
}