#include "EnemyShip.h"
USING_NS_CC;

EnemyShip::EnemyShip() :BaseEnemy("images/enemy/Enemy_1.png")
{
	Vector<SpriteFrame*> idleAnimation;
	idleAnimation.reserve(4);
	idleAnimation.pushBack(SpriteFrame::create("images\\enemy\\animations\\engineFireAnimation\\_1.png", Rect(0, 0, 30, 30)));
	idleAnimation.pushBack(SpriteFrame::create("images\\enemy\\animations\\engineFireAnimation\\_2.png", Rect(0, 0, 30, 30)));
	idleAnimation.pushBack(SpriteFrame::create("images\\enemy\\animations\\engineFireAnimation\\_3.png", Rect(0, 0, 30, 30)));
	idleAnimation.pushBack(SpriteFrame::create("images\\enemy\\animations\\engineFireAnimation\\_4.png", Rect(0, 0, 30, 30)));
	initAnimation(idleAnimation, 0.2f);
}

//EnemyShip::~EnemyShip()
//{
//}
