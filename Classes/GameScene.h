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
	cocos2d::PhysicsBody* PlayerBody;
	bool IsLeftButtonPressed = false;
	bool IsRightButtonPressed = false;
	const cocos2d::Size SCREENSIZE;
	const cocos2d::Size VISIBLESIZE;
	const cocos2d::Vec2 ORIGIN;
	const float GLOBALSCALE;
	void ButtonShootCallback(cocos2d::Ref* s);
	void InitPlayer();
	void InitButtons();
	virtual bool init();
public:
	GameScene();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameScene);
};
#endif //PROJ_ANDROID_GAMESCENE_H
