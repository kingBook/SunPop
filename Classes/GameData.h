#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__
#include <iostream>
#include <vector>
using namespace std;

/*
 * �Ƿ񴴽��̵�
 */
#ifndef GAME_IS_CREATE_SHOP
#define GAME_IS_CREATE_SHOP 0 
#endif

/*
 * �Ƿ񴴽����а�
 */
#ifndef GAME_IS_CREATE_LEADERBOARD
#define GAME_IS_CREATE_LEADERBOARD 0 
#endif

class GameData{
public:
	static int getTargetScore(int level);
	static int getShopBuyTotal(int id);//�������
	static int getShopGiveTotal(int id); //���͵�����
	static float getShopMoney(int id);//��Ҫ���ѵĽ�Ǯ
	static const bool isDebug=false;
private:
	static float _shopData[3][3];
};
#endif

/*




�̳�	
$0.99 	20+18 shopBtn0 com.qywl.killBlock.shopBtn0 ������ʯx20����x18 ����$0.99���38����ʯ
$1.99 	50+40 shopBtn1 com.qywl.killBlock.shopBtn1 ������ʯx50����x40 ����$1.99���90����ʯ
$2.99 	80+56 shopBtn2 com.qywl.killBlock.shopBtn2 ������ʯx80����x56 ����$2.99���136����ʯ

///���ش�	------��ȡ��
////$1.99 	50+40 bag0 com.qywl.killBlock.bag0 ������ʯx50����x40 ����$1.99���90����ʯ

��ȡ�����	
$0.99 	30+20 bag1 com.qywl.killBlock.bag1 ������ʯx30����x20 ����$0.99���50����ʯ
*/