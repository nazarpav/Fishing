#ifndef PROJ_ANDROID_UI_H
#define PROJ_ANDROID_UI_H
#include "cocos\editor-support\cocostudio\SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Utils.h"
class GameUI {
private:
	Utils _utils;
	void ButtonShootCallback(cocos2d::Ref* s);
	cocos2d::PhysicsBody* _player;
	cocos2d::Scene* _scene;
	std::function<void()> _exitGameCallback;
public:
	void init();
	GameUI(cocos2d::PhysicsBody* player, cocos2d::Scene* scene, std::function<void()> exitGameCallback);
	~GameUI();
};
#endif //PROJ_ANDROID_UI_H
