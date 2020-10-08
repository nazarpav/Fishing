#include "EnemyShip.h"
USING_NS_CC;

std::string EnemyShip::generateSpritePath()
{
	int _random = random(1, 2);
	switch (_random)
	{
	case 1:
		return "images/enemy/Enemy_1.png";
	case 2:
		return "images/enemy/Enemy_2.png";
	}
}

EnemyShip::EnemyShip() :BaseEnemy(generateSpritePath())
{
	Vector<SpriteFrame*> idleAnimation;
	idleAnimation.reserve(4);
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/animations/engineFireAnimation/_1.png", Rect(0, 0, 30, 30)));
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/animations/engineFireAnimation/_2.png", Rect(0, 0, 30, 30)));
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/animations/engineFireAnimation/_3.png", Rect(0, 0, 30, 30)));
	idleAnimation.pushBack(SpriteFrame::create("images/enemy/animations/engineFireAnimation/_4.png", Rect(0, 0, 30, 30)));
	initAnimation(idleAnimation, 0.1f);
}

//EnemyShip::~EnemyShip()
//{
//}
