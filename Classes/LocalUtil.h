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
    
	/**是繁体中文*/
	bool getIsTaiwanCn(){return _isTaiwanCn;};
	/**是简体中文*/
	bool getIsSCn(){return _isCn&&!_isTaiwanCn;};
	/**是中文*/
	bool getIsCn(){return _isCn;}
public:
	LocalUtil();
	~LocalUtil();
	/**
	*isCnGetTaiwan: 表示如果是繁体中文，是否获取繁体中文字符
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