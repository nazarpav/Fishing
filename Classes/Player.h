#ifndef PROJ_ANDROID_PLAYER_H
#define PROJ_ANDROID_PLAYER_H
#include "cocos2d.h"
#include "Utils.h"
class Player {
private:
	Utils _utils;
	cocos2d::Node* _player;
	cocos2d::PhysicsBody* _playerBody;
	void init();
public:
	Player();
	~Player();
	cocos2d::Node* getNode();
	cocos2d::PhysicsBody* getPhysicsBody();
};
#endif //PROJ_ANDROID_PLAYER_H
