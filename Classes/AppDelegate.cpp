#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameData.h"

#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "PluginAdMob/PluginAdMob.h"
#include "PluginIAP/PluginIAP.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    sdkbox::PluginAdMob::init();
	sdkbox::IAP::init();
#endif
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
	
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	glview->setFrameSize(480,800);
#endif
	glview->setDesignResolutionSize(480, 800, kResolutionExactFit);
    // turn on display FPS
    director->setDisplayStats(GameData::isDebug);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
