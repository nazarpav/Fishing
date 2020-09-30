#ifndef PROJ_ANDROID_ENEMYCONTROLLER_H
#define PROJ_ANDROID_ENEMYCONTROLLER_H
#include"Utils.h"
#include"cocos2d.h"
#include"BaseEnemy.h"
#include"EnemyMeteor.h"
#include"EnemyShip.h"
#include "cocos\editor-support\cocostudio\SimpleAudioEngine.h"
#include <UI.h>
//#include<chrono>
//#include<ctime>
class EnemyController {
private:
	Utils _utils;
	cocos2d::Scene* _scene;
	cocos2d::PhysicsBody* _barrierForEnemies;
	//cocos2d::Animation* _explosionAnimation;
	cocos2d::Vector<cocos2d::SpriteFrame*> _framesVector;
	cocos2d::Action* _explosionAnimation;
	GameUI* _ui;
public:
	EnemyController(cocos2d::Scene* scene, GameUI* ui);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	~EnemyController();
};
#endif //PROJ_ANDROID_ENEMYCONTROLLER_H
