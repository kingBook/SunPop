#include "HelloWorldScene.h"
#include "MyGame.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
   // scheduleOnce(schedule_selector(HelloWorld::delayTest),3);
	MyGame*game=MyGame::create();
	this->addChild(game);
    return true;
}

void HelloWorld::delayTest(float t){
	log("delayTest");
	/*CCParticleExplosion* effect = CCParticleExplosion::create();
    effect->setTexture(CCTextureCache::sharedTextureCache()->addImage("star.png"));
    effect->setTotalParticles(15);
    effect->setStartColor(ccc4f(253/255.0f,80/255.0f,126/255.0f,1));
    effect->setStartColorVar(ccc4f(0,0,0,1));
    effect->setEndColor(ccc4f(253/255.0f,80/255.0f,126/255.0f,1));
    effect->setEndColorVar(ccc4f(0,0,0,1));
    effect->setStartSize(25.0f);
    effect->setGravity(Point(0,-200));
    effect->setLife(5.0f);
    effect->setSpeed(250);
    effect->setSpeedVar(20);
    effect->setPosition(getPosition());
	effect->setPosVar(Point(240,400));
	effect->setAutoRemoveOnFinish(true);
	 addChild(effect);*/

	/*ParticleSystemQuad* effect=ParticleSystemQuad::create("effect.plist");
	effect->setStartColor(Color4F::RED);
    effect->setEndColor(Color4F::RED);
	effect->setPosition(Point(240,400));
	effect->setAutoRemoveOnFinish(true);
	addChild(effect);*/
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
