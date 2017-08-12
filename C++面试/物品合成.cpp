/*
题目描述：
	有一堆物品（用数字的id表示）存储在数组里面，item_array[]={1001,1002,1001,....1100}，可能存在多个相同物品。
	给定下满两个和合成公式：
		1）消耗3个物品1001 + 5个物品1043可以合成一个物品2000
		2）消耗2个1001 + 4个1002可以合成一个1043
	现要求写一个函数，求一堆物品可以合成多少个2000。
思路与分析：
	Versin1.0: 2000需要的材料1043可以被合成，如果给定的物品中有1043，那么一方面要考虑1043，另一方面还得考虑合成多少1043，这个问题如果换一个思路，将原来给定数组中的1043先进行拆解为2个1001和4个1002，那么每一个2000需要的材料为 3个1001 + 5 * (2个1001 + 4个1002) = 13个1001 + 20个1002
	根据上面描述的思路，可分为三个步骤：
		扫描输入的数组，统计1002 1001 1043 个数
		拆分1043
		统计1001和1002，综合计算最后结果
	Version2.0: 上面的1.0存在明显的bug，可以分析这样一个特例，如果只有一个1001，而有一堆的1043，那么本来2000应该一个都合成不了的，但是由于有部分的1043进行了分解产生了1001导致可以合成2000。也就是1.0提出的先分解再合成的思路有问题或者需要改进。
	算法改进：
		先利用提供的1001和1043进行合成，计算出第一批的2000
		然后在剩下的原料中查看是否存在多余的1001，如果1001多出来的数量多余3，那么也就是1043不够用，否则1043有剩余，既然1043没有剩余，那么可以放心大胆的用Version1.0的思路先拆分1043然后统计1001和1002计算出另一批的2000。
细节：
	这里的题目描述说的是“合成”2000，好像题目中隐藏了提供的原材料中不会出现2000，所以这里也没有进行相关的2000统计。可能不是很严谨，但是这是基于题目的“合成”的表述进行书写。
*/

#include <iostream>
using namespace std;

struct GoodsNum
{
	int g1001;
	int g1002;
	int g1043;
};

GoodsNum goodsNum  = {0};

/*
	统计的各种物品的个数，这里只统计1001 1002 1043
*/
void AddUp(int item_array[], int item_num){
	for(int i = 0; i < item_num; ++i){
		switch(item_array[i]){
			case 1001:
				goodsNum.g1001++;
				continue;
			case 1002:
				goodsNum.g1002++;
				continue;
			case 1043:
				goodsNum.g1043++;
				continue;
			default:
				continue;
		}
	}
}

/*
	拆分1043，修改统计计数
*/
void Divide1043(){
	goodsNum.g1001 += goodsNum.g1043 * 2;
	goodsNum.g1002 += goodsNum.g1043 * 4;
	goodsNum.g1043 = 0;
}

/*
	统计可合成多少个2000
@return int 可以合成的2000的个数
*/
int GetNumOf2000(){
	int max2000A = goodsNum.g1001 / 13;
	int max2000B = goodsNum.g1002 / 20;
	return goodsNum.g1001 / 13 > goodsNum.g1002 / 20 ? goodsNum.g1001 : goodsNum.g1002 / 20;
}


/*
	统计可以合成多少2000
@param int item_array[] 输入的物品数组
@param int item_num 输入的物品的数量
@return int  这堆物品可合成的2000的个数
*/
int func(int item_array[], int item_num){
	int toReturn = 0;
	//统计三种物品个数
	AddUp(item_array, item_num);
	//解决version1.0的拆分bug：先计算不拆分之前可以合成的2000个数
	int max2000A = goodsNum.g1001 / 3;
	int max2000B = goodsNum.g1043 / 5;
	if(max2000A <= max2000B){
		toReturn = max2000A;
		goodsNum.g1001 %= 3;
		goodsNum.g1043 -= 5 * max2000A;
		//执行到这个判断里面说明1001不够多，这里可直接返回不用接着拆分1043进行下一步的计算了（注意这里提到的拆分其实是为了更好的计算1043的合成）
		return toReturn;
	}else{
		toReturn = max2000B;
		goodsNum.g1001 -= 3 * max2000B;
		goodsNum.g1043 %= 5;
	}
	//拆分1043
	Divide1043();
	//获取最后可得到的2000的个数
	toReturn += GetNumOf2000();
	return toReturn;
}

int main(){
	int test[] = {1001,1001,1001,1001,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043,1043};
	cout << func(test,26) << endl;
	return 0;
}