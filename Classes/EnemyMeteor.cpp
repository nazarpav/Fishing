#include "EnemyMeteor.h"
USING_NS_CC;

EnemyMeteor::EnemyMeteor() :BaseEnemy("images/Enemy_3.png")
{
	Vector<SpriteFrame*> idleAnimation; 
	idleAnimation.reserve(4);
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/Enemy_1.png", Rect(0, 0, 30, 30 - 64)));
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/Enemy_2.png", Rect(0, 0, 30, 30 - 64)));
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/Enemy_1.png", Rect(0, 0, 30, 30 - 64)));
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/Enemy_2.png", Rect(0, 0, 30, 30 - 64)));
	initAnimation(idleAnimation, 0.2f);
}

/*EnemyMeteor::~EnemyMeteor()
{
}*/