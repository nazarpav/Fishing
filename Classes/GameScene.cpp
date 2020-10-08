#include "GameScene.h"
USING_NS_CC;

bool GameScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	getPhysicsWorld()->setDebugDrawMask(0xffff);
	addChild(_player.getNode(), 0, 104);
	_gameBackground.init(this);
	_gameUi.init();
	_enemyController = new EnemyController(this, _gameUi);
	return true;
}

GameScene::GameScene() :_gameUi(GameUI(_player, this,
	[]() {Director::getInstance()->replaceScene(MenuScene::createScene()); }))
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/BackgroundSoundInGame.mp3", true);
}

GameScene::~GameScene()
{
	delete _enemyController;
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

cocos2d::Scene* GameScene::createScene()
{
	return GameScene::create();
}
