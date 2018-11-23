#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

#import "IosLocalUtil.h"
#import "cocos2d.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//                                              objective-c
////////////////////////////////////////////////////////////////////////////////////////////////
@interface LocalUtilHelper: NSObject <GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GKMatchmakerViewControllerDelegate, GKMatchDelegate>{
    
}
+ (LocalUtilHelper *)getInstance;
- (NSString*)getCurrentLanguage;
//- (BOOL)getIsTaiwanChinese;
@end
//---------------------------------------------------------------------------------------

@implementation LocalUtilHelper

//静态初始化 对外接口
static LocalUtilHelper *_instance = nil;
+ (LocalUtilHelper *) getInstance {
    if (!_instance) {
        _instance = [[LocalUtilHelper alloc] init];
    }
    return _instance;
}

- (id)init {
    if ((self = [super init])){
        
    }
    return self;
}

 //得到本机现在用的语言
 //en:英文  zh-Hans:简体中文   zh-Hant:繁体中文    ja:日本  ......
 
- (NSString*)getCurrentLanguage{
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    NSArray* languages = [defaults objectForKey:@"AppleLanguages"];
    NSString* currentLanguage = [languages objectAtIndex:0];
    return currentLanguage;
}

/*- (BOOL)getIsTaiwanChinese{
	NSString* currentLanguage=[self getCurrentLanguage];
    NSLog(@"===========currentLanguage is :%@", currentLanguage);
	return [currentLanguage isEqualToString:@"zh-Hant"];
}*/

@end



////////////////////////////////////////////////////////////////////////////////////////////////
//                                              c++
////////////////////////////////////////////////////////////////////////////////////////////////
IosLocalUtil* IosLocalUtil::_instance=nullptr;
IosLocalUtil* IosLocalUtil::getInstance(){
	if(_instance==nullptr){
        _instance=new IosLocalUtil();
       // [LocalUtilHelper getInstance].cCaller=_instance;
    }
	return _instance;
}

std::string IosLocalUtil::getCurrentLanguage() const{
    NSString* nsStr=[[LocalUtilHelper getInstance] getCurrentLanguage];
   // const char* lpfaceName = [nsStr UTF8String];
    std::string language=[nsStr UTF8String];
    return language;
}

/**
 * HongKong:zh-HK, Taiwan:zh-TW, fanTi: zh-Hant-CN
 */
bool IosLocalUtil::getIsTaiwanChinese(){
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	//return [[LocalUtilHelper getInstance] getIsTaiwanChinese];
    NSString* nsStr=[[LocalUtilHelper getInstance] getCurrentLanguage];
    std::string language=[nsStr UTF8String];
    return language=="zh-HK"||language=="zh-TW"||language=="zh-Hant-CN"||language=="zh-Hant";
#endif
return false;
}
