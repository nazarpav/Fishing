#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H
#pragma once
#include "cocos2d.h"
#include "UI.h"
#include "Player.h"
#include "GameBackground.h"
#include "MenuScene.h"
#include "EnemyController.h"
class GameScene : public cocos2d::Scene
{
	Utils _utils;
	Player _player;
	GameBackground _gameBackground;
	GameUI _gameUi;
	EnemyController* _enemyController;
	virtual bool init();
public:
	GameScene();
	~GameScene();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameScene);
};
#endif //PROJ_ANDROID_GAMESCENE_H
