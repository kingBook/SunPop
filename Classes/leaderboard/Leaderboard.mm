#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

#import "Leaderboard.h"
#import "cocos2d.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//                                              objective-c
////////////////////////////////////////////////////////////////////////////////////////////////
@interface GameKitHelper : NSObject <GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GKMatchmakerViewControllerDelegate, GKMatchDelegate>{
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;
}

@property (assign, readonly) BOOL gameCenterAvailable;
@property (nonatomic, assign) Leaderboard *leaderboard;
+ (GameKitHelper *)sharedGameKitHelper;
- (void) authenticateLocalUser;

- (void) showLeaderboard;
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;
- (void) reportScore: (int64_t) score forCategory: (NSString*) category;
@end
//---------------------------------------------------------------------------------------

@implementation GameKitHelper
@synthesize gameCenterAvailable;

//静态初始化 对外接口
static GameKitHelper *sharedHelper = nil;
static UIViewController* currentModalViewController = nil;
+ (GameKitHelper *) sharedGameKitHelper {
    if (!sharedHelper) {
        sharedHelper = [[GameKitHelper alloc] init];
    }
    return sharedHelper;
}

//对Game Center支持判断
- (BOOL)isGameCenterAvailable {
    // check for presence of GKLocalPlayer API
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));

    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer =@"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer 
    options:NSNumericSearch] != NSOrderedAscending);

    return (gcClass && osVersionSupported);
}

- (id)init {
    if ((self = [super init])){
        gameCenterAvailable = [self isGameCenterAvailable];
        if (gameCenterAvailable) {
            NSNotificationCenter *nc = 
            [NSNotificationCenter defaultCenter];
            [nc addObserver:self 
            selector:@selector(authenticationChanged) 
            name:GKPlayerAuthenticationDidChangeNotificationName 
            object:nil];
        }
    }
    return self;
}

//后台回调登陆验证
- (void)authenticationChanged {
    if ([GKLocalPlayer localPlayer].isAuthenticated &&!userAuthenticated) {
        NSLog(@"Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
		_leaderboard->authenticateLocalUserFinish(true);
    } else if (![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated) {
        NSLog(@"Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
		_leaderboard->authenticateLocalUserFinish(false);
    }
}

//用户登录
- (void)authenticateLocalUser { 
    if (!gameCenterAvailable) return;
        NSLog(@"Authenticating local user...");
        if ([GKLocalPlayer localPlayer].authenticated == NO) { 
            [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:nil]; 
        } else {
        NSLog(@"Already authenticated!");
    }
}

//显示排行榜
- (void) showLeaderboard{
    if (!gameCenterAvailable) return;
    GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
    if (leaderboardController != nil) {
        leaderboardController.leaderboardDelegate = self;

        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        currentModalViewController = [[UIViewController alloc] init];
        [window addSubview:currentModalViewController.view];
        [currentModalViewController presentModalViewController:leaderboardController animated:YES];
    }
}

//关闭排行榜回调
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController{
    if(currentModalViewController !=nil){
        [currentModalViewController dismissModalViewControllerAnimated:NO];
        [currentModalViewController release];
        [currentModalViewController.view removeFromSuperview];
        currentModalViewController = nil;
    }
}

// 上传一个分数
- (void) reportScore: (int64_t) score forCategory: (NSString*) category
{
    GKScore *scoreReporter = [[[GKScore alloc] initWithCategory:category] autorelease];
    scoreReporter.value = score;
    [scoreReporter reportScoreWithCompletionHandler:^(NSError *error) {
        if (error != nil)
        {
            // handle the reporting error
            NSLog(@"上传分数出错.");
            //If your application receives a network error, you should not discard the score.
            //Instead, store the score object and attempt to report the player’s process at
            //a later time.
			_leaderboard->submitScoreFinish(false);
        }else {
            NSLog(@"上传分数成功");
			_leaderboard->submitScoreFinish(true);
        }
        
    }];
}
@end



////////////////////////////////////////////////////////////////////////////////////////////////
//                                              c++
////////////////////////////////////////////////////////////////////////////////////////////////
Leaderboard* Leaderboard::_instance=nullptr;
Leaderboard *Leaderboard::getInstance(){
	if(_instance==nullptr){
        _instance=new Leaderboard();
        [GameKitHelper sharedGameKitHelper].leaderboard=_instance;
    }
	return _instance;
}

void Leaderboard::authenticateLocalUser(AuthenticateLocalUserCallback callback){
    _authenticateLocalUserCallback=callback;
    [[GameKitHelper sharedGameKitHelper] authenticateLocalUser];
}

void Leaderboard::showLeaderboard(){
    [[GameKitHelper sharedGameKitHelper] showLeaderboard];
}

void Leaderboard::submitScore(int score, SubmitScoreCallback callback){
    _submitScoreCallback=callback;
    int64_t val=(int64_t)score;
    [[GameKitHelper sharedGameKitHelper] reportScore:val forCategory:@"com.qywl.SunPop.scoreLeaderboard"];
}

/**登录完成*/
void Leaderboard::authenticateLocalUserFinish(bool succeed){
	if(_authenticateLocalUserCallback){
		_authenticateLocalUserCallback(succeed);
	}
}

/**提交分数完成*/
void Leaderboard::submitScoreFinish(bool succeed){
	if(_submitScoreCallback){
		_submitScoreCallback(succeed);
	}
}
