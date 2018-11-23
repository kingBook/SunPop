#ifndef __RANDOM_ARR_H__
#define __RANDOM_ARR_H__
#define MAX_ID 100
#include "cocos2d.h"

class RandomArr{
public:
	static void instance();
	static void randomize(int list[], int maxId);
	static int* randElement(int sum, int cnt, int min, int max);
	static int getNextRandomElement();
private:
	static int _nextRandomId;
	static int _list[MAX_ID];
	static int _ranIdList[MAX_ID];
	static float nextRandom();
};

#endif