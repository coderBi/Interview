package test.string.args;
import java.io.*;

/*
题目描述：
	String[] args 与 String args[]的写法有什么不同。
分析：
	从语意上讲，两者是有不同的，String[]本身表示字符串数组类型，String[] args定义了一个字符串数组类型的引用。而String args[]定义一个数组，数组中每一个元素是一个String类型的引用。但是实际使用中二者没有区别，二者都是使用new一个String数组进行初始化: String[] arg1 = new String[10] 和 String arg2[] = new String[10]。从存放的角度二者都是存放new的这片空间的其实地址，但是从语意上一个是数组名一个是指向数组的引用（从C++的角度可以理解为别名），所以二者是一样的使用效果。
*/

class Main
{
	public static void main(String[] args){
		String[] arg1 = new String[10];	
		String arg2[] = new String[10];
		System.out.println(arg2 instanceof String[]);  //打印true 可以看到二者是一样的数据类型，而内存中存储的又是一样的地址的引用，所以二者没有任何区别（或者可以说仅仅是语意理解上的区别，没有使用上的区别）
	}
}