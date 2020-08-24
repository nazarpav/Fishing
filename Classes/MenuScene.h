#ifndef PROJ_ANDROID_MENUSCENE_H
#define PROJ_ANDROID_MENUSCENE_H
#include <cocos2d.h>
#include "HelloWorldScene.h"
#include "Utils.h"
#include <ui/CocosGUI.h>
class MenuScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void gameCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
};
#endif //PROJ_ANDROID_MENUSCENE_H
