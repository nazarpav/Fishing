#ifndef PROJ_ANDROID_BASEENEMY_H
#define PROJ_ANDROID_BASEENEMY_H
#include "cocos2d.h"
#include "Utils.h"
class BaseEnemy {
protected:
	Utils _utils;
	cocos2d::Node* _baseEnemyNode;
	cocos2d::PhysicsBody* _baseEnemyPhysicsBody;
	void initAnimation(const  cocos2d::Vector<cocos2d::SpriteFrame*>& idleAnimationsPates, const  float animationDelay);
public:
	BaseEnemy(const std::string& pathToBaseEnemySprite);
	cocos2d::Node* getNode()const;
	void setPosition(const cocos2d::Vec2& position)const;
	void setVelocity(const cocos2d::Vec2& velocity)const;
	static int getCollisionBitmask();
	static int getCategoryBitmask();
	//virtual ~BaseEnemy() = 0;
};
#endif //PROJ_ANDROID_BASEENEMY_H
