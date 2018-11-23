#include "RandomArr.h"
#include <iostream>
#include <string>
using namespace std;

int RandomArr::_list[MAX_ID]={};
int RandomArr::_ranIdList[MAX_ID]={};
int RandomArr::_nextRandomId=-1;

void RandomArr::instance(){
	int id=0,i,j;
	for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            _list[id] = (int)((i << 4) | j);
            id++;
        }
    }
	for(i=0;i<MAX_ID;i++)_ranIdList[i]=i;
	randomize(_ranIdList,MAX_ID);
}

void RandomArr::randomize(int list[], int maxId){
	int i, id0, id1;
    for(i = 0; i < maxId; i++) {
        id0 = (int)(RandomArr::nextRandom()*maxId);//取0~maxId(不包含maxId)间的随机数
        id1 = list[i];
        list[i] = list[id0];
        list[id0] = id1;
    }
}

//产生cnt个元素，各个元素的和为sum，元素的最小值为min，元素的最大值为max的32位整数数组。
int* RandomArr::randElement(int sum, int cnt, int min, int max){
	int* tmp=new int[cnt];
	int mn = sum / cnt;
    int i;
	for(i = 0; i <= cnt - 2; i++) {
        tmp[i] = mn;
    }
	//最后一个元素用来容纳转整时产生的小数部分，保证和。
    tmp[cnt - 1] = sum - mn * (cnt - 1);
	//随机化等值加减
    int a1,a2,r1,rn;
	for(i = 0; i <= cnt - 1; i++) {
		//取一个随机差
		r1 = (int)(RandomArr::nextRandom()*(max - min + 1));
		//加减随机差之后两个数据
		a1 = tmp[i] + r1;
		do //防止自身加减，会导致仅记录减法结果。并且，导致数据变换次数减小。
		{
			rn = (int)(RandomArr::nextRandom()*(cnt - 1));
		} while(!(rn != i));
		a2 = tmp[rn] - r1;
		//不超范围的进行加减
		if(a1 >= min && a1 <= max && a2 >= min && a2 <= max) {
			tmp[i] = a1;
			tmp[rn] = a2;
		}
	}
	return tmp;
}

int RandomArr::getNextRandomElement(){
	if(_nextRandomId==MAX_ID-1)_nextRandomId=-1;
	_nextRandomId++;
	int id=_ranIdList[_nextRandomId];
	return _list[id];
}

float RandomArr::nextRandom(){
	return CCRANDOM_0_1();
}