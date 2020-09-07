#include "GameScene.h"
USING_NS_CC;

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	getPhysicsWorld()->setDebugDrawMask(0xffff);
	addChild(_player.getNode());
	_gameBackground.init(this);
	_gameUi.init();
	return true;
}

GameScene::GameScene() :_gameUi(GameUI(_player.getPhysicsBody(), this,
	[]() {Director::getInstance()->replaceScene(MenuScene::createScene()); }))
{
}

GameScene::~GameScene()
{
}

cocos2d::Scene* GameScene::createScene()
{
	return GameScene::create();
}
