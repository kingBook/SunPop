#ifndef __LOCAL_UTIL_H__
#define __LOCAL_UTIL_H__
#include "cocos2d.h"
USING_NS_CC;
class LocalUtil{
public:
	static LocalUtil* getInstance();
	LanguageType getLanguage(){ return _language; }
    
    /**
     * HongKong:zh-HK, Taiwan:zh-TW, fanTi: zh-Hant-CN
     */
    std::string getIosLanguage()const{return _iosLanguage;}
    
	/**�Ƿ�������*/
	bool getIsTaiwanCn(){return _isTaiwanCn;};
	/**�Ǽ�������*/
	bool getIsSCn(){return _isCn&&!_isTaiwanCn;};
	/**������*/
	bool getIsCn(){return _isCn;}
public:
	LocalUtil();
	~LocalUtil();
	/**
	*isCnGetTaiwan: ��ʾ����Ƿ������ģ��Ƿ��ȡ���������ַ�
	*/
	std::string getKeyString(const std::string &key,bool isCnGetTaiwan=false)const;
private:
	static LocalUtil* _instance;
private:
	std::unordered_map<int,std::string> _xmlPaths;
	LanguageType _language;
	bool _isTaiwanCn=false;
	bool _isCn=false;
    std::string _iosLanguage="";
};
#endif