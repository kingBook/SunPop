#include "LocalUtil.h"
#include "cocos2d.h"

#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "IosLocalUtil.h"
#endif/*CC_PLATFORM_IOS*/

LocalUtil* LocalUtil::_instance=nullptr;
LocalUtil* LocalUtil::getInstance(){
	if(_instance==nullptr)_instance=new LocalUtil();
	return _instance;
}

LocalUtil::LocalUtil(){
	_language=Application::getInstance()->getCurrentLanguage();
	_xmlPaths[0]="xmls/strings_en.xml";
	_xmlPaths[1]="xmls/strings_scn.xml";
	_xmlPaths[2]="xmls/strings_taiwancn.xml";

	_isCn=(_language==LanguageType::CHINESE);
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    _iosLanguage=IosLocalUtil::getInstance()->getCurrentLanguage();
	if(_isCn){
		_isTaiwanCn=IosLocalUtil::getInstance()->getIsTaiwanChinese();
	}
#endif/*CC_PLATFORM_IOS*/
	//²âÊÔ·±Ìå
	//_isCn=_isTaiwanCn=true;
	//²âÊÔÓ¢ÎÄ
	//_isCn=_isTaiwanCn=false;
}

LocalUtil::~LocalUtil(){
	
}

std::string LocalUtil::getKeyString(const std::string &key,bool isCnGetTaiwan/*=false*/)const{
    int id=0;
	if(_isCn){
		if(isCnGetTaiwan&&_isTaiwanCn)id=2;
		else id=1;
	}
    std::string path=_xmlPaths.at(id);
    ValueMap valueMap=FileUtils::getInstance()->getValueMapFromFile(path);
    return valueMap.at(key).asString();
}