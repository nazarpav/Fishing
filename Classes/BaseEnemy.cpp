#include "BaseEnemy.h"
USING_NS_CC;
void BaseEnemy::initAnimation(const Vector<SpriteFrame*>& idleAnimationsPates, const  float animationDelay)
{
	//Sprite* _baseIdleEnemySpriteAnimation = Sprite::create();
	//_baseIdleEnemySpriteAnimation->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(idleAnimationsPates, animationDelay))));
	////_baseIdleEnemySpriteAnimation->setPosition(Point::ZERO);
	//_baseEnemyNode->addChild(_baseIdleEnemySpriteAnimation, 1);
}
BaseEnemy::BaseEnemy(const std::string& pathToBaseEnemySprite) 
{
	_baseEnemyNode = Node::create();
	Sprite* _baseIdleEnemySprite = Sprite::create(pathToBaseEnemySprite);
	_baseEnemyPhysicsBody = PhysicsBody::createBox(Size(_baseIdleEnemySprite->getContentSize().width, _baseIdleEnemySprite->getContentSize().height));
	//_baseEnemyPhysicsBody->setCategoryBitmask(BaseEnemy::getCategoryBitmask());
	//_baseEnemyPhysicsBody->setCollisionBitmask(BaseEnemy::getCollisionBitmask());
	_baseEnemyPhysicsBody->setContactTestBitmask(0xFFFFFFFF);
	_baseEnemyPhysicsBody->setDynamic(true);
	_baseEnemyPhysicsBody->setGravityEnable(false);
	_baseEnemyPhysicsBody->setRotationEnable(false);
	_baseEnemyNode->addComponent(_baseEnemyPhysicsBody);
	_baseEnemyNode->addChild(_baseIdleEnemySprite,0,1001);
}

cocos2d::Node* BaseEnemy::getNode()const
{
	return _baseEnemyNode;
}

void BaseEnemy::setPosition(const Vec2& position)const
{
	_baseEnemyNode->setPosition(position);
}

void BaseEnemy::setVelocity(const cocos2d::Vec2& velocity)const
{
	_baseEnemyPhysicsBody->setVelocity(velocity);
}

int BaseEnemy::getCollisionBitmask()
{
	return 0x01;
}

int BaseEnemy::getCategoryBitmask()
{
	return 0x02;
}
