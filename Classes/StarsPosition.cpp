#include "StarsPosition.h"

StarsPosition::StarsPosition(StarsBoard* starsBoards){
	_starsBoards = starsBoards;
	/*for(int i=0;i<5;i++){
		_starsBoards[i].logMy();
	}*/
	_sumPop=0;
	_nDistance=0;
}

int StarsPosition::getBlackByPoint(int p, int retval[]){
	int tmpcnt = 0;
	int i;
    StarsBoard mTable;
    StarsBoard fullBoard; //二值化完整棋盘，用于判定是否为空行
    for (i = 0; i < 5; i++)fullBoard=fullBoard.orHandler(_starsBoards[i]);
	for (i = 0; i < 5; i++){
        if (_starsBoards[i].getValue(p)){
            _starsBoards[i].fillPath(mTable, fullBoard, p, retval, tmpcnt);
            retval[100] = (int)(i);        //颜色
            retval[101] = (int)(tmpcnt);   //长度
			//CCLOG("%d %d",i, tmpcnt);
            return tmpcnt;
        }
    }
    return 0;
}

int StarsPosition::doPop(int point[]){
	int cnt = point[101];
    int vl = cnt * cnt * 5;
    int i,j;
    //累计分值
    _sumPop += vl;
    //更新步数
    _nDistance++;
    //消除块；消除时会导致当前位置消失更高位置下降
    for (i = 0; i < 5; i++){
        for (j = 0; j < cnt; j++) {
            _starsBoards[i].pop(point[j]);
        }
    }
    return vl;
}

void StarsPosition::doPopOne(int p){
	for(int i = 0; i < 5; i++) _starsBoards[i].pop(p);
}

int* StarsPosition::doMoveToLeft(){
	int* ret=new int[11];
	int c;  int i;
	StarsBoard fullBoard; //二值化完整棋盘，用于判定是否为空行
    StarsBoard* tmpBoard=new StarsBoard[5]; //新的棋盘数组
	
	for (c = 0; c < 5; c++){
        fullBoard=fullBoard.orHandler(_starsBoards[c]);
		StarsBoard newStarsBoard;
        tmpBoard[c] = newStarsBoard;
    }
	//遇到非空行就复制到新的之中
    int curidx = 0;
    for (i = 0; i <10; i++){
        if (!fullBoard.isEmptyColumn(i)){
            for (c = 0; c < 5; c++){
                tmpBoard[c].setColumn(curidx,(int)(_starsBoards[c].getColumn(i)));
            }
            ret[curidx] = i;    //记录当前位置存储的是原来的第几列。
            curidx++;
        }
    }
    //记录有效个数
    ret[10] = curidx;

    //替换现有引用
	delete _starsBoards;
    _starsBoards = tmpBoard;
    return ret;

}

int StarsPosition::nextGenerateMove(){
	int cnt=0;
	int tmpcnt=0;
	StarsBoard mTable;
    StarsBoard fullBoard; //二值化完整棋盘，用于判定是否为空行
	for (int c = 0; c < 5; c++)fullBoard = fullBoard.orHandler(_starsBoards[c]);
    int p;
	for (int c=0; c<5; c++){//遍历颜色
		mTable=StarsBoard();
		for(int y=0; y<10; y++){//遍历坐标
			for(int x=0; x<10; x++){
				p=(int)((x<<4)|y);
				int tmpps[102]={};
				if(mTable.getValue(p)==false){
					_starsBoards[c].fillPath(mTable, fullBoard, p, tmpps, tmpcnt);
					if(tmpcnt>1){
						tmpps[100]=(int)(c);//颜色
						tmpps[101]=(int)(tmpcnt);//长度
						cnt++;
					}
				}
			}
		}
	}
	return cnt;
}

void StarsPosition::dispose(){
	_starsBoards->dispose();
	delete _starsBoards;
	_starsBoards=NULL;
}

StarsBoard* StarsPosition::getStarsBoards(){
	return _starsBoards;
}