#ifndef PROJ_ANDROID_MENUSCENE_H
#define PROJ_ANDROID_MENUSCENE_H
#include <cocos2d.h>
#include <math.h>
#include "HelloWorldScene.h"
#include "Utils.h"
#include <ui/CocosGUI.h>
class MenuScene :public cocos2d::Scene
{
private:
	cocos2d::Size screenSize;
	cocos2d::Sprite* _backgroundImage;
	cocos2d::Sprite* _point;
	cocos2d::Label* Dl;
	virtual bool init();
	void GameCloseCallback(cocos2d::Ref* pSender)const;
	void GameStartCallback(cocos2d::Ref* pSender)const;
	void Schedule();
	void Unschedule();
	void Update(const float dt);
	void BackgroundImagesInit();
	void BackgroundImagesRelease()const;
public:
	MenuScene();
	~MenuScene();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(MenuScene);
};
#endif //PROJ_ANDROID_MENUSCENE_H
