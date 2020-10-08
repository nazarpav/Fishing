#include "Player.h"
USING_NS_CC;
void Player::init()
{
	Sprite* sprite = Sprite::create("images/Player/PlayerIdle.png");
	sprite->setScale(_utils.GLOBALSCALE);
	_player->setPosition(Vec2(_utils.ORIGIN.x + _utils.VISIBLESIZE.width / 2 * _utils.GLOBALSCALE, _utils.ORIGIN.y + _utils.VISIBLESIZE.height / 4 * _utils.GLOBALSCALE));
	PhysicsBody* _playerBody;
	_playerBody = PhysicsBody::createBox(Size(sprite->getContentSize().width * _utils.GLOBALSCALE, sprite->getContentSize().height * _utils.GLOBALSCALE));
	_playerBody->setDynamic(true);
	_playerBody->setGravityEnable(false);
	_playerBody->setRotationEnable(false);
	Sprite* mySprite = Sprite::create();

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/__1.png", Rect(0, 0, 30 * _utils.GLOBALSCALE, 30 * _utils.GLOBALSCALE)));
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/__2.png", Rect(0, 0, 30 * _utils.GLOBALSCALE, 30 * _utils.GLOBALSCALE)));
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/__3.png", Rect(0, 0, 30 * _utils.GLOBALSCALE, 30 * _utils.GLOBALSCALE)));
	animFrames.pushBack(SpriteFrame::create("images/Player/EngineFireAnimation/__4.png", Rect(0, 0, 30 * _utils.GLOBALSCALE, 30 * _utils.GLOBALSCALE)));

	mySprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.2f))));
	mySprite->setPosition(Vec2(0, -3 * _utils.GLOBALSCALE));//
	mySprite->setScale(_utils.GLOBALSCALE);
	_playerBody->setContactTestBitmask(0xFFFFFFFF);

	_player->addComponent(_playerBody);
	_player->addChild(sprite, 0, "Idle");
	_player->addChild(mySprite, 2);
}

void Player::equipFirstAidKit(int health)
{
	_healthCount += health;
}

int Player::makeDamage(int damage)
{
	_healthCount -= damage;
	return _healthCount;
}

Player::Player()
{
	_player = Node::create();
	_healthCount = 100;
	init();
}

Player::~Player()
{
}

int Player::getHealthCount()
{
	return _healthCount;
}

Node* Player::getNode()
{
	return _player;
}

cocos2d::PhysicsBody* Player::getPhysicsBody()
{
	return _player->getPhysicsBody();
}
