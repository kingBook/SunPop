#ifndef __STARS_BOARD_H__
#define __STARS_BOARD_H__
#include "cocos2d.h"
class StarsBoard{
public:
	StarsBoard();
	static StarsBoard* create();
	StarsBoard orHandler(StarsBoard value);
	int getTrueCount();
	void setAll(bool value);
	bool getValue(int p);
	void setTrue(int p);
	void setFalse(int p);
	bool isEmptyColumn(int index);
	void setColumn(int index,int value);
	int getColumn(int index);
	void pop(int p);
	void push(int p, bool val);
	void fillPath(StarsBoard mTable, StarsBoard fullBoard, int p, int retval[],int &retcnt);
	void logMy();
	void dispose();
private:
	int* _list;
};

#endif