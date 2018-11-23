#ifndef __STARS_POSITION_H__
#define __STARS_POSITION_H__
#include "StarsBoard.h"

class StarsPosition{
public:
	StarsPosition(StarsBoard* starsBoards);
	int getBlackByPoint(int p, int retval[]);
	int doPop(int point[]);
	void doPopOne(int p);
	int* doMoveToLeft();
	int nextGenerateMove();
	StarsBoard* getStarsBoards();
	void dispose();
private:
	int _sumPop;
	int _nDistance;
	StarsBoard* _starsBoards;
};
#endif