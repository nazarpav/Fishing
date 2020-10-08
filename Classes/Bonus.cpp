#include "Bonus.h"
USING_NS_CC;
Bonus::Bonus(BonusType bonusType, Vec2 position)
{
	_baseNode =  Node::create();
	_baseNode->setPosition(position);
	Sprite* baseAnimation = Sprite::create();
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("images/Game/bonus/bonusBackgroundAnimation/bonusBackground_1.png", Rect(0, 0, 30, 30)));
	animFrames.pushBack(SpriteFrame::create("images/Game/bonus/bonusBackgroundAnimation/bonusBackground_2.png", Rect(0, 0, 30, 30)));
	animFrames.pushBack(SpriteFrame::create("images/Game/bonus/bonusBackgroundAnimation/bonusBackground_3.png", Rect(0, 0, 30, 30)));
	animFrames.pushBack(SpriteFrame::create("images/Game/bonus/bonusBackgroundAnimation/bonusBackground_4.png", Rect(0, 0, 30, 30)));
	baseAnimation->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f))));
	_baseNode->addChild(baseAnimation, 0);
	Sprite* sprite;
	switch (bonusType)
	{
	case FirstAidKit:
		sprite = Sprite::create("images/Game/bonus/firstAidKit.png");
		_baseNode->addChild(sprite, 1);
		break;
	case AmmoChest:
		sprite = Sprite::create("images/Game/bonus/ammo.png");
		_baseNode->addChild(sprite, 1);
		break;
	case UnknownBonus:
		sprite = Sprite::create("images/Game/bonus/ammo.png");
		break;
	default:
		return;
		break;
	}
	PhysicsBody* _playerBody;
	_playerBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height));
	_playerBody->setDynamic(true);
	_playerBody->setGravityEnable(false);
	_playerBody->setRotationEnable(false);
	_playerBody->setContactTestBitmask(0xFFFFFFFF);
	_baseNode->addComponent(_playerBody);
}

cocos2d::Node* Bonus::getNode()
{
	return _baseNode;
}

void Bonus::Action(Player& player, BonusType bonus)
{
	switch (bonus)
	{
	case FirstAidKit:
		player.equipFirstAidKit(20);
		break;
	case AmmoChest:
		break;
	case UnknownBonus:
		player.equipFirstAidKit(20);
		break;
	default:
		break;
	}
}
