#include <iostream>
using namespace std;

/*
问题描述：
	两个单向链表，如何判定这两个链表是否存在相交。如何寻找它们的交点。
分析：
	1）由于是单向链表，那么一旦在一个点相交了，那么后续这两个链表也就是完全一样的了。这里如果不考虑链表中存在环的情况，那么可以先获取到两个链表的长度，然后让较长的链表的指针从头走到与短链表一样长的地方，然后两个链表同时向后遍历，如果某一个节点相同了，那么这个节点就是两个链表的交点，如果这两个链表不相交那么他们的交点会是最后的NULL。
	2）下面分析链表如果出存在环的情况。首先，如果一个链表存在环，另一个链表不存在环，可以很容易通过反证法得到这两个链表一定是不相交的（因为一个链表是到不了null的而另一个会到达末尾的null）。那么两个链表如果相交并且有环，那么它们必定都是有环的。因为是单向链表，一旦进入环就出不来，所以两个链表只能共用一个环。判断两个有环的链表是否相交可以在一个链表中查找另一个链表的环入口节点，如果相交由于共用一个环所以必然找得到该节点，如果找不到那么就两个有环链表就不相交。紧接着分析，这两个链表进入环的入口节点是否一样又可以进行两个分析，如果两个链表入环点是一样的，那么可以从这个入环点向回倒退一直找到二者第一个相同的节点为两个链表的交点。如果两个链表的入口节点不一样，那么很容易得到在入环之前二者是没有重合的节点的。这个时候二者所有的交点都在环内，根据实际情况可以返回其中一个入环点为二者的交点。
补充：
	如果发现两个链表都是有环的并且环的入口是一样的，那么这种情况返回的交点可能在环的外面，这种情况可以以环的入口为尾部，然后从两个头部到这个尾部可以看做是两个无环的链表相交交点分析。
*/

struct Node
{
	int data;
	Node * next;
};

/*这个结构体用于保存一个链表的环的入口和入口到链表起始点的距离。如果一个链表无环，入口点应该保存为null，距离应该为链表的长度*/
struct PointAndLen
{
	Node * point;
	int length;
};

/**
* 获取一个链表的环的入口和入口到链表头的距离，如果链表无环，那么入口返回的是null，而距离返回的是链表的长度
* @param Node* head  参与计算的链表
* @return PointAndLen 获取到的环入口和入口到头节点的距离.
*/
PointAndLen GetPointAndLen(Node * head){
	PointAndLen toReturn = {nullptr, 0};
	Node * slow = head, *fast = head;
	//寻找环的入口
	while(fast && fast->next){
		fast = fast->next->next;
		slow = slow->next;
		if(slow == fast){
			//有环
			slow = head;
			while(slow != fast){
				slow = slow->next;
				fast = fast->next;
			}
			break;
		}
	}
	if(fast && fast->next){
		toReturn.point = slow; //交点
	}else{
		toReturn.point = nullptr;
	}

	//计算交点到链表起始点的距离
	while(head != toReturn.point){
		head = head->next;
		toReturn.length++;
	}
	return toReturn;
}

/**
* 获取两个单向链表的交点
* @param Node* link1 单向链表1
* @param Node* link2 单向链表2
* @return Node* 返回两个链表的交点
* @note 如果不相交，会返回null
*/
Node* GetIntersectionOfLinks(Node* link1, Node* link2){
	PointAndLen pl1 = GetPointAndLen(link1),
				pl2 = GetPointAndLen(link2);
	Node * toReturn = nullptr;
	if(!pl1.point && !pl2.point){
		//两个都无环情况
		Node * ptr1 = link1, * ptr2 = link2;
		int sub;
		if(pl1.length > pl2.length){
			//链表1更长一些，让链表1先移动一段距离
			sub = pl1.length - pl2.length;
			for(int i = 0; i < sub; ++i)
				ptr1 = ptr1->next;
			
		}else{
			//链表2更长一些
			sub = pl2.length - pl1.length;
			for(int i = 0; i < sub; ++i)
				ptr2 = ptr2->next;
		}
		//两个链表视为等长的时候同时向后移动两个指针
		for(; ptr2 != ptr1; ptr2 = ptr2->next, ptr1 = ptr1->next){}
		toReturn = ptr2;
	}else if(pl1.point && pl2.point){
		//两个都有环情况
		if(pl1.point == pl2.point){
			//两个的环的入口是一样的，这个时候，可以将环的入口当做尾节点，对两个链表进行类似于无环相交的分析
			int sub;
			Node * ptr1 = link1, *ptr2 = link2;
			if(pl1.length > pl2.length){
				//链表1的起始点距离环的入口更远一些
				sub = pl1.length - pl2.length;
				for(int i = 0; i < sub; ++i){
					ptr1 = ptr1->next;
				}
			}else{
				//链表2的起始点距离环的入口更远一些
				sub = pl2.length - pl1.length;
				for(int i = 0; i < sub; ++i){
					ptr2 = ptr2->next;
				}
			}
			for(; ptr2 != ptr1; ptr1 = ptr1->next, ptr2 = ptr2->next){}
			toReturn = ptr1;
		}else{
			//两个环的入口不一致，通过反证法可以知道这两个链表中的环一定是同一个。那么在两个链表入环之前是不可能产生相交的。所以这个时候可以返回任意一个链表的入口作为相交点
			//在一个链表上查找另一个链表的入口点，如果找到了就表示二者相交，否则它们不相交
			bool found = false;
			for(Node * ptr = pl1.point->next; ptr != pl1.point; ptr = ptr->next){
				if(ptr == pl2.point){
					found = true;
					break;
				}
			}
			if(found)
				//返回其中一个链表的入口当做相交点
				toReturn = pl1.point;
			else
				toReturn = nullptr;
		}
	}else
		//一个有环一个无环，这种情况下两个链表不可能相交，所以结果是null
		toReturn = nullptr;
	return toReturn;
}

int main(){
	//测试
	Node n1, n2, n3, n4, n5;
	n1.next = &n2; n1.data = 1;
	n2.next = &n3; n2.data = 2;
	n3.next = &n4; n3.data = 3;
	n4.next = &n5; n4.data = 4;
	n5.next = &n3; //构成环
	n5.data = 5;

	Node n6, n7, n8, n9, n10;
	n6.next = &n7; n6.data = 6;
	n7.next = &n8; n7.data = 7;
	n8.next = &n9; n8.data = 8;
	n9.next = &n10; n9.data = 9;
	n10.next = &n4; //另一个环入口n4
	n10.data = 10;
	
	//有环相交测试
	Node * result = GetIntersectionOfLinks(&n1, &n6);
	if(!result){
		cout << "there is no intersection between the two links" << endl;
	}else{
		cout << "the data of the intersection is: " << result->data << endl; //3
	}

	//一个有环一个无环测试
	n10.next = nullptr;
	result = GetIntersectionOfLinks(&n1, &n6);
	if(!result){
		cout << "there is no intersection between the two links" << endl; //不可能相交
	}else{
		cout << "the data of the intersection is: " << result->data << endl;
	}

	//两个都无环相交测试
	n5.next = &n9;
	result = GetIntersectionOfLinks(&n1, &n6);
	if(!result){
		cout << "there is no intersection between the two links" << endl;
	}else{
		cout << "the data of the intersection is: " << result->data << endl; //9
	}
	return 0;
}