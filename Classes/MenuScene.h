#ifndef PROJ_ANDROID_MENUSCENE_H
#define PROJ_ANDROID_MENUSCENE_H
#pragma once
#include <ui/CocosGUI.h>
#include <cocos2d.h>
#include <math.h>
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "Utils.h"
class MenuScene : public cocos2d::Scene
{
private:
	const cocos2d::Size SCREENSIZE;
	const cocos2d::Size VISIBLESIZE;
	const cocos2d::Vec2 ORIGIN;
	const std::string MenuSchedulerKey = "MenuScheduler";
	const float MenuFontSize = 41;
	cocos2d::Sprite* _backgroundImage;
	cocos2d::MenuItemLabel* CreateMenuItem(std::string text, cocos2d::Vec2 position, cocos2d::ccMenuCallback callBack);
	virtual bool init();
	void Schedule();
	void Unschedule();
	void UpdateMenuBackground(const float dt);
	void MenuBackgroundInit();
public:
	MenuScene();
	~MenuScene();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(MenuScene);
};
#endif //PROJ_ANDROID_MENUSCENE_H
