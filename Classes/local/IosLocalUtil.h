#ifndef __IOS_LOCALUTIL_H__
#define __IOS_LOCALUTIL_H__
class IosLocalUtil{
public:
    static IosLocalUtil*getInstance();
    bool getIsTaiwanChinese();
    std::string getCurrentLanguage() const;
private:
    static IosLocalUtil*_instance;
};
#endif /* __IOS_LOCALUTIL_H__*/
