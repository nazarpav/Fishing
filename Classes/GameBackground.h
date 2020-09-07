#ifndef PROJ_ANDROID_GAMEBACKGROUND_H
#define PROJ_ANDROID_GAMEBACKGROUND_H
#include "cocos2d.h"
#include "Utils.h"
class GameBackground {
private:
	Utils _utils;
	const std::string GameSchedulerKey = "GameScheduler";
	cocos2d::Sprite* _backgroundSprite;
	cocos2d::Sprite* _mapWallLeftSprite;
	cocos2d::Sprite* _mapWallRightSprite;
	void InitMapWalls();
	void InitGameBackground();
	void UpdateGameBackground(const float dt);
	void Schedule();
	void Unschedule();
public:
	void init(cocos2d::Scene* scene);
	GameBackground();
	~GameBackground();
};
#endif //PROJ_ANDROID_GAMEBACKGROUND_H
