#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H
#pragma once
#include <ui/CocosGUI.h>
#include "MenuScene.h"
#include <cocos2d.h>
#include <math.h>
class GameScene : public cocos2d::Scene
{
	cocos2d::Node* Player;
	cocos2d::Animation* anim;
	cocos2d::PhysicsBody* PlayerBody;
	const std::string GameSchedulerKey = "GameScheduler";
	cocos2d::Sprite* _backgroundSprite;
	cocos2d::Sprite* _mapWallLeftSprite;
	cocos2d::Sprite* _mapWallRightSprite;
	const cocos2d::Size SCREENSIZE;
	const cocos2d::Size VISIBLESIZE;
	const cocos2d::Vec2 ORIGIN;
	const float GLOBALSCALE;
	void ButtonShootCallback(cocos2d::Ref* s);
	void InitPlayer();
	void InitMapWalls();
	void InitButtons();
	void InitShells();
	void InitGameBackground();
	virtual bool init();
	void Schedule();
	void Unschedule();
	void UpdateGameBackground(const float dt);
public:
	GameScene();
	~GameScene();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameScene);
};
#endif //PROJ_ANDROID_GAMESCENE_H
