#include "EnemyMeteor.h"
USING_NS_CC;

EnemyMeteor::EnemyMeteor() :BaseEnemy("images/enemy/Enemy_3.png")
{
	Vector<SpriteFrame*> idleAnimation;
	idleAnimation.reserve(4);
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/animations/meteorTailAnimation/_1.png", Rect(0, 0, 30, 64)));
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/animations/meteorTailAnimation/_2.png", Rect(0, 0, 30,64)));
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/animations/meteorTailAnimation/_3.png", Rect(0, 0, 30, 64)));
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/animations/meteorTailAnimation/_4.png", Rect(0, 0, 30,64)));
	initAnimation(idleAnimation, 0.1f);
}

/*EnemyMeteor::~EnemyMeteor()
{
}*/