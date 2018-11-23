#include "GameData.h"
float GameData::_shopData[3][3]={
	{80, 56, 2.99f},
	{50, 40, 1.99f},
	{20, 18, 0.99f}
};

int GameData::getShopBuyTotal(int id){
	return (int)GameData::_shopData[id][0];
}

int GameData::getShopGiveTotal(int id){
	return (int)GameData::_shopData[id][1];
}

float GameData::getShopMoney(int id){
	return GameData::_shopData[id][2];
}

int GameData::getTargetScore(int level){
	int list[36];
	list [0] = 10000;//1000;
	list [1] = 2500;
	list [2] = 4500;
	list [3] = 6500;
	list [4] = 8520;
	list [5] = 10560;
	list [6] = 12620;
	list [7] = 14700;
	list [8] = 16800;
	list [9] = 18920;
	list [10] = 21060;
	list [11] = 23220;
	list [12] = 25400;
	list [13] = 27600;
	list [14] = 29820;
	list [15] = 32060;
	list [16] = 34320;
	list [17] = 36600;
	list [18] = 38900;
	list [19] = 41220;
	list [20] = 43560;
	list [21] = 45920;
	list [22] = 48300;
	list [23] = 50700;
	list [24] = 53120;
	list [25] = 55560;
	list [26] = 58020;
	list [27] = 60500;
	list [28] = 63000;
	list [29] = 65520;
	list [30] = 68060;
	list [31] = 70620;
	list [32] = 73200;
	list [33] = 75800;
	list [34] = 78420;
	list [35] = 81060;
	if(level<=36){
		return list[level-1];
	}else{
		int targetScore = list[35]+(level-36)*1500;
		return targetScore;
	}
}