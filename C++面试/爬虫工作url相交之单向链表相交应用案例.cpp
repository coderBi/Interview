#include <iostream>
#include <stdio.h>
#include <sstream>
using namespace std;

/*
问题描述：
	单向链表相交判定的应用：网页爬虫的原理是从一个入口的网页开始查找这个网页中所有的url，然后紧接着查找下一个url中包含的url。这个查找的结束条件是查找某一个页面的时候发现其中所有的页面都已经被查过了或者是某一个页面中不包括任何的url了。现在简化问题为一个页面只能包含一个url，爬虫通过爬两个入口网页形成了两个链表，如何判定这两个链表中是否存在相同的url。
分析：
	两次组成的链表内存结构是分开的，也就是物理上next不是有环无环的依据。链表中有一个url属性是这个页面上存放的url，这个url可能为空。所以实际分析链表的相交性主要是集中在url属性上。同一般性的链表相加分析一样，首先如果两个链表是无环的（这里的有环无环是相对于url属性的）那么爬虫在两次走到相同的url之后接下来链表节点中的url属性都是一样的，通过这个分析可以知道两个链表中的最后一个节点的url属性是一样的。上述的分析是判断无环的两个链表相交的，如果有环相交，和一般性判断一样二者要想相交一定都是有环的，而且一定是有一个相同的环(因为是单向链表，进入一个环就不能出来再进入另一个环)。可以很容易的分析得到两个链表的尾部节点一定都在环上，所以在存在环的时候可以在一个链表中查找另一个的尾节点，如果找到就表示有环相交，如果没有找到就不可能相交。
综合：
	上面尽管分析了两种情况，但是仔细分析可以发现可以通过一个操作合并两种分析，那就是先找到一个链表的尾部节点，然后在另一个链表中寻找这个尾部节点，如果是在另一个链表的非尾部找到了，我们可以通过反证法知道原先的尾部节点所在的链表一定是构成了环的，二者有环相交。如果是在另一个链表的尾部找到，那么可以认为是两个无环链表相交（其实也可能是相同的环入口相交，这是一个临界情况）。
*/

struct URLNode
{
	std::string url;
	URLNode * next;
};

/**
* 判断两次爬虫构成的链表中是否存在重合的url
*
* @param URLNode * list1 爬虫采集到的链表1
* @param URLNode * list2 爬虫采集到的链表2
* @return bool 如果两个链表中存在相同的url就返回true 否则返回false
* @note 通过内部详细的分析，只需要在一个链表中寻找另一个链表的尾节点url，如果找到了就是相交的，这包括了有环相交和无环相交
*/
bool IsIntersected(URLNode * list1, URLNode * list2){
	if(!list1 || !list2)
		return false;
	URLNode * tail1 = list1;
	//寻找第一个链表的尾节点
	while(tail1->next)
		tail1 = tail1->next;
	//在另一个链表中寻找尾节点的url
	for(URLNode * p = list2; p != nullptr; p = p->next){
		if(p->url == tail1->url)
			return true;
	}
	return false;
}

int main(){
	//测试
	URLNode * list1 = new URLNode;
	URLNode * p = list1;
	for(int i = 0; i < 5; i++){
		p->url = ((ostringstream&)(ostringstream() << i)).str();
		p->next = new URLNode;
		p = p->next;
	}
	p->next = nullptr;
	p->url = "5";

	URLNode * list2 = new URLNode;
	p = list2;
	for(int i = 10; i < 15; i++){
		p->url = ((ostringstream&)(ostringstream() << i)).str();
		p->next = new URLNode;
		p = p->next;
	}
	p->next = nullptr;
	p->url = "10";

	cout << boolalpha << IsIntersected(list1,list2) << endl; //false 第一个链表无环第二个链表有环
	p->url = "5";
	cout << boolalpha << IsIntersected(list1,list2) << endl; //true 无环相交 相交点在最后一个节点
	return 0;
}