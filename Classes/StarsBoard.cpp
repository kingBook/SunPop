#include "StarsBoard.h"
#include<iostream>
#include<vector>
#include <algorithm>  
using namespace std;
StarsBoard::StarsBoard(){
	_list = new int[10];
	for(int i=0;i<10;i++){
		_list[i]=0;
	}
	//CCLOG("%s","StarsBoard()");
}

StarsBoard* StarsBoard::create(){
	return new StarsBoard();
}

StarsBoard StarsBoard::orHandler(StarsBoard value){
	for(int i=0; i<10; i++){
		_list[i] = (int)(_list[i]|(value._list[i]));
	}
	return (*this);
}

int StarsBoard::getTrueCount(){
	int i=0,c=0,v=0;
	for(i=0;i<10;i++){
		v=_list[i];
		while(v>0){
			v=v&(v-1);
			c++;
		}
	}
	return c;
}

bool StarsBoard::getValue(int p){
	return (_list[p>>4] & (1 << (p & 0xF)))!=0;
}

void StarsBoard::setTrue(int p){
	_list[p >> 4] = (int)(_list[p >> 4] | (1 << (p & 0xF)));
}

void StarsBoard::setFalse(int p){
	_list[p >> 4] =(int)(_list[p >> 4] & ~(1 << (p & 0xF)));
}

bool StarsBoard::isEmptyColumn(int index){
	return _list[index]==0;
}

void StarsBoard::setColumn(int index,int value){
	_list[index] = value;
}

int StarsBoard::getColumn(int index){
	return _list[index];
}

void StarsBoard::setAll(bool value){
	int num = value?-1:0;
	int i;
	for(i=0;i<10;i++){
		_list[i]=num;
	}
}

void StarsBoard::pop(int p){
	int num;
    int index = (int)(p >> 4);
    int num4 = p & 15;
    int num2 = _list[index] & (((int)(-1)) << (num4 + 1));
    if ((_list[index] & (((int)1) << num4)) != 0){
        num = _list[index] & ~(((int)(-1)) << num4);
    }else{
        num = _list[index] & ~(((int)(-1)) << (num4 + 1));
    }
    _list[index] = num2 | (num << 1);
}

void StarsBoard::push(int p, bool val){
	int index = (int)(p >> 4);
    int num4 = p & 15;
    int num2 = _list[index] & (((int)(-1)) << (num4 + 1));
    if (val) num2 |= ~(((int)(-1)) << (num4 + 1)) & (((int)(-1)) << num4);
    int num = _list[index] & ~(((int)(-1)) << (num4 + 1));
    _list[index] = num2 | (num >> 1);
}

int cmp( const void *pFirst, const void *pSecond){

    int nA = *(( int *)pFirst);

    int nB = *(( int *)pSecond);

    return (nA<nB ? -1 : nA>nB ? 1 : 0); // 由小到大排序
}

void StarsBoard::fillPath(StarsBoard mTable, StarsBoard fullBoard, int p, int retval[],int &retcnt){
	vector<int> mArray;
	int mP = p; //正在处理点
    int mAP; //临时变量——可能被入栈的点
    int cnt = 0;
	int x;
	int i;
	mArray.push_back(mP);
	do{
        if (mTable.getValue(mP) == false){ //若未处理过
            x = mP >> 4;
            if ((_list[x] & (1 << (mP & 0xF))) != 0){ //若有子
                //临近点入栈
                if ((mP & 0xF) > 0){ //上
                    mAP = (int)(mP - 1);
                    if (!mTable.getValue(mAP)){
                        mArray.push_back(mAP);
                    }
                }
                if ((mP & 0xF) < 10){ //下
                    mAP = (int)(mP + 1);
                    if (!mTable.getValue(mAP)){
                        mArray.push_back(mAP);
                    }
                }
                if (x > 0){ //左
                    mAP = (int)(mP - 0x10);
                    if (!mTable.getValue(mAP)){
                        for (i = x - 1; i >= 0; i--){
                            if (fullBoard._list[i] != 0){
                                mAP = (int)((i << 4) | (mP & 0xF)); //向左查找第一个非空行取坐标。
                                break;
                            }
                        }
                        mArray.push_back(mAP);
                    }
                }
                if (x < 9){ //右
                    mAP = (int)(mP + 0x10);
                    if (!mTable.getValue(mAP)){
                        for (i = x + 1; i <= 9; i++){ //向右查找第一个非空行取坐标。
                            if (fullBoard._list[i] != 0){
                                mAP = (int)((i << 4) | (mP & 0xF));
                                break;
                            }
                        }
                        mArray.push_back(mAP);
                    }
                }
                //记录本点
                retval[cnt] = mP;
                cnt++;
            }
            mTable.setTrue(mP); //修改为已处理
        }
        if (mArray.size() == 0){ //还有点就出栈，没有就结束
            break;
        }else{
			mP = mArray.at(mArray.size()-1);
			mArray.pop_back();
		}
    } while (true);
    //按Y进行排序，以便恢复局面时使用。
	/*CCLOG("%s","a");
	for(int k=0;k<102;k++){
		CCLOG("%d",retval[k]);
	}*/
	qsort(retval,cnt,sizeof(int),cmp);
	/*CCLOG("%s","b");
	for(int k=0;k<102;k++){
		CCLOG("%d",retval[k]);
	}*/
    //返回有效个数
    retcnt = cnt;
}

void StarsBoard::dispose(){
	delete _list;
	_list=NULL;
}


void StarsBoard::logMy(){
	CCLOG("%d %d %d %d %d %d %d %d %d %d", _list[0],_list[1],_list[2],_list[3],_list[4],_list[5],_list[6],_list[7],_list[8],_list[9]);
}
